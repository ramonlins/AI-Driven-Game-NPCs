import socket
#import pdb
import traceback
import struct

import ray
import numpy as np

from ray.rllib.algorithms.algorithm import Algorithm
from gymnasium.spaces import Box


def serialize_action(action) -> bytes:
    """ Serialized actions

    Args:
        action (array): Next coordinates (x', y') of agent

    Returns:
        bytes: serilized action data
    """
    # Create a byte object to hold the serialized data
    data_bytes = b''

    # Pack each float into the byte object
    for value in action:
        data_bytes += struct.pack('f', value)

    return data_bytes


# Setup server
HOST = "127.0.0.1"
PORT: int = 8888

# MoveToGoal I/O config
action_space = Box(low=-float('inf'), high=float('inf'), shape=(2,))
observation_space = Box(low=-float('inf'), high=float('inf'), shape=(6,))

env_config = {
    "action_space": action_space,
    "observation_space": observation_space
}

# Define your custom checkpoint directory
checkpoint_dir = "/home/rlins/Git/AI-Driven-Game-NPCs/Unreal/MoveToGoal/results"

try:
    # IPv4
    network = socket.AF_INET

    # TCP
    transport = socket.SOCK_STREAM
    with socket.socket(network, transport) as s:
        # Link host and port
        s.bind((HOST, PORT))

        # Listen to client
        s.listen()

        print("Waiting for Unreal Client ...")
        connection, client_adress = s.accept()

        with connection:
            print("Connected by", client_adress)
            data = connection.recv(1024).decode('utf-8')

            if data == "Hello Server":
                print("Received handshake from Unreal client")
                connection.sendall(b"Hello Client")
                is_conn = True

                # Start learning
                if (is_conn):
                    print("Starting ray ...")
                    ray.init()

                    ppo_algo = Algorithm.from_checkpoint(checkpoint_dir)

                    # Receive first data
                    initial_data = connection.recv(32)

                    # Unserialized data obs<FVector> + reward<float> + done<int32>
                    us_data = struct.unpack("fffffffi", initial_data)
                    obs, reward, done = us_data[:6], us_data[6], us_data[-1]

                    print(f"Received Initial OBS: {obs}")
                    print(f"Received Initial REWARD: {reward}")
                    print(f"Received Initial state DONE: {done}")

                    # Take action
                    action = ppo_algo.compute_single_action(np.array(obs))

                    action_bytes = serialize_action(action)

                    # Send the action
                    connection.sendall(action_bytes)

                    # Receive next data from unreal
                    next_data = connection.recv(32)

                    # obs_batch, rew_batch, done_batch = [], [], []
                    # Start reinforcement learning loop
                    while True:
                        # Episodes are controlled in unreal
                        next_us_data = struct.unpack("fffffffi", next_data)

                        # TODO: Fix it (Close)
                        if not data:
                            break

                        next_obs, reward, done = next_us_data[:6], next_us_data[6], next_us_data[-1]

                        print(f"Received FVector OBS: {next_obs}")
                        print(f"Received FVector REWARD: {reward}")
                        print(f"Received int DONE: {done}")

                        # Take action from next states
                        action = ppo_algo.compute_single_action(np.array(next_obs))

                        action_bytes = serialize_action(action)

                        # Send action
                        connection.sendall(action_bytes)

                        obs = next_obs

                        # Receive data from unreal
                        next_data = connection.recv(32)

    ray.shutdown()

except Exception as error:
    print("Error message:", error)
    print("-" * 60)
    traceback.print_exc()  # This prints the full traceback
    print("-" * 60)

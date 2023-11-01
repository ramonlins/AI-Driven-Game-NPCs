import socket
import pdb
import traceback
import struct

import ray
import numpy as np
import gymnasium as gym

from ray.rllib.algorithms.ppo import PPO, PPOConfig
from gymnasium.spaces import Box

#from MockEnv import GlobalStateManager, MockEnv


class GlobalStateManager:
    def __init__(self):
        self.observation = np.zeros(6)
        self.reward = np.zeros(1)
        self.done = False

    def update(self, observation, reward, done):
        self.observation = observation
        self.reward = reward
        self.done = False if done == 0 else True

    def get_state(self):
        return self.observation, self.reward, self.done, {}


class MockEnv(gym.Env):
    def __init__(self, env_config):
        super().__init__()
        self.action_space = env_config["action_space"]
        self.observation_space = env_config["observation_space"]
        #self.global_state_manager = env_config["state_manage"]

        self.current_observation_space = np.zeros(self.observation_space.shape[0])
        self.current_reward = np.zeros(1)
        self.current_done = False

    def step(self, action):
        # Get the updated state from the global state manager
        observation, reward, done, _ = global_state_manager.get_state()

        return observation, reward, done, {}

    def reset(self):
        # return self.current_observation_space, self.current_reward, self.current_done, False, {}
        observation, _, _, _ = global_state_manager.get_state()

        return observation


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


# Manage mock environment
global_state_manager = GlobalStateManager()

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

                    # Configuring PPO
                    config = PPOConfig()
                    config.rollouts(num_rollout_workers=0)
                    config.environment(env=MockEnv,  env_config=env_config)
                    config.environment(disable_env_checking=True)
                    config.resources(num_gpus=1, num_gpus_per_learner_worker=1)

                    # Create ppo algorithm
                    ppo_algo = PPO(config=config)

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

                    # Start reinforcement learning loop
                    while True:
                        # Episodes are controlled in unreal
                        next_us_data = struct.unpack("fffffffi", next_data)
                        next_obs, reward, done = next_us_data[:6], next_us_data[6], next_us_data[-1]

                        print(f"Received FVector OBS: {next_obs}")
                        print(f"Received FVector REWARD: {reward}")
                        print(f"Received int DONE: {done}")

                        # Update mock environment states, reward and done state
                        global_state_manager.update(np.array(next_obs), np.array(reward), done)

                        # Train ppo with new data
                        ppo_algo.train()

                        # Take action from next states
                        action = ppo_algo.compute_single_action(np.array(next_obs))

                        action_bytes = serialize_action(action)

                        # Send action
                        connection.sendall(action_bytes)

                        # TODO: Fix it (Close)
                        if not data:
                            break

                        # Receive data from unreal
                        next_data = connection.recv(32)

    ray.shutdown()

except Exception as error:
    print("Error message:", error)
    print("-" * 60)
    traceback.print_exc()  # This prints the full traceback
    print("-" * 60)

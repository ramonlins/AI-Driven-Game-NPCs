import socket
import pdb
import traceback
import struct
from inference import MLPAgent
import numpy as np

# Setup server
HOST = "127.0.0.1"
PORT: int = 8888

# Build model
model = MLPAgent(3, 2)

try:
    # IPv4
    network = socket.AF_INET
    # TCP
    protocol = socket.SOCK_STREAM
    with socket.socket(network, protocol) as s:
        s.bind((HOST, PORT))
        s.listen()
        print("Waiting for Unreal Client ...")
        connection, client_adress = s.accept()
        with connection:
            print("Connected by", client_adress)
            data = connection.recv(1024).decode('utf-8')
            while True:
                if data == "Hello Server":
                    print("Received handshake from Unreal client")
                    connection.sendall(b"Hello Client")
                    is_conn = True

                #if is_conn:
                    # Receive data from unreal
                    #for ep in range(50):
                    #    data = connection.recv(32)
                    #    t = 0
                    #    done = False
                    #    while not done or t == 1000:
                            # Unpack the received FVector
                else:
                    us_data = struct.unpack("fffffffi", data)

                    obs, reward, done = us_data[:6], us_data[6], us_data[-1]

                    print(f"Received FVector OBS: {obs}")
                    print(f"Received FVector REWARD: {reward}")
                    print(f"Received int DONE: {done}")

                    # Get action
                    #action = model(obs[:3])
                    # TODO: inference
                    #action = trainer.compute_action(obs)

                    #pdb.set_trace()
                    action = np.random.uniform(-5, 5, 2)
                    #action = np.array([10, 0, 0])
                    # Convert the numpy array to a flattened list
                    #data_list = action.tolist()

                    # Create a byte object to hold the serialized data
                    data_bytes = b''

                    # Pack each float into the byte object
                    for value in action:
                        data_bytes += struct.pack('f', value)

                    # Send action
                    connection.sendall(data_bytes)

                    # TODO: Fix it (Close)
                    if not data or done == 1:
                        break

                    #t += 1

                # Receive data from unreal
                data = connection.recv(32)

                    # TODO: Trainer
                    # trainer.train()


except Exception as error:
    # exc_traceback = traceback.extract_tb(error.__traceback__)
    # filename = exc_traceback[-1].filename
    # line_number = exc_traceback[-1].lineno
    # print(f"Exception occurred in file {filename} at line {line_number}. Error message: {error}")
    print("Error message:", error)
    print("-" * 60)
    traceback.print_exc()  # This prints the full traceback
    print("-" * 60)

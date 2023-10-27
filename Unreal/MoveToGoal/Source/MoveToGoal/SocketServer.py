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
                else:
                    # Unpack the received FVector
                    obs = struct.unpack("fff", data)
                    print(f"Received FVector: {obs[0]}, {obs[1]}, {obs[2]}")

                    # Get action
                    action = model(obs)
                    print(action)
                    #pdb.set_trace()
                    #action = np.random.uniform(-20, 20, 2)

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
                    if not data:
                        break
                # Receive data from unreal
                data = connection.recv(12)

except Exception as error:
    # exc_traceback = traceback.extract_tb(error.__traceback__)
    # filename = exc_traceback[-1].filename
    # line_number = exc_traceback[-1].lineno
    # print(f"Exception occurred in file {filename} at line {line_number}. Error message: {error}")
    print("Error message:", error)
    print("-" * 60)
    traceback.print_exc()  # This prints the full traceback
    print("-" * 60)

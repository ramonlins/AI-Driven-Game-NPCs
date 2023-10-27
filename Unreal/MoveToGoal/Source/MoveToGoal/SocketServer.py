import socket
import pdb
import struct
from inference import MLPAgent
import numpy as np

# Setup server
HOST = "127.0.0.1"
PORT: int = 8888


model = MLPAgent(3, 2)

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print("Waiting for Unreal Client ...")
        conn, addr = s.accept()
        with conn:
            print("Connected by", addr)
            data = conn.recv(1024).decode('utf-8')

            while True:
                if data == "Hello Server":
                    print("Received handshake from Unreal client")
                    conn.sendall(b"Hello Client")
                else:
                    # Unpack the received FVector
                    obs = struct.unpack("fff", data)
                    print(f"Received FVector: {obs[0]}, {obs[1]}, {obs[2]}")

                    # Get action
                    #action = model(obs)
                    #pdb.set_trace()
                    action = np.random.uniform(-20, 20, 2)

                    # Convert the numpy array to a flattened list
                    data_list = action.tolist()

                    # Create a byte object to hold the serialized data
                    data_bytes = b''

                    # Pack each float into the byte object
                    for value in data_list:
                        data_bytes += struct.pack('f', value)

                    # Send action
                    conn.sendall(data_bytes)

                    if not data:
                        break

                data = conn.recv(12)

except Exception as e:
    print(e)

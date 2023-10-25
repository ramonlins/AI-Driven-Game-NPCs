import socket
import pdb
import struct

# Setup server
HOST = "127.0.0.1"
PORT: int = 8888

try:
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print("Waiting for Unreal Client ...")
        #pdb.set_trace()
        conn, addr = s.accept()
        with conn:
            print("Connected by", addr)
            data = conn.recv(1024).decode('utf-8')

            while True:
                if data == "Hello":
                    print("Received handshake from Unreal client")
                    # conn.sendall(b"Connected")
                else:
                    # Unpack the received FVector
                    x, y, z = struct.unpack("fff", data)
                    print(f"Received FVector: {x}, {y}, {z}")

                    if not data:
                        break

                data = conn.recv(12)

except Exception as e:
    print(e)

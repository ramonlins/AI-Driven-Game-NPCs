import socket
import pdb

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
            while True:
                data = conn.recv(1024).decode('utf-8')
                if data == "Hello":
                    print("Received handshake from Unreal client")
                    conn.sendall(b"Connected")
                else:
                    break
except Exception as e:
    print(e)

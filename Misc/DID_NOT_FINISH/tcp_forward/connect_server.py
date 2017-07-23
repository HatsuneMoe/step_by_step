import socket
from world_is_mine_branch2 import PipeThread

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
    server_socket.connect(('45.62.118.18', 8877))

    server_socket.sendall(b'35f38fb7e5a09d139c16341010216d40bf921327')

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as target_conn:
        target_conn.connect(('127.0.0.1', 8888))
        print('new connect')
        # two direct pipe
        while True:
            PipeThread(server_socket, target_conn).start()


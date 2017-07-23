import select
import socket


class PipeThread:
    def __init__(self, source, target):
        self.source = source
        self.target = target
        self.fdset = [source, target]

    def start(self):
        while True:
            r, w, e = select.select(self.fdset, [], [])
            if self.source in r:
                data = self.source.recv(1024)
                if not data:
                    break
                self.target.send(data)
            if self.target in r:
                data = self.target.recv(1024)
                if not data:
                    break
                self.source.send(data)


class Forwarding:
    def __init__(self, _port):
        self.port = _port

    def run(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as target_socket:
            target_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            target_socket.bind(('0.0.0.0', 8877))
            target_socket.listen(1)
            while True:
                target_conn, target_addr = target_socket.accept()
                data = target_conn.recv(1024)
                print(data)
                if data == b'35f38fb7e5a09d139c16341010216d40bf921327':
                    print(target_addr)
                    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as cli_socket:
                        cli_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
                        cli_socket.bind(('0.0.0.0', self.port))
                        cli_socket.listen(10)
                        while True:
                            client_conn, client_addr = cli_socket.accept()
                            PipeThread(target_conn, client_conn).start()

if __name__ == '__main__':
    port = 8899
    Forwarding(port).run()


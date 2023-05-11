import socket

HOST = '127.0.0.1'
PORT = 12345

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))

print('Connected to server {}:{}'.format(HOST, PORT))
client.sendall(input('Please enter your name: ').encode())
data = client.recv(1024)
print('Received:', data.decode())

client.close()

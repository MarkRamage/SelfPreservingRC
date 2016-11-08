import zmq

context = zmq.Context()

print("Connecting to server")
socket = context.socket(zmq.REQ)
socket.connect("tcp://localhost:5555")

while True:
    socket.send(bytearray(True))
    message = socket.recv()
    byte = message
    print(byte)
    for elem in byte:
        print(bool(elem))

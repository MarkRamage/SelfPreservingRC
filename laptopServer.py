import time
import zmq
import pygame

context = zmq.Context()
socket = context.socket(zmq.REP)
socket.bind("tcp://*:5555")

elements = [True, False, True, False, False]
byte = bytearray(elements)

while True:
    message = socket.recv()

    time.sleep(1)

    socket.send(byte)

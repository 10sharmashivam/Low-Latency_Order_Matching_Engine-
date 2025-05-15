import socket
import time

def send_order(order_id, order_type, price, quantity):
    sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    sock.connect("/tmp/order_engine.sock")
    msg = f"ORDER:{order_id}:{order_type}:{price}:{quantity}\n"
    sock.send(msg.encode())
    response = sock.recv(1024).decode()
    print(f"Response: {response}")
    sock.close()

if __name__ == "__main__":
    for i in range(10):
        send_order(i, "BUY", 100.0 + i, 100)
        time.sleep(0.1)
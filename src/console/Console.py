import sys
from Setup import isValidDevice
from Device import *

device = None

def main():
    if not isValidDevice(sys.argv[1]):
        exit()
    
    print(f"Using device {sys.argv[1]}...")
    device = Device(sys.argv[1], 9600)

    while True:
        inp = input("Enter something: ")
        device.write(inp)
        response = device.read()
        print(f"Device has responded: {response}")


if __name__ == "__main__":
    main()

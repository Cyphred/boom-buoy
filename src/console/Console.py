import sys
from Setup import *
from Device import *

device = None

def main():
    if not deviceExists(sys.argv[1]) and not deviceIsValid(sys.argv[1]):
        print(f"{sys.argv[1]} is an invalid device! Aborting...")
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

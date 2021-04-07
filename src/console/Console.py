import sys
from Setup import isValidDevice
from Device import *
from Settings import *

device = None
settings = None

def main():
    # Verifies that a parameter has been passed
    if len(sys.argv) == 1:
        print("ERROR: No device specified. Aborting...")
        exit()

    if not isValidDevice(sys.argv[1]):
        exit()
    
    print(f"Connecting to device {sys.argv[1]}...", end=" ")
    device = Device(sys.argv[1], 9600) # Creates the device
    print("connected!")

    settings = Settings('settings.json')

if __name__ == "__main__":
    main()

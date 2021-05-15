import sys
from Setup import *
from Device import *
from Settings import *
from StationCommands import *

device = None
settings = None

def main():
    clear()

    # Splash info
    print("Arduino-based Dynamite Fishing Monitoring System")
    print("Version 1.0\n")

    # Verifies that a parameter has been passed
    if len(sys.argv) == 1:
        print("ERROR: No device specified. Aborting...")
        quit()

    if not devicePathExists(sys.argv[1]):
        exit()

    if not devicePathIsCOM(sys.argv[1]):
        exit();

    # Create instance of device
    print(f"Attempting connection with {sys.argv[1]}...")
    device = Device(sys.argv[1], 9600) # Creates the device
    if not authenticateWithDevice(device, 3000):
        exit()

    # Initialize device settings
    settings = Settings('settings.json')

    device.device.close()

def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

if __name__ == "__main__":
    main()

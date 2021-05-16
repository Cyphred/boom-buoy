import os.path
import serial.tools.list_ports
import time

# Checks if the device path exists
def devicePathExists(devicePath):
    print("Checking if device path is valid...", end="")
    if os.path.exists(devicePath):
        print("OK")
        return True
    else:
        print("FAILED")
        print(f"\nERROR: Device \"{devicePath}\" does not exist.")
        return False

# Checks if the device in the path is a valid COM device
def devicePathIsCOM(devicePath):
    print("Verifying COM device...", end="")
    ports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
    if devicePath in ports[0] or devicePath in ports[1]:
        print("OK")
        return True
    else:
        print("FAILED")
        print(f"\nERROR: \"{devicePath}\" is not a valid COM device.")
        return False

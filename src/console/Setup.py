import os.path
import serial.tools.list_ports

def isValidDevice(device):
    if not _deviceExists(device):
        print(f"ERROR: \"{device}\" does not exist.")
        return False

    if not _deviceIsCOM(device):
        print(f"ERROR: \"{device}\" is not a valid COM device.")
        return False

    return True

# Checks if the device exists
def _deviceExists(device):
    if os.path.exists(device):
        return True
    else:
        return False

# Checks if the device is a valid COM device
def _deviceIsCOM(device):
    ports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
    if not device in ports[0] and not device in ports[1]:
        return False
    return True

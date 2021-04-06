import os.path
import serial.tools.list_ports

# Checks if the device exists
def deviceExists(device):
    if os.path.exists(device):
        return True
    else:
        return False

# Checks if the device is a valid COM device
def deviceIsValid(device):
    ports = [tuple(p) for p in list(serial.tools.list_ports.comports())]
    if not device in ports[0] and not device in ports[1]:
        return False
    return True

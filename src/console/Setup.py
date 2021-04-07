import os.path
import serial.tools.list_ports
import Device
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

# Sends a magic byte to the device and checks if it sends
# the appropriate response.
def authenticateWithDevice(device, timeout):
    print("Authenticating...", end="")

    reply = None
    timeout /= 1000
    start = time.time()

    # Send connection requests to device until a response is received,
    # or until the allowed time expires.
    while not reply and (time.time() - start) < timeout:
        device.write('g')
        reply = device.read()

    # reply is empty if no response has been received
    if not reply:
        print("FAILED")
        print("ERROR: Device took to long to respond.")
        return False

    # if the magic byte is received
    if reply == 'g':
        print("OK")
        return True
    else:
        print("FAILED")
        print("ERROR: Device sent an invalid response. Are you sure you selected the correct device?")
        return False

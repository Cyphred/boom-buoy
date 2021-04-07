from Device import *
import time

def getPingTimeout(device):
    device.write(chr(9))
    timeout = int(device.waitForData())
    return timeout

# Queries the connection state between the buoy and the station
def getBuoyState(device):
    device.write(chr(10))
    state = int(device.waitForData())
    if state == 30:
        return "disconnected"
    elif state == 31:
        return "monitor"
    elif state == 32:
        return "stream"
    else:
        return "unknown"

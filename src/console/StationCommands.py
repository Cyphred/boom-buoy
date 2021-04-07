from Device import *
import time

# Sends a get request to the station and waits for a response
def requestAndWait(device, command):
    device.write(command)
    data = int(device.waitForData())
    return data

def getVarianceThreshold(device):
    return requestAndWait(device, chr(7))

def getMeasurementInterval(device):
    return requestAndWait(device, chr(8))

def getPingTimeout(device):
    return requestAndWait(device, chr(9))

# Queries the mode of communication between the buoy and the station
def getMode(device):
    state = requestAndWait(device, chr(10))
    if state == 30:
        return "disconnected"
    elif state == 31:
        return "monitor"
    elif state == 32:
        return "stream"
    else:
        return "unknown"

from Device import *
import time

def _setOperationalVariable(device, command, value):
    response = _requestAndWait(device, command)
    if response is chr(100):
        device.writeStream(value)
        response = None
    else:
        return False

    start = time.time()
    while not response and (time.time() - start) < 1000:
        response = device.read()

    if response is chr(100):
        return True
    else:
        return False

# Sends a get request to the station and waits for a response
def _requestAndWait(device, command):
    device.write(command)
    data = device.waitForData()
    return data

def setVarianceThreshold(device, value):
    return _setOperationalVariable(device, chr(3), value)

def setMeasurementInterval(device, value):
    return _setOperationalVariable(device, chr(4), value)

def setPingTimeout(device, value):
    return _setOperationalVariable(device, chr(5), value)

def setMode(device, value):
    return _setOperationalVariable(device, chr(6), value)

def getVarianceThreshold(device):
    data = _requestAndWait(device, chr(7))
    return int(data)

def getMeasurementInterval(device):
    data = _requestAndWait(device, chr(8))
    return int(data)

def getPingTimeout(device):
    data = _requestAndWait(device, chr(9))
    return int(data)

# Queries the mode of communication between the buoy and the station
def getMode(device):
    state = _requestAndWait(device, chr(10))
    print(f"state is {state}")
    if state == '0':
        return "disconnected"
    elif state == '1':
        return "monitor"
    elif state == '2':
        return "stream"
    else:
        return "unknown"

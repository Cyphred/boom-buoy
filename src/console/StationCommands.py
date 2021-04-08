import Console
from Device import *
import time

def station_settings_get():
    print("Fetching status info...")
    mode = getMode()
    interval = getMeasurementInterval()
    timeout = getPingTimeout()
    variance = getVarianceThreshold()
    print(f"Mode: {mode}")
    print(f"Measurement Interval: {interval}ms")
    print(f"Ping Timeout: {timeout}ms")
    print(f"Variance Threshold: {variance}%")

def station_settings_apply():
    print("Applying settings...")
    timeout = Console.settings.data['buoy_settings']['ping_timeout']
    mode = Console.settings.data['buoy_settings']['mode']
    variance = Console.settings.data['buoy_settings']['variance_threshold']
    interval = Console.settings.data['buoy_settings']['measurement_interval']

    print(f"  Setting ping timeout to {timeout}ms...", end="")
    if setPingTimeout(timeout):
        print("OK")
    else:
        print("FAILED")

    print(f"  Setting mode to {mode}...", end="")
    if setMode(mode):
        print("OK")
    else:
        print("FAILED")

    print(f"  Setting variance threshold to {variance}%...", end="")
    if setVarianceThreshold(variance):
        print("OK")
    else:
        print("FAILED")

    print(f"  Setting measurement interval to {interval}ms...", end="")
    if setMeasurementInterval(interval):
        print("OK")
    else:
        print("FAILED")

def station_settings_edit():
    print("edit settings")

def _setOperationalVariable(command, value):
    response = _requestAndWait(command)
    if response is chr(100):
        Console.device.writeStream(value)
        response = None
    else:
        return False

    start = time.time()
    while not response and (time.time() - start) < 1000:
        response = Console.device.read()

    if response is chr(100):
        return True
    else:
        return False

# Sends a get request to the station and waits for a response
def _requestAndWait(command):
    Console.device.write(command)
    data = Console.device.waitForData()
    return data

def setVarianceThreshold(value):
    return _setOperationalVariable(chr(3), value)

def setMeasurementInterval(value):
    return _setOperationalVariable(chr(4), value)

def setPingTimeout(value):
    return _setOperationalVariable(chr(5), value)

def setMode(value):
    return _setOperationalVariable(chr(6), value)

def getVarianceThreshold():
    data = _requestAndWait(chr(7))
    return int(data)

def getMeasurementInterval():
    data = _requestAndWait(chr(8))
    return int(data)

def getPingTimeout():
    data = _requestAndWait(chr(9))
    return int(data)

# Queries the mode of communication between the buoy and the station
def getMode():
    state = _requestAndWait(chr(10))
    if state == '0':
        return "disconnected"
    elif state == '1':
        return "monitor"
    elif state == '2':
        return "stream"
    else:
        return "unknown"


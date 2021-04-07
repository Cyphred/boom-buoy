from Device import *
import time

# Requests the station for a status report
def statusReport(device):
    device.waitForData()

def isBuoyConnected():
    device.write(chr(3))


import serial

class Device:
    device = None

    def __init__(self, devicePath, baudRate):
        self.devicePath = devicePath
        self.baudRate = baudRate
        self.device = serial.Serial(port=devicePath, baudrate=baudRate, timeout=.1)

    # Writes data over serial
    def write(self, data):
        print(f"You have entered: {data}")
        self.device.write(bytes(data, 'utf-8'))

    # Fetches data from serial
    def read(self):
        data = self.device.readline()
        return data.decode('utf-8') # Decode bytes object back into a string

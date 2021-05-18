import sys
from Common import *
from Device import *
import serial.tools.list_ports
import os.path

station = None
data = []

def main():
    if not hasEnoughParameters(sys.argv,2):
        print("Usage: Console.py <device path> <save data path>")
        exit()

    # Splash info
    clear()
    print("Arduino-based Dynamite Fishing Monitoring System")
    print("[ Noise Data Logger ]")
    print("Version 1.0\n")

    if not devicePathExists(sys.argv[1]):
        exit()

    if not devicePathIsCOM(sys.argv[1]):
        exit()

    if not connectDevice():
        exit()

    while True:
        try:
            bytes = station.device.readline();
            timestamp = getTimestamp()
            if bytes:
                bytes = bytes[:-2]
                decoded = bytes.decode()
                #decoded = decoded.rstrip(decoded[-1]) # Removes the last newline character

                # If the sent line starts with a number, log it and print.
                if bytes[0] >= 48 and bytes[0] <= 57:
                    decoded = int(decoded)
                    data.append([timestamp,decoded])
                    print(f"{data[len(data)-1]}")

                # If the sent line is just text, just print it out.
                else:
                    print(decoded)

        except:
            print("============================================================")
            #print(e)
            print("Interrupt received.")
            print("[ LOGGING SUMMARY ]")
            print(f"- Data Points: {len(data)}")

            if len(data) > 0:
                duration = data[len(data) - 1][0] - data[0][0]
                duration = round(duration, 3)
                print(f"- Duration: {duration}s")
                saveData(data, sys.argv[2])
            else:
                print("No data to save.")

            break

    disconnectDevice()
    input("Program complete. Press enter to quit.")

def devicePathExists(devicePath):
    print("Checking if device path is valid...", end="")
    if os.path.exists(devicePath):
        print("OK")
        return True
    else:
        print("FAILED")
        print(f"\nERROR: Device \"{devicePath}\" does not exist.")
        return False

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

def connectDevice():
    print(f"Attempting connection with {sys.argv[1]}...", end="")
    global station
    station = Device(sys.argv[1], 115200) # Creates the device
    station.device.flush()
    if station:
        print("OK")
        return True
    else:
        print("ERROR")
        return False

def disconnectDevice():
    print("Disconnecting device...",end="")
    station.device.close()
    print("OK")

if __name__ == "__main__":
    main()

import sys
from Setup import *
from Device import *
import time
import csv

station = None

def main():
    clear()

    # Splash info
    print("Arduino-based Dynamite Fishing Monitoring System")
    print("Version 1.0\n")

    # Verifies that a parameter has been passed
    if len(sys.argv) == 1:
        print("ERROR: No device specified. Aborting...")
        quit()

    if not devicePathExists(sys.argv[1]):
        exit()

    if not devicePathIsCOM(sys.argv[1]):
        exit()

    if not connectDevice():
        exit()

    while True:
        try:
            bytes = station.device.readline();
            timestamp = time.time()
            if bytes:
                decoded = bytes.decode()
                decoded = decoded.rstrip(decoded[-1])

                # If the sent line starts with a number
                if bytes[0] >= 48 and bytes[0] <= 57:
                    decoded = str(timestamp) + "," + decoded
                    with open("/mnt/data/test_data.csv","a") as f:
                        writer = csv.writer(f,delimiter=",")
                        writer.writerow([decoded])

                print(decoded)
        except:
            print("Keyboard Interrupt")
            break

    station.device.close()

def connectDevice():
    print(f"Attempting connection with {sys.argv[1]}...", end="")
    global station
    station = Device(sys.argv[1], 115200) # Creates the device
    if station:
        print("OK")
        return True
    else:
        print("ERROR")
        return False


def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

if __name__ == "__main__":
    main()

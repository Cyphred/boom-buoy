import sys
from Common import *

data = []
counter = 0

def main():
    if not hasEnoughParameters(sys.argv,1):
        print("Usage: BlastTimer.py <save data path>")
        exit()

    # Splash info
    clear()
    print("Arduino-based Dynamite Fishing Monitoring System")
    print("[ Blast Time Logger ]")
    print("Version 1.0\n")

    try:
        input("Press enter to start logging blast time data.")
        addPoint()

        input("Press enter to record blast time.")
        addPoint()

        input("Press enter to stop logging blast time data.")
        addPoint()
    except:
        print("Interrupt received")

    print("[ LOGGING SUMMARY ]")

    if len(data) > 0:
        duration = data[2][0] - data[0][0]
        duration = round(duration, 4)
        print(f"- Duration: {duration}s")

        blastTime = data[1][0] - data[0][0]
        blastTime = round(blastTime, 4)
        print(f"- Blast: {blastTime}")
        saveData(data, sys.argv[1])
    else:
        print("No data to save.")

    input("Program complete. Press enter to quit.")

def addPoint():
    global counter
    counter += 1
    data.append([getTimestamp(),counter])

if __name__ == "__main__":
    main()

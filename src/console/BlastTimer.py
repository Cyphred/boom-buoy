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

    input("Press enter to start logging blast time data.")
    addPoint()

    while True:
        try:
            clear()
            print(f"{len(data)} points recorded so far.")
            input("Press enter to record current time.")
            addPoint()

        except:
            clear()
            end = getTimestamp()
            #print(e)
            print("Interrupt received.")
            print("[ LOGGING SUMMARY ]")
            print(f"- Data Points: {counter}")

            if len(data) > 0:
                duration = end - data[0][0]
                duration = round(duration, 3)
                print(f"- Duration: {duration}s")
                saveData(data, sys.argv[1])
            else:
                print("No data to save.")

            break

    input("Program complete. Press enter to quit.")

def addPoint():
    global counter
    counter += 1
    data.append([getTimestamp(),counter])

if __name__ == "__main__":
    main()

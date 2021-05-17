import sys
import csv
import time

points = []
counter = 0

def main():
    # Splash info
    clear()
    print("Arduino-based Dynamite Fishing Monitoring System")
    print("[ Blast Time Logger ]")
    print("Version 1.0\n")

    if len(sys.argv) != 2:
        print("ERROR: Not enough arguments.")
        quit()

    input("Press enter to start logging blast time data.\nNOTE:This will also count as the official start of data logging. Noise level data taken before pressing enter will be pruned upon processing.")
    addPoint()

    while True:
        try:
            print(f"{points} points recorded.")
            input("Press enter to record current time.")
            addPoint()

        except:
            print("\nKeyboard Interrupt")
            roundTimestamps()
            saveData()
            break

# Adds a data point
def addPoint():
    global points
    global counter
    timestamp = time.time()
    counter+=1
    points.append([timestamp,counter])

# Saves data to file
def saveData():
    global points
    print(f"Saving data to {sys.argv[1]}...")
    with open(sys.argv[1], 'w') as f:
        write = csv.writer(f)
        write.writerows(points)
        print(f"Saved {len(points)} data points.")

def roundTimestamps():
    print("Rounding timestamps to 3 decimal places...")
    global points
    for p in points:
        p[0] = round(p[0], 3)

if __name__ == "__main__":
    main()

import csv
import os.path
import time

def hasEnoughParameters(params,num):
    if len(params) != num + 1:
        print(f"ERROR: Not enough arguments. (Expected {num}, got {len(params) - 1}.)")
        return False
    return True

def clear():
    os.system('cls' if os.name == 'nt' else 'clear')

def saveData(data, filePath):
    print(f"Saving data to {filePath}...")
    with open(filePath, 'w') as f:
        write = csv.writer(f)
        write.writerows(data)
        print(f"Saved {len(data)} data points to \"{filePath}\".")

def getTimestamp():
    return time.time()

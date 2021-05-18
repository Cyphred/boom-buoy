import matplotlib.pyplot as plt
import numpy as np
import csv
import sys
import os.path

if not os.path.exists(sys.argv[1]):
    print(f"ERROR: '{sys.argv[1]}' does not exist!")
    exit()

noiseLevel = []
noiseTime = []
blastTime = []
dataFile = sys.argv[1]

# Import data
print("Importing data...",end="")

with open(dataFile,'r') as data:
    reader = csv.reader(data, delimiter=',')
    for row in reader:
        if int(row[0]) == 0:
            noiseTime.append(float(row[1]))
            noiseLevel.append(int(row[2]))
        elif int(row[0]) == 1:
            blastTime.append(float(row[1]))

print("Done")

print("Imported:")
print(f"Noise Level Data Points: {len(noiseLevel)}")
print(f"Blast Time Data Points: {len(blastTime)}")

plt.plot(noiseTime, noiseLevel, linewidth='1')

for time in blastTime:
    plt.axvline(x=time,color="red")

plt.xlabel("Time")
plt.ylabel("Noise Level")
plt.title("Buoy Data")
plt.grid(color="#c7c7c7", linestyle='--', linewidth=0.5)
plt.show()

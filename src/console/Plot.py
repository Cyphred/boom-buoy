import matplotlib.pyplot as plt
import numpy as np
import csv
import sys
import os.path

if len(sys.argv) != 2:
    print("ERROR: Not enough arguments.")

noiseLevel = []
noiseTime = []
dataFile = sys.argv[1]
graphTitle = sys.argv[1]

# Check if save path exists
if not os.path.exists(sys.argv[1]):
    print(f"ERROR: '{sys.argv[1]}' does not exist!")
    exit()

# Import data
print("Importing data...",end="")

with open(dataFile,'r') as data:
    reader = csv.reader(data, delimiter=',')
    for row in reader:
        noiseTime.append(float(row[0]))
        noiseLevel.append(int(row[1]))

print("Done")

print("Imported:")
print(f"Noise Level Data Points: {len(noiseLevel)}")

print("Plotting graphs...")

# Plot raw noise data
plt.plot(noiseTime, noiseLevel, color="#c7c7c7", linewidth="0.5")

# Compute standard deviation in sets of 10
deviation = []
deviationTime = []
temp_deviation = []

for i in range(len(noiseLevel)):
    temp_deviation.append(noiseLevel[i])
    if len(temp_deviation) == 10:
        deviation.append(sum(temp_deviation) / 10)
        temp_deviation = []
        deviationTime.append(noiseTime[i])

# Plot standard deviation
plt.plot(deviationTime, deviation, color="blue")

# Plot line for actual blast time
plt.axvline(x=0,color="red")

plt.xlabel("Time in seconds relative to blast")
plt.ylabel("Noise Level")
plt.title(graphTitle)
plt.grid(color="#c7c7c7", linestyle='--', linewidth=0.5)
plt.show()

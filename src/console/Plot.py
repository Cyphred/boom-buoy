import matplotlib.pyplot as plt
import numpy as np
import csv
import sys
import os.path

if len(sys.argv) != 4:
    print("ERROR: Not enough arguments.")

noiseLevel = []
noiseTime = []
dataFile = sys.argv[1]
graphTitle = sys.argv[1]

# Settings
deviationSetSize = int(sys.argv[2])
diffThreshold = int(sys.argv[3])

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
    if len(temp_deviation) == deviationSetSize:
        deviation.append(sum(temp_deviation) / deviationSetSize)
        temp_deviation = []
        deviationTime.append(noiseTime[i])

# Plot standard deviation
plt.plot(deviationTime, deviation, color="blue", linewidth="0.8")

# Traverse through each standard deviation and check its neighbors for potential spikes
spikes = []
for i in range(2, len(deviation)):
    ave = (deviation[i-2] + deviation[i-1]) / 2
    diff = deviation[i] - ave
    diff = (diff / ave) * 100
    if diff > diffThreshold:
        plt.axvline(x=deviationTime[i], color="green", linewidth="1", linestyle="dashed")

# Plot line for actual blast time
plt.axvline(x=0, color="red", linewidth="1")

plt.xlabel("Time in seconds relative to blast")
plt.ylabel("Noise Level")
plt.title(graphTitle)
plt.grid(color="#c7c7c7", linestyle='--', linewidth=0.5)
plt.show()

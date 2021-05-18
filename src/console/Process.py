import sys
import csv
from Common import *

if not hasEnoughParameters(sys.argv, 3):
    print("ERROR: Not enough arguments.")
    exit()

raw_noise_data = []
raw_blast_time = []
pathToRawNoiseData = sys.argv[1]
pathToRawBlastTimeData = sys.argv[2]
outputFile = sys.argv[3]

# Read noise data
print("Importing noise data...",end="")

with open(pathToRawNoiseData,'r') as data:
    reader = csv.reader(data)
    for row in reader:
        timestamp = float(row[0])
        noise = int(row[1])
        raw_noise_data.append([timestamp, noise])

print(f"Done. Loaded {len(raw_noise_data)} data points.")

# Read blast time data
print("Importing blast time data...",end="")

with open(pathToRawBlastTimeData,'r') as data:
    reader = csv.reader(data, delimiter=',')
    for row in reader:
        timestamp = float(row[0])
        count = int(row[1])
        raw_blast_time.append([timestamp, count])

print(f"Done. Loaded {len(raw_blast_time)} data points.")

print("Adjusting timestamps...")

# Save and remove the first blast time data point, because its only purpose is a marker for the start point.
startTime = raw_blast_time[0][0]
raw_blast_time = raw_blast_time[1:] 

# Adjust timestamps relative to start time
for row in raw_blast_time:
    row[0] = round(row[0], 4)
    row[0] = row[0] - startTime

for row in raw_noise_data:
    row[0] = row[0] - startTime
    row[0] = round(row[0], 4)

print("Trimming datapoints earlier than the start point...")

# Trim all data points with a negative timestamp in noise data
# Uses first column to identify it as noise data
processed_data = []
for row in raw_noise_data:
    if row[0] >= 0:
        processed_noise_data.append([0,row[0],row[1]])

# Store blast time data
# Uses second column to identify it as blast time data
for row in raw_blast_time:
    processed_data.append([1,row[0],row[1]])

saveData(processed_data, outputFile)

input("Data processing complete. Press enter to quit.")

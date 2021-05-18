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

# Take note of data start and end times, as well as acutal blast time
startTime = raw_blast_time[0][0]
acutal_blast_time = raw_blast_time[1][0]
endTime = raw_blast_time[2][0]

print("Trimming datapoints out of range...")

# Exclude all data points outside the range of the start and end times
processed_data = []
for row in raw_noise_data:
    if row[0] >= startTime and row[0] <= endTime:
        row[0] = round(row[0],4)
        processed_data.append([row[0],row[1]])

print("Adjusting timestamps...")

# Adjust timestamps relative to actual blast time
for row in processed_data:
    row[0] = row[0] - acutal_blast_time

saveData(processed_data, outputFile)

input("Data processing complete. Press enter to quit.")

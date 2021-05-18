import matplotlib.pyplot as plt
import numpy as np
import csv
import sys
import os.path

# Compute standard deviation in sets of 10
def standardDeviation(data, set_size):
    deviation = []
    temp_deviation = []

    for i in range(len(data)):
        temp_deviation.append(data[i][1])
        if len(temp_deviation) == set_size:
            result = sum(temp_deviation) / set_size
            deviation.append([data[i][0],result])
            temp_deviation = []

    return deviation

def mean(data, offset):
    mean = []
    current_set = []

    for a in range(len(data)):
        for b in range(offset * -1, offset + 1):
            try:
                current_set.append(data[a + b][1])
            except:
                pass

        result = sum(current_set) / len(current_set)
        mean.append([data[a][0],result])

    return mean

def main():
    if len(sys.argv) < 2:
        print("ERROR: Not enough arguments.")

    data_noise = []
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
            data_noise.append([float(row[0]), int(row[1])])

    print(f"Imported {len(data_noise)} data points.")

    print("Plotting graphs...")

    # Standard deviation of raw noise data
    #data_deviation = standardDeviation(data_noise, 3)
    #x,y = map(list, zip(*data_deviation))
    #plt.plot(x, y, color="blue", linewidth="0.8")

    # Mean of raw noise data
    data_mean = mean(data_noise, 10)

    # Detect potential blasts
    variance_threshold = 10
    if len(sys.argv) > 2:
        variance_threshold = int(sys.argv[2])
    for i in range(len(data_noise)):
        variance = ((data_noise[i][1] - data_mean[i][1]) / data_mean[i][1]) * 100
        if variance >= variance_threshold:
            plt.axvline(x=data_noise[i][0], color="#f72cba", linewidth="1", linestyle="dotted")

    # Plot raw noise data
    x,y = map(list, zip(*data_noise))
    plt.plot(x, y, color="#2cbaf7", linewidth="1")
    x,y = map(list, zip(*data_mean))
    plt.plot(x, y, color="#f72cba", linewidth="1")

    # Plot line for actual blast time
    plt.axvline(x=0, color="red", linewidth="1")

    plt.xlabel("Time in seconds relative to blast")
    plt.ylabel("Noise Level")
    plt.title(graphTitle)
    plt.grid(color="#c7c7c7", linestyle='--', linewidth=0.5)
    plt.show()

if __name__ == "__main__":
    main()

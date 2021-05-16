import sys
import csv
import time

if len(sys.argv) != 2:
    print("ERROR: Not enough arguments.")
    quit()

points = []
counter = 0

while True:
    try:
        print(points)
        input("Press enter to record current time.")
        counter+=1
        points.append([counter,time.time()])

    except:
        print("\nKeyboard Interrupt")
        break


print(f"Saving data to {sys.argv[1]}...")
fields = ['Count','Timestamp']
with open(sys.argv[1], 'w') as f:
    write = csv.writer(f)
    write.writerow(fields)
    write.writerows(points)
    print(f"Saved {len(points)} data points.")

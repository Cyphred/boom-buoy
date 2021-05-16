# !/bin/sh

[ -z $1 ] && echo "ERROR: Device not specified." && exit 1

echo "Starting test..."
timestamp=$(date +%Y-%m-%d-%H%M%S)
$TERMINAL python Console.py $1 "/mnt/data/buoy-data/sensors-$timestamp.csv" &
$TERMINAL python DropTimer.py "/mnt/data/buoy-data/drop-$timestamp.csv" &

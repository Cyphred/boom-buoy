# !/bin/sh

log_location="/mnt/data/buoy-data"
timestamp=$(date +%Y-%m-%d-%H%M%S)

# $1 is the device that will be passed as a parameter to Console.py
# This should be the station.
[ -z $1 ] && echo "[ERROR] Device not specified." && exit 1
if ! ls $1; then
	echo "'$1' is not a valid device."
	exit 1
fi

# Check if the data directory exists
if [ ! -d "$log_location" ]; then
	echo "[ERROR] \"$log_location\" is not a valid directory."
	exit 1
fi

# Create a new directory for a data set
if [ -d "$log_location/$timestamp" ]; then
	echo "[ERROR] A data set with the current timestamp $timestamp already exists."
	exit 1
else
	if mkdir $log_location/$timestamp/; then
		echo "Created directory \"$log_location/$timestamp/\""
	else
		echo "Could not create \"$log_location/$timestamp/\""
		exit 1
	fi
fi

echo "Starting test. DO NOT CLOSE THIS TERMINAL..."

echo "Running Console.py..."
$TERMINAL python Console.py $1 "$log_location/$timestamp/raw-noise-$timestamp.csv" &

echo "Running BlastTimer.py..."
$TERMINAL python BlastTimer.py "$log_location/$timestamp/raw-blast-$timestamp.csv" &

echo "Data logging scripts are now running."
echo "\nImportant Notes:"
echo "[+] DO NOT CLOSE THIS TERMINAL."
echo "[+] Log files will be saved to \"$log_location/$timestamp/\"."
echo "[+] After data logging is complete, data will be pre-processed before generating a plot."

while true; do
	printf "Enter YES in uppercase letters once data logging is complete: "
	read input
	[ "$input" == "YES" ] && break
done

# Process the logged data
python Process.py "$log_location/$timestamp/raw-noise-$timestamp.csv" "$log_location/$timestamp/raw-blast-$timestamp.csv" "$log_location/$timestamp/processed-$timestamp.csv"

# Plot the processed data
while true; do
	printf "Deviation set size: "
	read dss
	printf "Difference threshold: "
	read dt
	python Plot.py "$log_location/$timestamp/processed-$timestamp.csv" $dss $dt
done

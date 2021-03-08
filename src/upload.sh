# !/bin/sh

[ -z "$1" ] && echo "Please specify a board to upload to" && exit 1
arduino-cli upload -b arduino:avr:nano:cpu=atmega328old -v -p $1

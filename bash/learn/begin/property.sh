#!/bin/bash

# This script gives information about a file

FILENAME="$1"

if [ ! $# == 1 ]; then
	echo "Usage: $0 file_name";
	exit
fi

echo "Properties for $FILENAME:"

if [ -f $FILENAME ]; then
	echo "Size is $(du -h $FILENAME | awk '{ print $1}') \
or $(du -b $FILENAME | awk '{ print $1}') bytes"
	echo "Type is $(file $FILENAME | cut -d":" -f2 -)"
	echo "Inode number is $(ls -i $FILENAME | cut -d" " -f1 -)"
	echo "$(df -h $FILENAME | grep -v Mounted | awk '{ print "On",$1", \
which is mounted ad the",$6,"partition"}')"
else
	echo "File does not exist"
fi

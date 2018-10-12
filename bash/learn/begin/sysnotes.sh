#!/bin/bash

# This script makes an index of important config files, puts them
# together in a backup file and allows for adding comment for each file.

CONFIG=/var/tmp/sysconfig.out

echo "You want to read sysconf.out file? y/n"
read answer
if [ $answer = "y" ]; then
	cat $CONFIG
fi

echo "Continue script? y/n"
read answer
if [ $answer = "n" ]; then
   exit 1
fi

rm "$CONFIG" 2>dev/null
rm $CONFIG

echo "Output will be saved in $CONFIG"

# Create fd 7 with same target as fd 0 - save stdin value
exec 7<&0

# Update fd 0 to target file /etc/passwd
exec < /etc/passwd

# Read the first line of /etc/passwd
read rootpasswd

echo "Saving root account info"
echo "Your root account info: " >> "$CONFIG"
echo $rootpasswd >> "$CONFIG"

# Update fd 0 to target fd 7 target (old fd 0 target), delete fd 7
exec 0<&7 7<&-

echo -n "Enter comment of [ENTER] for no comment: "
read comment; echo $comment >> "$CONFIG"

echo "Saving hosts information"

# First prepare a hosts file not containing any comments
TEMP="/var/tmp/hosts.tmp"
cat /etc/hosts | grep -v "^#" > "$TEMP"

exec 7<&0
exec < "$TEMP"

read ip1 name1 alias1
read ip2 name2 alias2

echo "Your local host configuration: " >> "$CONFIG"

echo "$ip1 $name1 $alias1" >> "$CONFIG"
echo "$ip2 $name2 $alias2" >> "$CONFIG"

exec 0<&7 7<&-

echo -n "Enter comment or [ENTER] for no comment: "
read comment; echo $comment >> "$CONFIG"
rm "$TEMP"

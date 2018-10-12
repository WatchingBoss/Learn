#!/bin/bash
clear
echo "This is some system information"

echo "Hello, $USER"
echo

echo "Today's data is `date`, this is week `date +"%V"`."
echo

echo "These users are currently connected:"
w | cut -d " " -f 1 - | grep -v USER | sort -u
echo

echo "This is `uname -s` running on a `uname -m` processor."
echo

echo "This is the uptime information:"
set -x
uptime
set +x
echo

printf "Bey\n\n"


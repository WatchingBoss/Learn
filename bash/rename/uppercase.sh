#!/bin/bash
# Rename to uppercase files' name in current directory

LIST="$( ls )"

for i in $LIST; do
	NEWNAME=$( echo "$i" | tr '[:lower:]' '[:upper:]' )

# We can use awk for this
#	NEWNAME=$( echo "$i" | awk '{print tolower($0)}')

	if [ $i == $NEWNAME ]; then
		echo "$i" "$NEWNAME" 'are same'
		continue
	fi

   	mv "$i" "$NEWNAME"
done

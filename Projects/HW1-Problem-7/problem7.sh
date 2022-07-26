#! /bin/bash

counter=0;
for FILE in "$@"
do
	x=$(wc -l <$FILE);
	echo "$FILE has $x lines";
	echo "Current Total = $counter + $x";
	counter=$(($counter+$x));
	echo "Current Total = $counter";
done
echo "Total Lines = $counter";
echo "Total Files = $#";

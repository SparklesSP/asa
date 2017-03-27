#!/bin/bash

# Read type as 1st argument
EXEC=./gen_p1
FILES=./tests
TYPE=$1
ARCHES=5

if [[ $# -eq 0 ]] || [[ $TYPE -gt 2 ]]; then
	printf "Invalid test type provided\n"
	exit 1
fi

for v in `seq 10000 10000 100000`; do
	a=$(expr $v \* $ARCHES)
	printf "Generating for $v vertices and approximately $(expr $v + $a) arches, of type $TYPE\n"
	$EXEC $v $a $TYPE > temp.in
	a=$(cat temp.in | sed -n 1p | awk '{ printf( "%d", $2) }')
	mv temp.in $FILES/$v\_$a\_$TYPE.in
done

exit 0

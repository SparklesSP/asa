#!/bin/bash

rm -f mooshak/*.myout
rm -f mooshak/*.diff
for i in {1..16} 
do
  /usr/bin/time -f "%e" timeout 9 ./projeto < mooshak/$i > mooshak/$i.myout 2>tempo.time
  timmer=$(head -n 1 tempo.time)
  DIFF=$(diff "mooshak/${i}.myout" "mooshak/${i}out") 
  if [ "$DIFF" == "" ]; then
    echo "Test $i passed!!! in ${timmer}s"
  else
    echo "Test $i failed!!! in ${timmer}s"
  fi
done

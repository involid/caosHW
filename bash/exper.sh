#!/bin/bash

#a=("1" "2" "3")
#for (( i=0; i<3; i+=2 ))
#do
#    echo ${a[i]}
#done

if [[ 1 != 2 ]];
then
    echo ololo
fi

a=5
a=$(echo "$a/2.5" | bc -l)
#echo $a
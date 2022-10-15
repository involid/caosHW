#!/bin/bash

matrix=$(cat $1)

size=0
nums=()
for line in $matrix
do
    size=$(($size+1))
    IFS=','
    for num in $line
    do
        nums[${#nums[@]}]=$num
    done
done

length=$(($size+1))

for (( i=0; i<$size; i++ ))
do
    pos=$(($i+$i*$length))
    x=${nums[$pos]}
    for (( j=0; j<$size; j++))
    do
        if [ $i -eq $j ];
        then
            pos1=$(($i*$length))
            pos2=$(($pos1+$length))
            for ((t=$pos1; t<$pos2; t++))
            do
                nums[$t]=$(echo "${nums[$t]}/$x" | bc -l)
            done
            x=1
        else
            pos=$(($i+$j*$length))
            y=${nums[$pos]}
            y=$(echo "$y/$x" | bc -l)
            pos1=$(($i*$length))
            pos2=$(($j*$length))
            for ((t=0; t<$length; t++))
            do
                a=${nums[(($pos1+$t))]}
                a=$(echo "$a*$y" | bc -l)
                b=${nums[(($pos2+$t))]}
                c=`echo "($b)-($a)" | bc -l`
                nums[(($pos2+$t))]=$c
            done
        fi
    done
done

for((i=0; i<$size; i++))
do
    echo ${nums[(($i*$length+$size))]}
done

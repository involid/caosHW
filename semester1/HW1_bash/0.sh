#!/bin/bash

while read function
do
    IFS=":"
    result="---"
    for path in $MANPATH
    do
        file=$path/man3/$function.3
        if [ -f "$file" ];
        then
            result=$(cat $file | sed -e "/#include/q;d" | sed -e "s/^.*#include <\(.*\)>/\1/")
            break
        fi

        file=$file.gz
        if [ -f "$file" ]
        then
            result=$(gunzip -c $file | sed -e "/#include/q;d" | sed -e "s/^.*#include <\(.*\)>/\1/")
            break
        fi
    done
    echo $result
done
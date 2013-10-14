#!/bin/bash

ans="AC"

for dir in ../problems/$1/cases/*; do
    timeout 3s ./$1 < ${dir}/$1.in > ../$1.temp 2>/dev/null
    if [ $? -eq 124 ]; then
        ans="TLE"
        break
    fi
    
    timeout 3s ./$1 < ${dir}/$1.in > ../$1.temp 2>/dev/null
    if [ $? -ne 0 ]; then
        ans="RTE"
    fi
    
    echo ${dir}
    diff ../$1.temp ${dir}/$1.out > /dev/null
    diff ../$1.temp ${dir}/$1.out
    if [ $? -eq 1 ]; then
        ans="WA"
        #break
    fi
done

rm ../$1.temp

#sleep $[ ( $RANDOM % 120 )  + 120 ]s

echo ${ans}

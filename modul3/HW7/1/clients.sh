#!/bin/bash

IP=$1
PORT=$2
SERVER_PID=$3

gcc clients/A.c -o clients/A
gcc clients/A_not_write.c -o clients/A_not_write
gcc clients/B.c -o clients/B
gcc clients/C.c -o clients/C
gcc clients/D.c -o clients/D

./clients/A $IP $PORT > output/A.txt &
./clients/A_not_write $IP $PORT > output/A_not_write.txt &
./clients/B $IP $PORT > output/B.txt &
./clients/C $IP $PORT > output/C.txt &
./clients/D $IP $PORT > output/D.txt &

sleep 9
kill $SERVER_PID

rm clients/A
rm clients/A_not_write
rm clients/B
rm clients/C
rm clients/D

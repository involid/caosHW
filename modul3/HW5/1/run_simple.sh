#!/bin/bash

gcc http_server_2.c -o http_server
IP=127.0.0.1
PORT=1337
DIR_PATH=$(pwd)/clients

./http_server $PORT $DIR_PATH > /dev/null &
SERVER_PID=$!

gcc sigint.c -o sigint
./sigint $SERVER_PID
rm sigint

rm http_server

#!/bin/bash

gcc http_server_1.c -o http_server
IP=127.0.0.1
PORT=1337
DIR_PATH=$(pwd)/input

./http_server $PORT $DIR_PATH > /dev/null &
SERVER_PID=$!

chmod +x clients.sh
./clients.sh $IP $PORT
chmod -x clients.sh

gcc sigterm.c -o sigterm
./sigterm $SERVER_PID
rm sigterm

rm http_server

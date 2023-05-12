#!/bin/bash

gcc watch_exit_or_signal.c -o watch_exit_or_signal

gcc epoll_read_write_socket.c -o http_server
IP=127.0.0.1
PORT=1337

./watch_exit_or_signal http_server $PORT \
    1> output_debug/server_stdout.txt \
    2> output_debug/server_stderr.txt &
sleep 1
SERVER_PID=$(cat pid_process.txt)
rm pid_process.txt

chmod +x clients.sh
./clients.sh $IP $PORT $SERVER_PID
chmod -x clients.sh

ps -a > output_debug/processes_list.txt

rm http_server
rm watch_exit_or_signal


special_color_symbol=$(printf '\033')
red_color_format_string="s,.*,${special_color_symbol}[1;31m&${special_color_symbol}[0m,"
green_color_format_string="s,.*,${special_color_symbol}[1;32m&${special_color_symbol}[0m,"

diff output_expected/A.txt output/A.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "File A.txt is correct" | sed $green_color_format_string
else
    echo "File A.txt is not correct" | sed $red_color_format_string
    echo "Differences of expected and real output:"
    diff output_expected/A.txt output/A.txt | colordiff
fi

diff output_expected/A_not_write.txt output/A_not_write.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "File A_not_write.txt is correct" | sed $green_color_format_string
else
    echo "File A_not_write.txt is not correct" | sed $red_color_format_string
    echo "Differences of expected and real output:"
    diff output_expected/A_not_write.txt output/A_not_write.txt | colordiff
fi

diff output_expected/B.txt output/B.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "File B.txt is correct" | sed $green_color_format_string
else
    echo "File B.txt is not correct" | sed $red_color_format_string
    echo "Differences of expected and real output:"
    diff output_expected/B.txt output/B.txt | colordiff
fi

diff output_expected/C.txt output/C.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "File C.txt is correct" | sed $green_color_format_string
else
    echo "File C.txt is not correct" | sed $red_color_format_string
    echo "Differences of expected and real output:"
    diff output_expected/C.txt output/C.txt | colordiff
fi

diff output_expected/D.txt output/D.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "File D.txt is correct" | sed $green_color_format_string
else
    echo "File D.txt is not correct" | sed $red_color_format_string
    echo "Differences of expected and real output:"
    diff output_expected/D.txt output/D.txt | colordiff
fi

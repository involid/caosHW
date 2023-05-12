#!/bin/bash

chmod +x make_all_libs.sh
./make_all_libs.sh
chmod -x make_all_libs.sh

g++ interfaces.cpp main.cpp -ldl -o main
export CLASSPATH=class_sources
./main > real_output.txt
rm main


special_color_symbol=$(printf '\033')
red_color_format_string="s,.*,${special_color_symbol}[1;31m&${special_color_symbol}[0m,"
green_color_format_string="s,.*,${special_color_symbol}[1;32m&${special_color_symbol}[0m,"

diff expected_output.txt real_output.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "Test is passed" | sed $green_color_format_string
else
    echo "Test is failed" | sed $red_color_format_string
    echo "You can check differences of files expected_output.txt and real_output.txt"
fi

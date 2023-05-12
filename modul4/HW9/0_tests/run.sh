#!/bin/bash

PROGRAM_FILE=$1

cat random_string.txt | openssl dgst -sha512 -hex | sed 's/(stdin)= /0x/' > Expected_output.txt

gcc $PROGRAM_FILE -lcrypto -o dgst_sha512
cat random_string.txt | ./dgst_sha512 > Real_output.txt
rm dgst_sha512

special_color_symbol=$(printf '\033')
red_color_format_string="s,.*,${special_color_symbol}[1;31m&${special_color_symbol}[0m,"
green_color_format_string="s,.*,${special_color_symbol}[1;32m&${special_color_symbol}[0m,"

diff Expected_output.txt Real_output.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "Test is passed" | sed $green_color_format_string
else
    echo "Test is failed" | sed $red_color_format_string
    echo "You can check differences of files Expected_output.txt and Real_output.txt"
fi

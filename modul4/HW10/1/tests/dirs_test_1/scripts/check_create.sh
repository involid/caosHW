#!/bin/bash

mkdir dirs_test_1/real_output

cd mnt_1
ls -R > ../dirs_test_1/real_output/output_1_dirs.txt
find -type f | sort | xargs cat > ../dirs_test_1/real_output/output_2_files.txt

cd ..
cd dirs_test_1


special_color_symbol=$(printf '\033')
red_color_format_string="s,.*,${special_color_symbol}[1;31m&${special_color_symbol}[0m,"
green_color_format_string="s,.*,${special_color_symbol}[1;32m&${special_color_symbol}[0m,"

diff expected_output/output_1_dirs.txt real_output/output_1_dirs.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "Test 1: directories is correct" | sed $green_color_format_string
else
    echo "Test 1: directories is not correct" | sed $red_color_format_string
fi

diff expected_output/output_2_files.txt real_output/output_2_files.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "Test 1: files is correct" | sed $green_color_format_string
else
    echo "Test 1: files is not correct" | sed $red_color_format_string
fi

#!/bin/bash

chmod +x encrypt_sh.sh
chmod +x decrypt_sh.sh
chmod +x encrypt_c.sh
chmod +x decrypt_c.sh


./encrypt_sh.sh
# ./encrypt_c.sh

# ./decrypt_sh.sh
./decrypt_c.sh


special_color_symbol=$(printf '\033')
red_color_format_string="s,.*,${special_color_symbol}[1;31m&${special_color_symbol}[0m,"
green_color_format_string="s,.*,${special_color_symbol}[1;32m&${special_color_symbol}[0m,"

diff text.txt text_decrypt.txt > /dev/null
DIFFER=$?
if (($DIFFER == 0))
then
    echo "Test is passed" | sed $green_color_format_string
else
    echo "Test is failed" | sed $red_color_format_string
    echo "You can check differences of files text.txt and text_decrypt.txt"
fi

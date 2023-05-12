#!/bin/bash

# Delete test 2 output

chmod +x dirs_test_2/scripts/check_clean.sh
./dirs_test_2/scripts/check_clean.sh
chmod -x dirs_test_2/scripts/check_clean.sh

# Unmount file system

umount ./mnt_2
rm -R mnt_2

# Delete tmp files for test 2

chmod +x dirs_test_2/scripts/dirs_clean.sh
./dirs_test_2/scripts/dirs_clean.sh
chmod -x dirs_test_2/scripts/dirs_clean.sh

# Delete output of cmake and make

rm cmake_make_output_2.txt

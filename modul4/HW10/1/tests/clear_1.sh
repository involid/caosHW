#!/bin/bash

# Delete test 1 output

chmod +x dirs_test_1/scripts/check_clean.sh
./dirs_test_1/scripts/check_clean.sh
chmod -x dirs_test_1/scripts/check_clean.sh

# Unmount file system

umount ./mnt_1
rm -R mnt_1

# Delete tmp files for test 1

chmod +x dirs_test_1/scripts/dirs_clean.sh
./dirs_test_1/scripts/dirs_clean.sh
chmod -x dirs_test_1/scripts/dirs_clean.sh

# Delete output of cmake and make

rm cmake_make_output_1.txt

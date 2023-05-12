#!/bin/bash

# Prepare the executable file

mkdir build
cd build
cmake .. > ../cmake_make_output_1.txt
make >> ../cmake_make_output_1.txt

cp mergefs ../mergefs
cd ..
rm -R build

# Prepare test 1

chmod +x dirs_test_1/scripts/dirs_create.sh
./dirs_test_1/scripts/dirs_create.sh
chmod -x dirs_test_1/scripts/dirs_create.sh

# Mount file system for test 1

mkdir mnt_1
./mergefs ./mnt_1 --src dirs_test_1/dirs/A:dirs_test_1/dirs/B:dirs_test_1/dirs/C

# Check file system for test 1

chmod +x dirs_test_1/scripts/check_create.sh
./dirs_test_1/scripts/check_create.sh
chmod -x dirs_test_1/scripts/check_create.sh

# Delete the executable file

rm mergefs

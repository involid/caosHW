#!/bin/bash

# Prepare the executable file

mkdir build
cd build
cmake .. > ../cmake_make_output_2.txt
make >> ../cmake_make_output_2.txt

cp mergefs ../mergefs
cd ..
rm -R build

# Prepare test 2

chmod +x dirs_test_2/scripts/dirs_create.sh
./dirs_test_2/scripts/dirs_create.sh
chmod -x dirs_test_2/scripts/dirs_create.sh

# Mount file system for test 2

mkdir mnt_2
./mergefs ./mnt_2 --src dirs_test_2/dirs/A:dirs_test_2/dirs/B:dirs_test_2/dirs/A/A:dirs_test_2/dirs/B/A

# Check file system for test 2

chmod +x dirs_test_2/scripts/check_create.sh
./dirs_test_2/scripts/check_create.sh
chmod -x dirs_test_2/scripts/check_create.sh

# Delete the executable file

rm mergefs

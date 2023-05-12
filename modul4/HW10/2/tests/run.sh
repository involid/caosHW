#!/bin/bash

mkdir build
cd build
cmake .. > ../cmake_make_output.txt
make >> ../cmake_make_output.txt

cp unzipfs ../unzipfs
cd ..
rm -R build

mkdir mnt
./unzipfs ./mnt --src files.zip

rm unzipfs

chmod +x check.sh
./check.sh
chmod -x check.sh

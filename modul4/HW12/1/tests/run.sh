#!/bin/bash

mkdir build
cd build
cmake .. > ../cmake_and_make_output.txt
make >> ../cmake_and_make_output.txt

cp primes.so ..
cd ..
rm -R build

python3 check.py

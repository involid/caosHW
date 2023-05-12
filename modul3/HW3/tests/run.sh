#!/bin/bash

chmod +x make.sh
chmod +x clear.sh

export PATH=$PATH:$(pwd)/CAOS_test

./make.sh
gcc connect_2_processes.c -o connect_2_processes

echo "Expected output:"
printf "Hello from program B
Hello from program A
abra
shvabra
cadabra
foo
bar
dfsihjdsfh
Goodbye from program A
Goodbye from program B
"

echo

echo "Real output:"
cat CAOS_test/text.txt | ./connect_2_processes CAOS_test_A CAOS_test_B

rm connect_2_processes
./clear.sh

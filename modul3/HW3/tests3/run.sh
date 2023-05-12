#!/bin/bash

chmod +x make.sh
chmod +x clear.sh

export PATH=$PATH:$(pwd)/CAOS_test

./make.sh
gcc connect_n_processes.c -o connect_n_processes

echo "Expected output:"
printf "Hello from program E
Hello from program D
Hello from program C
Hello from program B
Hello from program A
abra
shvabra
cadabra
foo
bar
dfsihjdsfh
Goodbye from program A
Goodbye from program B
Goodbye from program C
Goodbye from program D
Goodbye from program E
"

echo

echo "Real output:"
cat CAOS_test/text.txt | ./connect_n_processes CAOS_test_A CAOS_test_B CAOS_test_C CAOS_test_D CAOS_test_E

rm connect_n_processes
./clear.sh

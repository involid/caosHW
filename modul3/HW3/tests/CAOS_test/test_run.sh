#!/bin/bash

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
cat text.txt | ./CAOS_test_A | ./CAOS_test_B

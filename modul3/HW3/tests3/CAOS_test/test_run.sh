#!/bin/bash

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
cat text.txt | ./CAOS_test_A | ./CAOS_test_B | ./CAOS_test_C | ./CAOS_test_D | ./CAOS_test_E

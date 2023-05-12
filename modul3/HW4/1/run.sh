#!/bin/bash

gcc do_actions.c -o do_actions
gcc test.c -o test

echo "-10" | ./test do_actions

rm test
rm do_actions

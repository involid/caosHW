#!/bin/bash

gcc ping_pong_using_signals.c -o ping_pong_using_signals
gcc test.c -o test

./test ping_pong_using_signals

rm test
rm ping_pong_using_signals

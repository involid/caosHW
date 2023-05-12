#!/bin/bash

gcc ping.c -o ping_program
IP=93.184.216.34 # example.com

tcpdump -i wlp2s0 ip src 93.184.216.34 > requests_list.txt 2> /dev/null &
TCPDUMP_PID=$!

PROGRAM_OUTPUT=$(sudo ./ping_program 93.184.216.34 5 100000)
sleep 1
kill $TCPDUMP_PID

EXPECTED_OUTPUT=$(cat requests_list.txt | grep "ICMP echo reply" | wc -l)

echo -n "Expected output: "
echo $EXPECTED_OUTPUT

echo -n "Real output: "
echo $PROGRAM_OUTPUT

rm ping_program
rm requests_list.txt

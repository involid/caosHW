#!/bin/bash

gcc signalfd_rtsig.c -o signalfd_rtsig
gcc test.c -o test

./test

rm test
rm signalfd_rtsig

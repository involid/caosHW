#!/bin/bash

g++ -shared -fPIC file.cpp -o file.so
nm file.so
rm file.so

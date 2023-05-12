#!/bin/bash

g++ -shared -fPIC example.cpp -o libexample.so
g++ main.cpp -L. -lexample -Wl,-rpath,'$ORIGIN' -o main
g++ tutorial.cpp -ldl -o tutorial

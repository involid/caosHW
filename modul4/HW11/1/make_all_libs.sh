#!/bin/bash

mkdir class_sources

g++ -shared -fPIC class_cpp/SimpleClass.cpp -o class_sources/SimpleClass.so
g++ -shared -fPIC class_cpp/SpecialClass.cpp -o class_sources/SpecialClass.so

mkdir class_sources/some
mkdir class_sources/some/package

g++ -shared -fPIC class_cpp/some/package/ClassInPackage.cpp -o class_sources/some/package/ClassInPackage.so

mkdir class_sources/std
mkdir class_sources/std/exe
mkdir class_sources/exe
mkdir class_sources/exe/std
mkdir class_sources/abra
mkdir class_sources/abra/std
mkdir class_sources/abra/std/cadabra

g++ -shared -fPIC class_cpp/std/Example1.cpp -o class_sources/std/Example1.so
g++ -shared -fPIC class_cpp/std/exe/Example2.cpp -o class_sources/std/exe/Example2.so
g++ -shared -fPIC class_cpp/exe/std/Example3.cpp -o class_sources/exe/std/Example3.so
g++ -shared -fPIC class_cpp/abra/std/cadabra/Example4.cpp -o class_sources/abra/std/cadabra/Example4.so

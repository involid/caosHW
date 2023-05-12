#!/bin/bash

cd dirs_test_1
mkdir dirs
cd dirs

mkdir A
mkdir B
mkdir C

mkdir A/dir1
mkdir A/dir2
mkdir B/dir1
mkdir B/dir3
mkdir C/dir1
mkdir C/dir2

sleep 0.01
echo -n "КАБАРДИНКА" > C/dir1/tmp1.txt
sleep 0.01
echo -n "КАРАКАТИЦА" > A/dir1/tmp1.txt
sleep 0.01
echo -n "КВАС" > B/dir1/tmp1.txt

sleep 0.01
echo -n "КИТЕЛЬ" > B/dir1/tmp3.txt
sleep 0.01
echo -n "КИРПИЧ" > A/dir1/tmp2.txt
sleep 0.01
echo -n "КИЛЬКА" > C/dir1/tmp3.txt

sleep 0.01
echo -n "КИОСК" > A/dir2/tmp1.txt
sleep 0.01
echo -n "КАРТОФЕЛЬ" > C/dir2/tmp2.txt

sleep 0.01
echo -n "КАСТРЮЛЯ" > A/dir2/a.txt
sleep 0.01
echo -n "КВАДРАТ" > C/dir2/b.txt

sleep 0.01
cp ../sources/government_inspector.txt B/dir3/c.txt
sleep 0.01
echo -n "КОМПАС" > B/dir3/d
sleep 0.01
echo -n "КРЕМЕНЬ" > B/dir3/e.txt

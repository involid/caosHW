mkdir build
cd build
cp ../0.c inf-II-12-0.c
cmake ..
make
mv matrix.so ../matrix.so
cd ..
rm -r build
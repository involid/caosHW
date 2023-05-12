rm -r build
mkdir build
cd build
cmake ..
make
mv exper ../exper
cd ..

umount mnt
./exper ./mnt --src files.zip
#ls -la mnt/A
#umount mnt
#cat x.txt
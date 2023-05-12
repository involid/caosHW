cmake .
make

rm -rf mnt
mkdir mnt
./simplefs ./mnt --src simplefs_src.txt

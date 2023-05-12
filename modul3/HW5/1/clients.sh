#!/bin/bash

IP=$1
PORT=$2

# TEST A: Readable simple

echo "FILE TEST A" > input/A_send_file
printf "abra\nshvabra\ncadabra" >> input/A_send_file

gcc clients/A_readable_simple.c -o clients/A_readable_simple
./clients/A_readable_simple $IP $PORT > output/A_real_output
rm clients/A_readable_simple

rm input/A_send_file

# TEST B: Readable many get

echo "FILE TEST B" > input/B_send_file
printf "foo\nbar" >> input/B_send_file

echo "FILE TEST B" > input/B_send_file_2
printf "bar\nfoo" >> input/B_send_file_2

gcc clients/B_readable_many_get.c -o clients/B_readable_many_get
./clients/B_readable_many_get $IP $PORT > output/B_real_output
rm clients/B_readable_many_get

rm input/B_send_file_2
rm input/B_send_file

# TEST C: Readable many strings

echo "FILE TEST C" > input/C_send_file
printf "ahahaha\nshvabra\ncadabra" >> input/C_send_file

gcc clients/C_readable_many_strings.c -o clients/C_readable_many_strings
./clients/C_readable_many_strings $IP $PORT > output/C_real_output
rm clients/C_readable_many_strings

rm input/C_send_file

# TEST D: Non exist

gcc clients/D_non_exist.c -o clients/D_non_exist
./clients/D_non_exist $IP $PORT > output/D_real_output
rm clients/D_non_exist

# TEST E: Non readable

echo -n "FILE TEST E" > input/E_send_file
chmod -r input/E_send_file

gcc clients/E_non_readable.c -o clients/E_non_readable
./clients/E_non_readable $IP $PORT > output/E_real_output
rm clients/E_non_readable

rm input/E_send_file

# TEST F: Exe non readable

echo "#!/bin/bash" > input/F_send_file
echo "echo \"Fstring 1\"" >> input/F_send_file
echo -n "echo \"Fstring 2\"" >> input/F_send_file
chmod -r input/F_send_file
chmod +x input/F_send_file

gcc clients/F_exe_non_readable.c -o clients/F_exe_non_readable
./clients/F_exe_non_readable $IP $PORT > output/F_real_output
rm clients/F_exe_non_readable

rm input/F_send_file

# TEST G: Exe readable

echo "#!/bin/bash" > input/G_send_file
echo "echo \"Gstring 1\"" >> input/G_send_file
echo -n "echo \"Gstring 2\"" >> input/G_send_file
chmod +x input/G_send_file

gcc clients/G_exe_readable.c -o clients/G_exe_readable
./clients/G_exe_readable $IP $PORT > output/G_real_output
rm clients/G_exe_readable

rm input/G_send_file

# TEST H: Sleep and signal

echo -n "FILE TEST H" > input/H_send_file
printf "cat\ngrep\nsed" >> input/H_send_file

gcc clients/H_sleep_and_signal.c -o clients/H_sleep_and_signal
./clients/H_sleep_and_signal $IP $PORT > output/H_real_output
rm clients/H_sleep_and_signal

rm input/H_send_file

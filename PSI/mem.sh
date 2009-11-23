#/bin/sh
gcc 12_mem_batas2_serwer.c -o serwer
gcc 12_mem_batas2_client.c -o client
./serwer&
./client&
./client&
./client&

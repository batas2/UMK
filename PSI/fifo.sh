#/bin/sh
rm -f /tmp/client_fifo*
rm -f /tmp/serwer_fifo
gcc 11_fifo_batas2_serwer.c -o serwer
gcc 11_fifo_batas2_client.c -o client

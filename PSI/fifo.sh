#/bin/sh
rm -f /tmp/client_fifo*
rm -f /tmp/serwer_fifo
gcc server.c -o _server
gcc client.c -o _client
rm -f /tmp/serwer_fifo
rm -f /tmp/client_fifo
./_server&
./_client

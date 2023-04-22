gcc -o server server.c
gcc -o client client.c

./server -l server.log -t 30
./client -l client.log -t 20

#/bin/bash

gcc -o multi-threaded-server multi-threaded-server.c -pthread
./multi-threaded-server

CC=gcc
CFLAGS=-Wall -Wno-unused-value -pthread

caltrain: caltrain-runner.c caltrain.c caltrain.h
	$(CC) $(CFLAGS) -o caltrain caltrain-runner.c -lpthread




gcc -pthread caltrain-runner.c caltrain.c
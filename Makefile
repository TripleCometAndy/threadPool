OBJS = main.o
CC = g++
CFLAGS = -std=c++11 -Wall -O3  -c  -g

threadPool: $(OBJS)
	$(CC) $(OBJS) -pthread -o threadPool

main.o: main.cpp threadPool.h
	$(CC) $(CFLAGS) main.cpp
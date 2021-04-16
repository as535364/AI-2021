CC:=g++
CFLAGS = -Wall -std=c++17 -g -O2

all: UCS
	$(CC) $(CFLAGS) -o P1_UCS UCS.cpp

.PHONY:clean
clean:
	rm -rf *.o P1_UCS

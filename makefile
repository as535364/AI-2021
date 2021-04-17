CC:=g++
CFLAGS = -Wall -std=c++17 -g -O2

all:
	$(CC) $(CFLAGS) -o P1_UCS UCS.cpp
	$(CC) $(CFLAGS) -o P1_IDS IDFS.cpp

.PHONY:clean
clean:
	rm -rf *.o *.out P1_UCS P1_IDS

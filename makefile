CC:=g++
CFLAGS = -Wall -std=c++17 -g -O2

all:
	$(CC) $(CFLAGS) -o P1_UCS P1_UCS.cpp
	$(CC) $(CFLAGS) -o P2_IDS P2_IDS.cpp
	$(CC) $(CFLAGS) -o P3_IDASTAR P3_IDASTAR.cpp

.PHONY:clean
clean:
	rm -rf *.o *.out P1_UCS P1_IDS

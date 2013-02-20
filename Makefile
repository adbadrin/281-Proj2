PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

all:
	g++ -std=c++11 main.cpp build.cpp round.cpp -o proj2

test:
	g++ -std=c++11 -g -Wall -Wextra -Wvla main.cpp build.cpp round.cpp -o test

clean:
	rm *.o proj2

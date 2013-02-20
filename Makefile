PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

all:
	g++ -std=c++11 -O3 main.cpp build.cpp zombies.cpp -o proj2

clean:
	rm *.o proj2

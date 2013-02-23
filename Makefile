PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64

all:
	g++ -std=c++11 main.cpp build.cpp round.cpp -o proj2

test:
	g++ -std=c++11 -g main.cpp build.cpp round.cpp -o test

altTest:
	g++ -std=c++11 -g main.cpp -o alttest

altTest2:
	g++ -std=c++11 -g tester.cpp -o alttest2

clean:
	rm *.o proj2 test alttest alttest2

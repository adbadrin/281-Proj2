#include <iostream>
#include "zombies.h"
#include "poorman_heap.h"
#include <list>
using namespace std;

struct testSt {
	testSt(int i_, int j_) : i(i_), j(j_) {}
	int i;
	int j;
};

int main() {
	list<zombies> testList;
	eecs281heap<zombies*, zombComp>* myHeap;
	zombComp compr;
	poorman_heap<zombies*, zombComp> poor(compr);
	myHeap = &poor;
	srand(10);
	for(int i = 0; i < 10; i++) {
		zombies myZ(100,10, i);
		testList.push_back(myZ);
		myHeap->push(&(testList.back()));
	}
	while(!(myHeap->empty())) {
		zombies* temp = myHeap->top();
		cout << "(" << temp->dist << ", " << temp->speed << "," << temp->name  << ") \n";
		myHeap->pop();
	}
	return 0;
}
			



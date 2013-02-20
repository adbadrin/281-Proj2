#include "zombies.h"
#include "poorman_heap.h"
#include <fstream>

void doRound(std::list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int& currRound, int& dumZomNum, fstream& myFile, bool& playerAlive, bool& allDead, int params[], int killerZom);

void playerAction(list<zombies>& master, eecs281heap<zombies*, zombComb>* myHeap, int params[], bool& allDead, int currRound);

int zombieAction(list<zombies>& master, ifstream& myFile, bool& playerAlive, bool& allDead);

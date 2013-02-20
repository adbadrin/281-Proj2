#ifndef BUILD_H
#define BUILD_H
#include "zombies.h"
#include "poorman_heap.h"
#include <fstream>

void zombieGen(std::list<zombies> master, eecs281heap<zombies*, zombComp>* myHeap, int params[], int toGen, int& dumZomNum, bool& allDead);

void updateZombie(zombies zom);

void playerAction(std::list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int params[], bool& allDead, int currRound);

int zombieAction(std::list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, bool& playerAlive, bool& allDead);

void doRound(std::list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int& currRound, int& dumZomNum, std::ifstream& myFile, bool& playerAlive, bool& allDead, int params[], int& killerZom);

#endif

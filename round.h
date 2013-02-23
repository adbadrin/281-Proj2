#ifndef ROUND_H
#define ROUND_H
#include <fstream>
#include "zombies.h"
#include "eecs281heap.h"


void zombieGen(std::list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int params[], int toGen, int& dumZomNum, bool& allDead);

void updateZombie(zombies& zom);

void playerAction(eecs281heap<zombies*, zombComp>* myHeap, int params[], bool& allDead, int currRound, std::string& lastKilled);

std::string zombieAction(std::list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, bool& playerAlive, bool& allDead);

void doRound(std::list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int& currRound, int& dumZomNum, std::ifstream& myFile, bool& playerAlive, bool& allDead, int params[], std::string& killerZom, std::string& lastKilled);

#endif

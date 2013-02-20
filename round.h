#include "zombies.h"
#include "eecs281heap.h"
#include <fstream>

void doRound(list<zombies> master, int genZomNum, ifstream& myfile);

void playerAction(list<zombies>& master, eecs281heap& myheap);

void zombieActions(list<zombies> master, int genZomNum, ifstream& myfile);

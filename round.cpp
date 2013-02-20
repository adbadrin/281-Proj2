#include "round.h"
using namespace std;

void zombieGen(list<zombies> master, eecs281heap<zombies*, zombComp>* myHeap, int params[], int toGen, int& counter, bool& allDead) {
	for(int i = 0; i < toGen; i++) {
		zombies temp(params[0], params[1], counter);
		master.push_back(temp);
		counter++;
	}
	if(toGen > 0) {
			allDead = false;
			myHeap.make_Heap();
	}
}

void updateZombie(zombies zom) {
	if(zom.whenShot() == -1) {
		int random_offset = (rand() % zom.speed)/2;
		zom.dist = zom.dist - zom.speed - random_offset;
		zom.roundsAlive++;
	}
}

void playerAction(list<zombies>& master, eecs281heap<zombies*, zombComb>* myHeap, int params[], bool& allDead, int currRound) {
	if(allDead) {}
	else {
		for(int i = 1; i <= params[0]; i++) {
			if(myHeap.empty()) {
				allDead = true;
				break;
			}
				zombie* victim = myHeap.top();
				victim->whenShot = currRound;
				myHeap.pop();
			}
	}
	if(myHeap.empty()) {
		allDead = true;
	}
}

int zombieAction(list<zombies>& master, eecs281hea<zombies*, zombComb>* myHeap, ifstream& myFile, bool& playerAlive, bool& allDead) {
	if(allDead) {}
	else {
		for(int i = 0; master.begin() + i != master.end()) {
			if((master.begin() + i)-> whenShot == -1) {}
			else {
					updateZombie(*(master.begin() + i));
					if((*(master.begin() + i)).dist <= 0) {
							playerAlive = false;
							return i;
					}
			}
		}
	myHeap.make_heap();
	return -1;
	}
}



void doRound(list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int& currRound, int& dumZomNum, fstream& myFile, bool& playerAlive, bool& allDead, int params[], int killerZom) {
	int zomsToGen;
	int killerZom;
	string s;
	if(myFile.good()) {
		getline(myFile, s);
		int j = atoi(s.substr(s.find_first_of(" ") + 1));
		if(j > currRound) {
				while(currRound != j) {
						currRound++;
						playerAction(master, myHeap, playerAlive, allDead);
						killerZom = zombieAction(master, myFile, playerAlive, allDead);
						if(!(playerAlive)) {
								break;
						}
				}
				getline(myFile, s);
		}
		if(playerAlive) {
				if(s[0] = "N") {
					nextZomGen = atoi(s.substr(s.find_first_of(" ") + 1));
					zombieGen(master, myHeap, params, zomsToGen, dumZomNum);
					getline(myFile, s);
				}
				while( (s!= "---") || myFile.good()) {
						int specZomDist = atoi(s.substr(0, find_first_of(" ")));
						s = s.substr(f_first_of(" ") + 1);
						int specZomSpd = atoi(s.substr(0, find_first_of(" ")));
						s = s.substr(f_first_of(" ") + 1);
						zombie specZom(specZomDist, specZomSpd, s);
						master.push_back(specZom);
				}
				myHeap.make_heap();
				playerAction(master, myHeap);
				killerZom = zombieAction(master, myFile, playerAlive, allDead);
		}
	}
	else {
		currRound++;
		playerAction(master, myHeap, playerAlive, allDead, currRound);
		killerZom = zombieAction(master, myFile, playerAlive, allDead);
	}
}


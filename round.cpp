#include "round.h"
using namespace std;

void zombieGen(list<zombies> master, eecs281heap<zombies*, zombComp>* myHeap, int params[], int toGen, int& dumZomNum, bool& allDead) {
	for(int i = 0; i < toGen; i++) {
		zombies temp(params[2], params[3], dumZomNum);
		zombies* tempPoint = &temp;
		master.push_back(temp);
		myHeap->push(tempPoint);
		dumZomNum++;
	}
	if(toGen > 0) {
			allDead = false;
			myHeap->make_heap();
	}
}

void updateZombie(zombies zom) {
	if(zom.whenShot == -1) {
		int random_offset = (rand() % zom.speed)/2;
		zom.dist = zom.dist - zom.speed - random_offset;
		zom.roundsAlive++;
	}
}

void playerAction(list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int params[], bool& allDead, int currRound) {
	if(allDead) {}
	else {
		for(int i = 1; i <= params[0]; i++) {
			if(myHeap->empty()) {
				allDead = true;
				break;
			}
				zombies* victim = myHeap->top();
				victim->whenShot = currRound;
				myHeap->pop();
			}
	}
	if(myHeap->empty()) {
		allDead = true;
	}
}

int zombieAction(list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, bool& playerAlive, bool& allDead) {
	if(allDead) {}
	list<zombies>::iterator myItr = master.begin();
	int i = 0;
		while(myItr != master.end()) {
			if(myItr-> whenShot == -1) {}
			else {
					updateZombie(*myItr);
					if(myItr->dist <= 0) {
							playerAlive = false;
							return i;
					}
			}
			myItr++;
			i++;
		}
	myHeap->make_heap();
	return -1;
}
void doRound(list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int& currRound, int& dumZomNum, fstream& myFile, bool& playerAlive, bool& allDead, int params[], int& killerZom) {
	int zomsToGen;
	string s;
	if(myFile.good()) {
		getline(myFile, s);
		int j = atoi((s.substr(s.find_first_of(" ") + 1)).c_str());
		if(j > currRound) {
				while(currRound != j) {
						currRound++;
						playerAction(master, myHeap, params, allDead, currRound);
						killerZom = zombieAction(master, myHeap, playerAlive, allDead);
						if(!(playerAlive)) {
								break;
						}
				}
				getline(myFile, s);
		}
		if(playerAlive) {
				if(s[0] = 'N') {
					zomsToGen = atoi((s.substr(s.find_first_of(" ") + 1)).c_str());
					zombieGen(master, myHeap, params, zomsToGen, dumZomNum, allDead);
					getline(myFile, s);
				}
				while( (s!= "---") || myFile.good()) {
						int specZomDist = atoi((s.substr(0, s.find_first_of(" "))).c_str());
						s = s.substr(s.find_first_of(" ") + 1);
						int specZomSpd = atoi((s.substr(0, s.find_first_of(" "))).c_str());
						s = s.substr(s.find_first_of(" ") + 1);
						zombies specZom(specZomDist, specZomSpd, s);
						master.push_back(specZom);
				}
				myHeap->make_heap();
				playerAction(master, myHeap, params, allDead, currRound);
				killerZom = zombieAction(master, myHeap, playerAlive, allDead);
		}
	}
	else {
		currRound++;
		playerAction(master, myHeap, params, allDead, currRound);
		killerZom = zombieAction(master, myHeap, playerAlive, allDead);
	}
}


#include "round.h"
#include <iostream>
using namespace std;

void zombieGen(list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int params[], int toGen, int& dumZomNum, bool& allDead) {
	for(int i = 0; i < toGen; i++) {
		zombies temp(params[2], params[3], dumZomNum);
		master.push_back(temp);
		myHeap->push(&(master.back()));
		dumZomNum++;
		cout << temp.name << " spawns at " << temp.dist << "\n";
	}
	if(toGen > 0) {
			allDead = false;
			myHeap->make_heap();
	}
}

void updateZombie(zombies& zom) {
	if(zom.whenShot == -1) {
		int random_offset = (rand() % zom.speed)/2;
		zom.dist = zom.dist - zom.speed - random_offset;
		zom.roundsAlive++;
		cout << zom.name << " moves to " << zom.dist << "\n";
	}
}

void playerAction(eecs281heap<zombies*, zombComp>* myHeap, int params[], bool& allDead, int currRound, string& lastKilled) {
	if(allDead) {}
	else {
		for(int i = 1; i <= params[0]; i++) {
			if((myHeap->empty())) {
				allDead = true;
				break;
			}
				zombies* victim = myHeap->top();
				victim->whenShot = currRound;
				lastKilled = victim->name; //(THIS IS WHERE THE SEGFAULT HAPPENS!)
				cout << lastKilled << " killed \n";
				myHeap->pop();
			}
	}
	if(myHeap->empty()) {
		allDead = true;
	}
}

string zombieAction(list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, bool& playerAlive, bool& allDead) {
	string killerZom = "";
	if(allDead) {
		return "";
	}
	list<zombies>::iterator myItr = master.begin();
	while(myItr != master.end()) {
		if(myItr-> whenShot > -1) {}
		else {
			updateZombie(*myItr);
			if((myItr->dist <= 0) && playerAlive) {
				playerAlive = false;
				killerZom =  myItr->name;
			}
		}
		myItr++;
	}
	myHeap->make_heap();
	return killerZom;
}
void doRound(list<zombies>& master, eecs281heap<zombies*, zombComp>* myHeap, int& currRound, int& dumZomNum, ifstream& myFile, bool& playerAlive, bool& allDead, int params[], string& killerZom, string& lastKilled) {
	int zomsToGen;
	string s;
	if(myFile.good()) {
		getline(myFile, s);
		int j = atoi((s.substr(s.find_first_of(" ") + 1)).c_str());
		if(j > currRound) {
				while(currRound != j) {
						cout<< "Round: " << currRound << "\n";
						killerZom = zombieAction(master, myHeap, playerAlive, allDead);
						playerAction(myHeap, params, allDead, currRound, lastKilled);
						if(!(playerAlive)) {
								break;
						}
						currRound++;
				}
		}
		getline(myFile,s);
		if(playerAlive) {
				cout << "Round: " << currRound << "\n";
				killerZom = zombieAction(master, myHeap, playerAlive, allDead);
				if(playerAlive) {
						if(s[0] == 'N') {
							zomsToGen = atoi((s.substr(s.find_first_of(" ") + 1)).c_str());
							zombieGen(master, myHeap, params, zomsToGen, dumZomNum, allDead);
							getline(myFile, s);
						}
						while((s!= "---") && myFile.good()) {
								int specZomDist = atoi((s.substr(0, s.find_first_of(" "))).c_str());
								s = s.substr(s.find_first_of(" ") + 1);
								int specZomSpd = atoi((s.substr(0, s.find_first_of(" "))).c_str());
								s = s.substr(s.find_first_of(" ") + 1);
								zombies specZom(specZomDist, specZomSpd, s);
								master.push_back(specZom);
								myHeap->push(&(master.back()));
								cout << specZom.name << " spawns at " << specZomDist << "\n";
								getline(myFile, s);
						}
						myHeap->make_heap();
						playerAction(myHeap, params, allDead, currRound, lastKilled);
						currRound++;
				}
		}
	}
	else {
		cout << "Round: " << currRound << "\n";
		killerZom = zombieAction(master, myHeap, playerAlive, allDead);
		playerAction(myHeap, params, allDead, currRound, lastKilled);
		if(playerAlive) {
			currRound++;
		}
	}
}


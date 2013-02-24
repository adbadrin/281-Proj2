#include <getopt.h>
#include <iostream>
#include "zombies.h"
#include <list>
#include "build.h"
#include "poorman_heap.h"
#include "sorted_heap.h"
#include "binary_heap.h"
#include "round.h"
using namespace std;


void printHelp() {
	//As name says, prints description of the program
	cout << "NAME \n";
	cout << "notld - a command line ‘Night of the Living Deadline’ game simulation program. \n";
	cout << "SYNOPSIS \n";
	cout << "notld (-c | --container) CONTAINER [-v | --verbose N] GAMEFILE \n";
	cout << "notld (-h | --help) \n ";
	cout << "DESCRIPTION \n";
	cout << "NOTLD (Night of the Living Deadline) game simulator with both zombie and player AI. This program acts as the player in an NOTLD game and shoots zombies in the optimal ordering to achieve the best possible result (stay alive for as long as possible). \n";
	cout << "OPTIONS \n";
	cout << "-h, --help \n";
	cout << "Print this help screen and exit. \n";
	cout << "-c, --container \n";
	cout << "Required option that states the type of priority queue to use. Must be one of BINARY, POOR_MAN, SORTED, or PAIRING. \n";
	cout << "-v, --verbose N \n";
	cout << "An optional option that indicates the program should print additional output statistics. \n";
}

struct shotSorter{
	bool doLexi;
	shotSorter(bool doLexi_) : doLexi(doLexi_) {}
	bool operator()(zombies zom1, zombies zom2) {
			if(zom1.whenShot == zom2.whenShot) {
					if(doLexi) {
						return zom1.name < zom2.name;
					}
					return zom1.name > zom2.name;
			}
			if(zom1.whenShot < zom2.whenShot) {
					return true;
			}
			return false;
	}
};

struct activeSorter{
	bool doLexi;
	activeSorter(bool doLexi_) : doLexi(doLexi_) {}
	bool operator()(zombies zom1, zombies zom2) {
		if(zom1.roundsAlive == zom2.roundsAlive) {
				if(doLexi) {
				return zom1.name < zom2.name;
				}
				return zom1.name < zom1.name;
		}
		if(zom1.roundsAlive < zom2.roundsAlive) {
			return true;
		}
		return false;
	}
};

void doVerbosity(list<zombies>& master, int level) {
	int numAlive = 0;
	list<zombies>::iterator myItr = master.begin();
	while(myItr != master.end()) {
			if(myItr->whenShot == -1) {
					numAlive++;
			}
			myItr++;
	}
	cout << "Zombies still active: " << numAlive << "\n";
	shotSorter sSort(true);
	activeSorter aSort(false);
	master.sort(sSort);
	int i = 0;
	myItr = master.begin();
	cout << "First zombies shot: \n";
	while(i < level) {
			if(myItr == master.end()) {
					break;
			}
			if(myItr->whenShot == -1) {}
			else {
					i++;
					cout << myItr->name << " " << i << "\n";
			}
			myItr++;
	}
	sSort.doLexi = false;
	master.sort(sSort);
	cout << "Last zombies shot: \n";
	i = 0;
	myItr = master.end();
	myItr--;
	while(i < level) {
			if(myItr == master.begin()) {
					break;
			}
			if(myItr->whenShot == -1) {
				break;
			}
			else {
					cout << myItr->name << " " << level - i << "\n";
					i++;
			}
			myItr--;
	}
	
	master.sort(aSort);
	cout << "Most active zombies: \n";
	i = 0;
	myItr = master.end();
	myItr--;
	while(i < level) {
			if(myItr == master.begin()) {
					break;
			}
			else {
					i++;
					cout <<myItr->name << " " << myItr->roundsAlive << "\n";
			}
			myItr--;
	}
	aSort.doLexi = true;
	master.sort(aSort);
	cout << "Least active zombies: \n";
	i = 0;
	myItr = master.begin();
	while(i < level) {
			if(myItr == master.end()) {
					break;
			}
			else {
					i++;
					cout << myItr->name << " " << myItr->roundsAlive << "\n";
			}
			myItr++;
	}

}

			
int main(int argc, char* argv[]) {
	list<zombies> master;
	bool gaveContainer = false; //Checks if a container type is provided
	bool givenGameFile = false; //Checks if a GAMEFILE is provided
	string heapType; //Stores type of heap to use 
	char* gameFile; //Stores name of gamefile
	bool beVerbose = false;
	int verbosity = -1; //Stores level of verbosity
	int c = 0;
	while(c != -1) {
		const struct option long_options[] = {
			{"help", 0, 0, 'h'},
			{"container", 1, 0, 'c'},
			{"verbose", 1, 0, 'v'},
			{0, 0, 0, 0}
		};
		int option_index = 0;
		c = getopt_long(argc, argv, "hc:v:", long_options, &option_index);
		switch(c) {
			case 'h':
				printHelp();
				return 0;

			case 'c':
				heapType = optarg;
				gaveContainer = true;
				break;

			case 'v':
				verbosity = atoi(optarg);
				beVerbose = true;
				break;
			
			default:
				break;
		}
	}
	//Process any remaining command line arguments
	if(optind < argc) {
		givenGameFile = true;
		gameFile = argv[optind++];
	}
	if(!(gaveContainer && givenGameFile)) {
		cerr << "Container type or GAMEFILE missing! \n";
		return 1;
	}
	ifstream myFile(gameFile);
	int params[4];
	setParams(myFile, params);
	srand(params[1]);
	zombComp myComp;
	eecs281heap<zombies*, zombComp>* myHeap;
	poorman_heap<zombies*, zombComp> poor (myComp);
	sorted_heap<zombies*, zombComp> sorte (myComp);
	binary_heap<zombies*, zombComp> bine (myComp);
	if(heapType == "POOR_MAN") {
		myHeap = &poor;
	}
	else if(heapType == "SORTED") {
		myHeap = &sorte;
	}
	else if(heapType == "BINARY") {
		myHeap = &bine;
	}
	bool playerAlive = true;
	bool allDead = true;
	int currRound = 1;
	int dumZomNum = 0;
	int shotNum = 0;
	string killerZom = "";
	string lastKilled = "";
	while(playerAlive && !(allDead && !myFile.good())) {
			doRound(master, myHeap, currRound, dumZomNum, myFile, playerAlive, allDead, params, killerZom, lastKilled, shotNum);
	}
	if(playerAlive) {
		cout << "VICTORY IN ROUND " << currRound - 1 << "! " << lastKilled << " was the last zombie. \n";
	}
	else {
		cout <<"DEFEAT IN ROUND " << currRound - 1 <<  "! " << killerZom << " ate your brains!\n";
	}
	if(beVerbose) {
		doVerbosity(master, verbosity);
	}
}

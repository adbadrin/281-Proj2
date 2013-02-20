#include <getopt.h>
#include <iostream>
#include "build.h"
#include "poorman_heap.h"
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

int main(int argc, char* argv[]) {
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
	list<zombies> master;
	eecs281heap<zombies*, zombComp>* myHeap;
	poorman_heap<zombies*, zombComp> poor;
	myHeap = &poor;
	bool playerAlive = true;
	bool allDead = true;
	int currRound = 1;
	int dumZomNum = 0;
	string killerZom = "";
	string lastKilled = "";
	while(playerAlive || (allDead && !(myFile.good()))) {
			doRound(master, myHeap, currRound, dumZomNum, myFile, playerAlive, allDead, params, killerZom, lastKilled);
	}
	if(playerAlive) {
		cout << "VICTORY IN ROUND " << currRound << "! " << lastKilled << " was the last zombie. \n";
	}
	else {
		cout <<"DEFEAT IN ROUND " << currRound <<  "! " << killerZom << " ate your brains!\n";
	}
	if(beVerbose) {
		//doVerbosity
	}
}

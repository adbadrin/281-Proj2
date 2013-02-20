#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <cstdlib>
#include <string>
#include <list>

struct zombies {

	zombies(int maxDist, int maxSpeed, int counter);
	zombies(int maxDist, int maxSpeed, std::string name_);
	int dist;
	int speed;
	std::string name;
	int rounds;
};

void updateZombie(zombies zom);

void zombieGen(std::list<zombies> master, int params[], int toGen, int& counter);

#endif

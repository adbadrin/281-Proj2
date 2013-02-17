#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <cstdlib>
#include <string>
#include <list>

struct zombies {

	zombies::zombies(int maxDist, int maxSpeed, int counter);
	zombies::zombies(int maxDist, int maxSpeed, std::string name);
	int dist;
	int speed;
	std::string name;
	int rounds;
}

void updateZombie(zombie zom); 

void zombieGen(std::list master, int params[], int& counter);

#endif

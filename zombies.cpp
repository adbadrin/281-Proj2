#include "zombies.h"
using namespace std;

zombies::zombies(int maxDist, int maxSpeed, int counter) : dist(rand() % maxDist + 1), speed(rand() % maxSpeed + 1), name("AI" + std::to_string(counter)), rounds(0) {}


zombies(int maxDist, int maxSpeed, std::string name) : dist(rand() % maxDist + 1), speed(rand() % maxSpeed + 1), name(name), rounds(0) {}


void zombieGen(list master, int params[], int toGen, int& counter) {
	for(int i = 0; i < toGen; i++) {
		zombie temp(params[0], params[1], counter);
		master.push_back(temp);
		counter++;
}

void updateZombie(zombie zom) {
	random_offset = (rand() % speed)/2;
	zom.dist = dist - zom.speed - random_offset;
}



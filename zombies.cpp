#include "zombies.h"
using namespace std;

zombies::zombies(int maxDist, int maxSpeed, int counter) : dist(rand() % maxDist + 1), speed(rand() % maxSpeed + 1), name("AI" + to_string(counter++)) {}


zombies::zombies(int maxDist, int maxSpeed, std::string name_) : dist(rand() % maxDist + 1), speed(rand() % maxSpeed + 1), name(name_) {}


void zombieGen(list<zombies> master, int params[], int toGen, int& counter) {
	for(int i = 0; i < toGen; i++) {
		zombies temp(params[0], params[1], counter);
		master.push_back(temp);
		counter++;
	}
}

void updateZombie(zombies zom) {
	int random_offset = (rand() % zom.speed)/2;
	zom.dist = zom.dist - zom.speed - random_offset;
}



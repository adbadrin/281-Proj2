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
	int roundsAlive;
	int whenShot;
};

struct zombComp{
	bool operator()(zombies zom1, zombies zom2) {
		int zom1ETA = zom1.dist / zom1.speed;
		int zom2ETA = zom2.dist / zom2.speed;
		if(zom1ETA == zom2ETA) {
			return zom1.name  < zom2.name;
		}
		return zom1ETA < zom2ETA;
	}
	bool operator()(zombies* zom1, zombies* zom2) {
		int zom1ETA = zom1->dist / zom1->speed;
		int zom2ETA = zom2->dist / zom2->speed;
		if(zom1ETA == zom2ETA) {
			return zom1->name < zom2->name;
		}
		return zom1ETA < zom2ETA;
	}
};

zombies::zombies(int maxDist, int maxSpeed, int counter) : dist(rand() % maxDist + 1), speed(rand() % maxSpeed + 1), name("AI" + to_string(counter++)), roundsAlive(0), whenShot(-1) {}


zombies::zombies(int maxDist, int maxSpeed, std::string name_) : dist(rand() % maxDist + 1), speed(rand() % maxSpeed + 1), name(name_), roundsAlive(0), whenShot(-1) {}



#endif

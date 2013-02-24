#ifndef ZOMBIES_H
#define ZOMBIES_H
#include <cstdlib>
#include <string>
#include <list>

struct zombies {
	int dist;
	int speed;
	std::string name;
	int roundsAlive;
	int whenShot;
	zombies(int maxDist, int maxSpeed, int& counter) {
		dist = rand() % maxDist + 1;
		speed = rand() % maxSpeed + 1;
		name = "AI";
		roundsAlive = 1;
		whenShot = -1;
		name += std::to_string(counter);
	}
	zombies(int maxDist, int maxSpeed, std::string name_) {
		dist = maxDist;
		speed = maxSpeed;
		name = name_;
		roundsAlive = 1;
		whenShot = -1;
	}
};

struct zombComp{
	bool operator()(zombies zom1, zombies zom2) {
		int zom1ETA = zom1.dist / zom1.speed;
		int zom2ETA = zom2.dist / zom2.speed;
		if(zom1ETA == zom2ETA) {
			return zom1.name  > zom2.name;
		}
		return zom1ETA > zom2ETA;
	}
	bool operator()(zombies* zom1, zombies* zom2) {
		int zom1ETA = zom1->dist / zom1->speed;
		int zom2ETA = zom2->dist / zom2->speed;
		if(zom1ETA == zom2ETA) {
			return zom1->name > zom2->name;
		}
		return zom1ETA > zom2ETA;
	}
};

#endif

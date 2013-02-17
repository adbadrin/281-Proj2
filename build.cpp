#include "build.h"
#include <ifstream>
using namespace std;


void setParams(ifstream myfile, int params[]) {
	myfile.open(gameFile);
	string s;
	int j;
	for(int i = 0 ; i < 4; i++) {
		myfile.getline(s);
		j = s.find_first_of(" ");
		s.substr(j+1);
		params[i] = atoi(s.c_str());
	}
}


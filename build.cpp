#include "build.h"
using namespace std;


void setParams(ifstream& myfile, int params[]) {
	string s;
	int j;
	for(int i = 0 ; i < 4; i++) {
		getline(myfile, s);
		j = s.find_first_of(" ") + 1;
		s = s.substr(j+1);
		params[i] = atoi(s.c_str());
	}
}


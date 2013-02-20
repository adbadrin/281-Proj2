#include "build.h"
using namespace std;

//Pushes the important stuff into params
//param[0] = Quiver_capacity
//param[1] = Random_seed
//param[2] = max rand distance
//param[3] = max rand speed
void setParams(ifstream& myfile, int params[]) {
	string s;
	int j;
	for(int i = 0 ; i < 4; i++) {
		getline(myfile, s);
		j = s.find_first_of(" ") + 1;
		s = s.substr(j);
		params[i] = atoi(s.c_str());
	}
	getline(myfile, s);
}


#include "basic.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
bool ReadInt(int &output) {
	string input = "";
	getline(cin, input);
	stringstream mystream(input);
	if (mystream >> output) {
		return true;
	}
	return false;
}

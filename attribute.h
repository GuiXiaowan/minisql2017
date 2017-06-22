#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

using namespace std;

class Attribute {
public:
	string name;
	int type; // -1 == float, 0 == int, n(n>0) == char(n)
	bool isUnique;
	
	Attribute(string name, int type, bool isUnique);
	Attribute();

public:
	void show_attr();
};

#endif
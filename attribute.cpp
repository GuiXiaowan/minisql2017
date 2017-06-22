#include "attribute.h"
#include <sstream>
#include <iostream>

using namespace std;

Attribute::Attribute(string name, int type,	bool isUnique) {
	this->name = name;
	this->type = type;
	this->isUnique = isUnique;
}

Attribute::Attribute() {
	this->name = "";
	this->type = 0;//Ä¬ÈÏÎªint
	this->isUnique = false;
}

void Attribute::show_attr() {
	/*cout << "Name : " << name <<endl;
	cout << "Type : " << type << endl;
	cout << "isUnique : " << isUnique << endl;
	cout << "isPriamary : " << isPrimary << endl;*/
	string Type;
	string postfix = "\t";
	if (type == -1) {
		Type = "float";
	}
	else if (type == 0) {
		Type = "int";
	}
	else {
		Type = "char(";
		stringstream ss;
		ss << type;
		Type += ss.str();
		Type += ")";
	}
	if (isUnique == true) {
		postfix += "unique";
	}
	cout << name << "\t" << Type << postfix <<endl;
}
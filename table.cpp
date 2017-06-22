#include "table.h"
#include <vector>
#include <iostream>

using namespace std;

Table::Table(string name, vector<Attribute> attr) {
	tableName = name;
	attributes = attr;
}

Table::Table() {
	tableName = "";
	primaryKey = "";
}

void Table::showTable() {
	cout << "Table name: " << tableName << endl;
	cout << "Primary Key : " + primaryKey << endl;
	vector<Attribute>::iterator v;
	v = attributes.begin();
	while (v != attributes.end()) {
		v->show_attr();
		v++;
	}
}
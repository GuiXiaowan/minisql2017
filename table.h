#ifndef TABLE_H
#define TABLE_H

#include "attribute.h"
#include <vector>

using namespace std;

class Table{
public:
	string tableName;
	vector<Attribute> attributes;
	int attrNum;
	string primaryKey;

	Table(string name, vector<Attribute> attr);
	Table();
	void showTable();
};

#endif
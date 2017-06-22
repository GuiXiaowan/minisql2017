#ifndef CONDITION_H
#define CONDITION_H

#include <string>
#include <sstream>

using namespace std;

class Condition {
public:
	const static int SQL_EQUAL = 0;
	const static int SQL_NOT_EQUAL = 1;
	const static int SQL_LESS = 2;
	const static int SQL_MORE = 3;
	const static int SQL_NOT_LESS = 4;
	const static int SQL_NOT_MORE = 5;
	
	string attr_name;
	string value;
	int cmp_type;
	int type;

	Condition(string attr_name, string value, string op, int type);
	Condition() {}
	int convert(string op);

	bool sql_compare(int val);
	bool sql_compare(float val);
	bool sql_compare(string val);//这三个是否保留再议

};

/*
select attr_name
from table_name
where attr_name = (type)value;
*/

#endif 

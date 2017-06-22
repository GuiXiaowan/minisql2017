#include "condition.h"
#include <iostream>

using namespace std;

Condition::Condition(string attr_name, string value, string op, int type) {
	this->attr_name = attr_name;
	this->value = value;
	this->cmp_type = this->convert(op);
	this->type = type;
}

int Condition::convert(string op) {
	if (op == "=") {
		return SQL_EQUAL;
	}
	else if (op == "<>") {
		return SQL_NOT_EQUAL;
	}
	else if (op == "<") {
		return SQL_LESS;
	}
	else if (op == ">") {
		return SQL_MORE;
	}
	else if (op == "<=") {
		return SQL_NOT_MORE;
	}
	else if (op == ">=") {
		return SQL_NOT_LESS;
	}
	else {
		return -1;//∑«∑® ‰»Î
	}
}

/*
bool Condition::sql_compare(int val) {
	int realVal;
	stringstream ss;
	ss << value;
	ss >> realVal;

	switch (type) {
	case SQL_EQUAL:
		return val == realVal;
	case SQL_NOT_EQUAL:
		return val != realVal;
	case SQL_LESS:
		return realVal < val;
	case SQL_MORE:
		return realVal > val;
	case SQL_NOT_LESS:
		return realVal >= val;
	case SQL_NOT_MORE:
		return realVal <= val;
	default:
		cout << "No such kind of operations." << endl;
		return false;
	}
}
bool Condition::sql_compare(float val) {
	float realVal;
	stringstream ss;
	ss << value;
	ss >> realVal;

	switch (type) {
	case SQL_EQUAL:
		return val == realVal;
	case SQL_NOT_EQUAL:
		return val != realVal;
	case SQL_LESS:
		return realVal < val;
	case SQL_MORE:
		return realVal > val;
	case SQL_NOT_LESS:
		return realVal >= val;
	case SQL_NOT_MORE:
		return realVal <= val;
	default:
		cout << "No such kind of operations." << endl;
		return false;
	}
}
bool Condition::sql_compare(string val) {
	switch (cmp_type) {
	case SQL_EQUAL:
		return val == value;
	case SQL_NOT_EQUAL:
		return val != value;
	case SQL_LESS:
		return value < val;
	case SQL_MORE:
		return value > val;
	case SQL_NOT_LESS:
		return value >= val;
	case SQL_NOT_MORE:
		return value <= val;
	default:
		cout << "No such kind of operations." << endl;
		return false;
	}
}

*/
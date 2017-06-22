#ifndef API_H
#define API_H

#include "table.h"
#include "condition.h"
#include "minisql.h"
#include "interpreter.h"
#include <time.h>

extern class Record rm;
extern class Catalog cm;

using namespace std;

class API {
public:
	double flag = 1;
	void createTable(Table tb);
	int dropTable(string tableName);//failed, return 0, else return 1

	int selectRow(string tableName, vector<Condition> vc);//failed, return 0, else return 1
	int selectAll(string tableName);
	int insertRow(string tableName, vector<Attribute> attrs);//此处用属性来表示每一项的值与类型
	int deleteRow(string tableName, vector<Condition> vc);
	int deleteAllTable(string tableName);

	int createIndex(string indexName, string tableName, string attr);
	int dropIndex(string indexName);

};

#endif // API_H

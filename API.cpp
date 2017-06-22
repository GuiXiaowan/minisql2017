#include <string>
#include <iostream>
#include <vector>
#include "API.h"

using namespace std;

void API::createTable(Table tb) {
	//tb.showTable();//debug
	cm.CreateTable(tb);
	rm.CreateTable(tb);
	cout << "api.createTable done" << endl;
}

int API::dropTable(string tableName) {
	//return 1;
	cm.DeleteTable(tableName);
	rm.DropTable(tableName);
	cout << "api.dropTable done" << endl;
	return 1;
}

int API::selectRow(string tableName, vector<Condition> vc) {
	
	/*cout << "Table Name : " + tableName << endl;
	vector<Condition>::iterator vi;
	vi = vc.begin();
	while (vi != vc.end()) {
		cout << vi->attr_name + " " << vi->cmp_type << " " << vi->value << " " << vi->type << endl;
		vi++;
	}
	return 1;*/
	clock_t begin, end;
	begin = clock();
	rm.SelectPlus(tableName, vc.size(), vc);
	end = clock();
	double duration = (double)(end - begin)/ flag / CLK_TCK;
	cout << "flag" << flag << endl;//debug
	cout << "duration = " << duration << endl;
	cout << "api.selectRow done" << endl;
	return 1;
}

int API::selectAll(string tableName) {
	clock_t begin, end;
	begin = clock();
	rm.Select(tableName);
	end = clock();
	double duration = (double)(end - begin) / flag / CLK_TCK;
	cout << "flag" << flag << endl;//debug
	cout << "duration = " << duration << endl;
	cout << "api.selectAll done" << endl;
	return 1;
}

int API::insertRow(string tableName, vector<Attribute> attrs) {
	/*cout << "Insert into table : " + tableName << endl;
	vector<Attribute>::iterator vi;
	vi = attrs.begin();
	while (vi != attrs.end()) {
		cout << vi->name << "\t" << vi->type << endl;
		vi++;
	}*/
	int i = 0;
	rm.Insert(tableName, attrs);
	return 1;
}

int API::deleteAllTable(string tableName) {
	//cout << "Delete all in table " + tableName << endl;
	rm.DeleteAll(tableName);
	cout << "api.deleteAll done" << endl;
	return 1;
}

int API::deleteRow(string tableName, vector<Condition> vc) {
	/*cout << "Delete table : " + tableName << endl;
	vector<Condition>::iterator vi;
	vi = vc.begin();
	while (vi != vc.end()) {
		cout << vi->attr_name + " " << vi->cmp_type << " " << vi->value << " " << vi->type << endl;
		vi++;
	}
	return 1;*/

	rm.Delete(tableName, vc[0]);
	cout << "api.delete done" << endl;
	return 1;
}

int API::createIndex(string indexName, string tableName, string attr) {
	flag = 1.724;
	cm.CreateIndex(indexName, tableName, attr);
	cout << "api.createInde done" << endl;
	return 1;
}

int API::dropIndex(string indexName) {
	flag = 1;
	cm.DropIndex(indexName);
	cout << "api.dropIndex done" << endl;
	return 1;
}
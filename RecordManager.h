#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include "table.h"
#include"ALU.h"
#include"CatalogManager.h"
#include"condition.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#define tableFileName "_TABLE_MESSAGE_"

using namespace std;

class Record
{
public:
	//RecordManager() {}
	//创建表
	int CreateTable(Table NewTable);
	//删除表
	int DropTable(string tableName);
	//插入元组
	int Insert(string TableName, vector<Attribute> tuple);
	//删除元组
	int Delete(string TableName, Condition condition);
	//清空元组
	int DeleteAll(string TableName);
	//查找数据量
	int Record::FindNum(string TableName);
	//无条件选择
	int Select(string TableName);
	//多条件选择
	int SelectPlus(string TableName, int times, vector<Condition> conditions);
	//查找表是否存在
	int Record::FindTable(string tableName);
};

extern class Catalog cm;

#endif

#ifndef CATALOGMANAGER_H
#define CATALOGMANAGER_H

#include "table.h"
#include"ALU.h"
#include"RecordManager.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#define tableFileName "_TABLE_MESSAGE_"
#define indexFileName "_INDEX_MESSAGE_"

using namespace std;



class Index
{
public:
	string indexName;
	string tableName;
	string attrName;
};

class Catalog
{
public:
	//创建表
	int CreateTable(Table NewTable);
	//删除表信息
	int DeleteTable(string tableName);
	//查找表信息
	Table findAllColumn(string tableName);
	//创建索引
	int CreateIndex(string indexName, string tableName, string attrName);
	//删除索引
	int DropIndex(string indexName);
	//查找索引
	int FindIndex(string tableName, string attrName);
	//初始
	int InitTable();
	//写表头
	int WriteTableHead(fstream & fout, int & TableHead);
	//索引文件初始化
	int InitIndex();
};

extern class Record rm;

#endif

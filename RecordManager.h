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
	//������
	int CreateTable(Table NewTable);
	//ɾ����
	int DropTable(string tableName);
	//����Ԫ��
	int Insert(string TableName, vector<Attribute> tuple);
	//ɾ��Ԫ��
	int Delete(string TableName, Condition condition);
	//���Ԫ��
	int DeleteAll(string TableName);
	//����������
	int Record::FindNum(string TableName);
	//������ѡ��
	int Select(string TableName);
	//������ѡ��
	int SelectPlus(string TableName, int times, vector<Condition> conditions);
	//���ұ��Ƿ����
	int Record::FindTable(string tableName);
};

extern class Catalog cm;

#endif

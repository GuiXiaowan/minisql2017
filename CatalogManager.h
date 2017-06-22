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
	//������
	int CreateTable(Table NewTable);
	//ɾ������Ϣ
	int DeleteTable(string tableName);
	//���ұ���Ϣ
	Table findAllColumn(string tableName);
	//��������
	int CreateIndex(string indexName, string tableName, string attrName);
	//ɾ������
	int DropIndex(string indexName);
	//��������
	int FindIndex(string tableName, string attrName);
	//��ʼ
	int InitTable();
	//д��ͷ
	int WriteTableHead(fstream & fout, int & TableHead);
	//�����ļ���ʼ��
	int InitIndex();
};

extern class Record rm;

#endif

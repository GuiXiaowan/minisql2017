#include"RecordManager.h"

//创建表
int Record::CreateTable(Table NewTable)
{
	ofstream fout;
	fout.open(NewTable.tableName, ios::out);

	//if (FindTable(NewTable.tableName) == 0) {
	//	cout << "The table is already exist!" << endl;
	//	return 1;
	//}

	if (fout) {
		fout << 0 << endl;					//初始0个记录
		//fout << NewTable.RecordLength << endl;	//记录长度
		fout.close();
	}
	else return 1;
	return 0;
}
//删除表
int Record::DropTable(string tableName)
{
	if (FindTable(tableName) == 1) {
		cout << "The table is not exist!" << endl;
	}
	ofstream fout(tableName);
	if (fout) {
		fout.close();
	}
	remove(&tableName[0]);

	return 0;
}
//插入新数据
int Record::Insert(string TableName,vector<Attribute> tuple)
{
	string Sum;
	string outResult;
	string result;
	string uniqueValue;
	Table table;
	int point;
	int tupleNum;
	int i, j;
	int flag=0;

	table = cm.findAllColumn(TableName);

	ifstream fi(TableName, ios::in);//只读打开文件
	if (fi)//判断打开的文件是否成功
	{
		ostringstream os;
		os << fi.rdbuf();//把所有内容送到ostringstream中
		result += os.str();
		point = 0;//strstr(os,tableName);

		//检查primary key 和 unique 冲突
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		point++;
		tupleNum = StrtoNum(Sum);
		for (i = 0; i < tupleNum; i++) {
			for (j = 0; j < table.attrNum; j++) {
				uniqueValue = "";
				while (result[point] != ' ') {
					uniqueValue += result[point];
					point++;
				}
				point++;
				if (uniqueValue ==tuple[j].name && table.attributes[j].isUnique==1) {
					cout << "Not Unique！";
					return 1;
				}
			}
			point++;			
		}

		//无unique冲突 插入数据
		point = 0;
		Sum = "";
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		//cout << Sum << endl;
		outResult = AddSum(Sum, Sum.size());
		//cout << point << endl;
		//outResult += "\n";
		outResult += &(result[point]);
		//cout << table.attrNum << endl;
		for (i = 0; i < table.attrNum; i++) {
			//cout << tuple[i].name << endl;
			outResult += tuple[i].name;
			outResult += ' ';
		}		
		outResult += '\n';
	}
	else {
		cerr << "Record : Insert tuple error!" << endl;
		return -1; 
	}
	fi.close();

	ofstream fo(TableName, ios::out);//写打开文件
	fo << outResult;
	fo.close();

	//success
	return 0;
}
//删除个别数据
int Record::Delete(string TableName, Condition condition)
{
	Table table;

	table = cm.findAllColumn(TableName);

	string result;
	string outResult;
	int point;
	int deleteNum;
	string middle;	
	string Sum;
	int tupleNum=0;
	//string outResult;
	int i, j;
	int attrpoint;
	vector<Attribute> tuple;
	Attribute attrStr;

	for (i = 0; i < table.attrNum; i++) {
		if (table.attributes[i].name == condition.attr_name) break;
	}
	attrpoint = i;

	ifstream fi(TableName, ios::in);//只读打开文件
	if (fi)//判断打开的文件是否成功
	{
		ostringstream os;
		os << fi.rdbuf();//把所有内容送到ostringstream中
		result += os.str();

		point = 0;
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		point++;
		tupleNum = StrtoNum(Sum);
		//cout << tupleNum << endl;
		for (i = 0; i < tupleNum; i++) {
			for (j = 0; j < table.attrNum; j++) {
				attrStr.name = "";
				while (result[point] != ' ') {
					attrStr.name += result[point];
					point++;
				}
				point++;
				tuple.push_back(attrStr);
			}
			point++;
			//cout << tuple[attrpoint].name << ' ' << condition.value << endl;
			switch (condition.cmp_type) {
			case 0:
			{
				if (tuple[attrpoint].name != condition.value) {
					for (j = 0; j < table.attrNum; j++) {
						middle += tuple[j].name;
						middle += ' ';
					}
					middle += '\n';
				}
				else tupleNum--;
				tuple.clear();
				break;
			}
			case 1:
			{
				if (tuple[attrpoint].name == condition.value) {
					for (j = 0; j < table.attrNum; j++) {
						middle += tuple[j].name;
						middle += ' ';
					}
					middle += '\n';
				}
				else tupleNum--;
				tuple.clear();
				break;
			}
			case 2:
			{
				if (tuple[attrpoint].name >= condition.value) {
					for (j = 0; j < table.attrNum; j++) {
						middle += tuple[j].name;
						middle += ' ';
					}
					middle += '\n';
				}
				else tupleNum--;
				tuple.clear();
				break;
			}
			case 3:
			{
				if (tuple[attrpoint].name <= condition.value) {
					for (j = 0; j < table.attrNum; j++) {
						middle += tuple[j].name;
						middle += ' ';
					}
					middle += '\n';
				}
				else tupleNum--;
				tuple.clear();
				break;
			}
			case 4:
			{
				if (tuple[attrpoint].name < condition.value) {
					for (j = 0; j < table.attrNum; j++) {
						middle += tuple[j].name;
						middle += ' ';
					}
					middle += '\n';
				}
				else tupleNum--;
				tuple.clear();
				break;
			}
			case 5:
			{
				if (tuple[attrpoint].name > condition.value) {
					for (j = 0; j < table.attrNum; j++) {
						middle += tuple[j].name;
						middle += ' ';
					}
					middle += '\n';
				}
				else tupleNum--;
				tuple.clear();
				break;
			}
			}

		}
		outResult += numtoStr(tupleNum);
		outResult += " \n";
		outResult += middle;
	}
	else return -1;
	fi.close();	

	ofstream fo(TableName, ios::out);//写打开文件
	fo << outResult;
	fo.close();

	//success
	return 0;
}
//删除所有数据
int Record::DeleteAll(string TableName)
{
	string outResult;
	outResult = "0\n";

	ofstream fo(TableName, ios::out);//写打开文件
	fo << outResult;
	fo.close();
	return 0;
}
//查找数据量
int Record::FindNum(string TableName)
{
	string Sum;
	string outResult;
	string result;
	string uniqueValue;
	Table table;
	int point;
	int tupleNum;
	int i, j;
	int flag = 0;

	ifstream fi(TableName, ios::in);//只读打开文件
	if (fi)//判断打开的文件是否成功
	{
		ostringstream os;
		os << fi.rdbuf();//把所有内容送到ostringstream中
		result += os.str();
		point = 0;
		Sum = "";
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}

		return StrtoNum(Sum);
	}
		
}
//全选
int Record::Select(string TableName)
{
	Table table;
	//int flag2 = 0;

	table = cm.findAllColumn(TableName);

	string result;
	int point;
	string Sum;
	int tupleNum;
	int flag;
	int i, j, k;
	int attrpoint[32];
	vector<Attribute> tuple;
	Attribute attrStr;

	ifstream fi(TableName, ios::in);//只读打开文件
	if (fi)//判断打开的文件是否成功
	{
		ostringstream os;
		os << fi.rdbuf();//把所有内容送到ostringstream中
		result += os.str();

		point = 0;//strstr(os,tableName);
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		point++;
		tupleNum = StrtoNum(Sum);
		if (tupleNum == 0) cout << "No record!" << endl;

		for (i = 0; i < tupleNum; i++) {
			flag = 0;
			for (j = 0; j < table.attrNum; j++) {
				attrStr.name = "";
				while (result[point] != ' ') {
					attrStr.name += result[point];
					point++;
				}
				point++;
				tuple.push_back(attrStr);
			}
			point++;
			for (j = 0; j < table.attrNum; j++) {
				cout << tuple[j].name << '\t';
			}
			cout << endl;
			tuple.clear();
		}
	}
	else return -1;
	fi.close();
	return 0;
}
//多条件查询
int Record::SelectPlus(string TableName,int times,vector<Condition> conditions)
{
	Table table;
	/*cout << times << endl;
	cout << conditions[0].attr_name << endl;
	cout << conditions[0].cmp_type << endl;
	cout << conditions[0].value << endl;*/
	table = cm.findAllColumn(TableName);
	int flag2 = 0;

	string result;
	int point;
	string Sum;
	int tupleNum;
	int flag;
	int i, j, k;
	int attrpoint[32];
	vector<Attribute> tuple;
	Attribute attrStr;

	for (i = 0; i < table.attrNum; i++) {
		for (j = 0; j < times; j++) {
			if (table.attributes[i].name == conditions[j].attr_name) { attrpoint[j] = i; }
		}

	}	

	ifstream fi(TableName, ios::in);//只读打开文件
	if (fi)//判断打开的文件是否成功
	{
		ostringstream os;
		os << fi.rdbuf();//把所有内容送到ostringstream中
		result += os.str();

		point = 0;//strstr(os,tableName);
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		point++;
		tupleNum = StrtoNum(Sum);


		for (i = 0; i < tupleNum; i++) {
			flag = 0;
			for (j = 0; j < table.attrNum; j++) {
				attrStr.name = "";
				while (result[point] != ' ') {
					attrStr.name += result[point];
					point++;
				}
				point++;
				tuple.push_back(attrStr);
			}
			point++;
			for (j = 0; j < times; j++) {
				switch (conditions[j].cmp_type) {
				case 0: {
					if (tuple[attrpoint[j]].name == conditions[j].value) {
						flag++;
					}
					break;
				}
				case 1: {
					if (tuple[attrpoint[j]].name != conditions[j].value) {
						flag++;
					}
					break;
				}
				case 2: {
					if (tuple[attrpoint[j]].name < conditions[j].value) {
						flag++;
					}
					break;
				}
				case 3: {
					if (tuple[attrpoint[j]].name > conditions[j].value) {
						flag++;
					}
					break;
				}
				case 4: {
					if (tuple[attrpoint[j]].name >= conditions[j].value) {
						flag++;
					}
					break;
				}
				case 5: {
					if (tuple[attrpoint[j]].name <= conditions[j].value) {
						flag++;
					}
					break;
				}
				}
			}
			if (flag == times) {
				for (j = 0; j < table.attrNum; j++) {
					cout << tuple[j].name << '\t';
				}
				flag2 = 1;
				cout << endl;
			}
			tuple.clear();
		}
	}
	else return -1;

	if (flag2 == 0) cout << "No record!" << endl;
	fi.close();
	return 0;
	
}
//查找表是否存在
int Record::FindTable(string tableName)
{
	ifstream fin(tableName);
	if (fin) {
		fin.close();
		return 0;
	}
	else return 1;
}

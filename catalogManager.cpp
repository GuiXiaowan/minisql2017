#include"CatalogManager.h"

//�����±�
int Catalog::CreateTable(Table NewTable)
{
	string Sum;
	string outResult;
	string result;
	int point;
	int i;

	if (rm.FindTable(NewTable.tableName) == 0) {
		cout << "The table is already exist!" << endl;
		return 1;
	}

	ifstream fi(tableFileName,ios::in);//ֻ�����ļ�
	if (fi)//�жϴ򿪵��ļ��Ƿ�ɹ�
	{
		ostringstream os;
		os << fi.rdbuf();//�����������͵�ostringstream��
		result += os.str();
		point = 0;//strstr(os,tableName);
		while (result[point]>='0'&&result[point] <= '9') {
			Sum += result[point];
			point++; 
		}
		//cout << "1" << endl;
		outResult += AddSum(Sum, Sum.size());
		//outResult += "\n";
		outResult += &(result[point]);
		//cout << "2" << endl;
		outResult += NewTable.tableName;
		outResult += ' ';
		outResult += NewTable.primaryKey;
		outResult += ' ';
		outResult += numtoStr(NewTable.attrNum);
		outResult += ' ';
		//cout << "3" << endl;
		//cout << NewTable.attrNum << endl;
		for (i = 0; i<NewTable.attrNum; i++) {
			//cout << NewTable.attributes[i].name << endl;
			outResult += NewTable.attributes[i].name;
			outResult += ' ';
			outResult += numtoStr(NewTable.attributes[i].type);
			outResult += ' ';
			if (NewTable.attributes[i].isUnique == true)outResult += "1";
			else outResult += "0";
			outResult += ' ';
		}
		//cout << "4" << endl;
		outResult += "\n";
	}
	else {
		cerr << "Catalog : CreateTable Open file error!" << endl;
		//return -1; 
	}
	fi.close();

	ofstream fo(tableFileName, ios::out);//д���ļ�
	fo << outResult;
	fo.close();

	//success
	return 0;
}
//ɾ����
int Catalog::DeleteTable(string tableName)
{
	string Sum;
	string outResult;
	string result;
	string attrNumStr;
	int point;
	int point2;
	int i;
	int attrNum;

	if (rm.FindTable(tableName) == 1) {
		cout << "The table is not exist!" << endl;
		return 1;
	}

	ifstream fi(tableFileName, ios::in);//ֻ�����ļ�
	if (fi)//�жϴ򿪵��ļ��Ƿ�ɹ�
	{
		ostringstream os;
		os << fi.rdbuf();//�����������͵�ostringstream��
		result += os.str();
		point = 0;//strstr(os,tableName);
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		outResult += SubSum(Sum, Sum.size());
		//outResult += "\n";
		point2 = result.find(tableName);
		for (i = point; i < point2; i++) outResult += result[i];
		point = point2+tableName.size() + 1;
		while (result[point] != ' '&&result[point] != '\0') {
			point++;
		}	//��primary key����
		point++;
		while (result[point] != ' '&&result[point] != '\0') {
			attrNumStr += result[point];
			point++;
		} //������Ŀ��
		point++;
		attrNum = StrtoNum(attrNumStr);
		//Attribute attr;
		//string strtoNum;
		for (i = 0; i<attrNum; i++) {
			while (result[point] != ' '&&result[point] != '\0') {
				point++;
			}
			point++;
			while (result[point] != ' '&&result[point] != '\0') {
				point++;
			}
			point++;point++;point++;
		}
		point++;
		outResult += &(result[point]);
	}
	else {
		cerr << "Catalog : CreateTable Open file error!" << endl;
		//return -1; 
	}
	fi.close();

	ofstream fo(tableFileName, ios::out);//д���ļ�
	fo << outResult;
	fo.close();

	//success
	return 0;
}
//���ұ����Ϣ
Table Catalog::findAllColumn(string tableName)
{
	Table tableMessage;
	
	string result = "";
	string attrNumStr = "";
	//string strtoNum = "";
	int point;
	fstream fio;
	int i;

	//fio.open(tableFileName, ios::in | ios::out);
	ifstream in(tableFileName, ios::in);//ֻ�����ļ�
	if (in)//�жϴ򿪵��ļ��Ƿ�ɹ�
	{
		ostringstream os;
		os << in.rdbuf();//�����������͵�ostringstream��
		result = os.str();
		point = result.find(tableName);
		tableMessage.tableName = tableName;
		point += tableName.size() + 1;
		while (result[point] != ' '&&result[point] != '\0') {
			tableMessage.primaryKey += result[point];
			point++;
		}
		point++;
		while (result[point] != ' '&&result[point] != '\0') {
			attrNumStr += result[point];
			point++;
		}
		point++;
		tableMessage.attrNum = StrtoNum(attrNumStr);
		Attribute attr;
		string strtoNum;
		for (i = 0; i<tableMessage.attrNum; i++) {			
			while (result[point] != ' '&&result[point] != '\0') {
				attr.name += result[point];
				point++;
			}
			point++;
			while (result[point] != ' '&&result[point] != '\0') {
				strtoNum += result[point];
				point++;
			}
			point++;
			attr.type = StrtoNum(strtoNum);
			//attr.isUnique = result[point] - '0';
			if (result[point] == '0')attr.isUnique = false;
			else attr.isUnique = true;
			point++; point++;
			tableMessage.attributes.push_back(attr);
			strtoNum = "";
			attr.name = "";
		}
	}
	else {
		cerr << "Catalog : FindAllColumn Open file error!" << endl;
		//return -1; 
	}

	return tableMessage;
}
//Index���� ɾ�� ����
int Catalog::CreateIndex(string indexName, string tableName, string attrName)
{
	Index index;
	string Sum;
	string outResult;
	string result;
	int point;
	int i;
	index.indexName = indexName;
	index.tableName = tableName;
	index.attrName = attrName;

	/*if (rm.FindTable(index.indexName) == 0) {
		cout << "The index is already exist!" << endl;
		return 1;
	}*/

	ifstream fi(indexFileName, ios::in);//ֻ�����ļ�
	if (fi)//�жϴ򿪵��ļ��Ƿ�ɹ�
	{
		ostringstream os;
		os << fi.rdbuf();//�����������͵�ostringstream��
		result += os.str();
		point = 0;//strstr(os,tableName);
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		outResult += AddSum(Sum, Sum.size());
		//outResult += "\n";
		outResult += &(result[point]);
		outResult += index.indexName;
		outResult += ' ';
		outResult += index.tableName;
		outResult += ' ';
		outResult += index.attrName;
		outResult += ' ';
		outResult += "\n";
	}
	else {
		cerr << "Catalog : CreateTable Open file error!" << endl;
		//return -1; 
	}
	fi.close();

	ofstream fo(indexFileName, ios::out);//д���ļ�
	fo << outResult;
	fo.close();

	//success
	return 0;
}
//ɾ������
int Catalog::DropIndex(string indexName)
{
	string Sum;
	string outResult;
	string result;
	string attrNumStr;
	int point;
	int point2;
	int i;
	int attrNum;

	/*if (rm.FindTable(tableName) == 1) {
		cout << "The table is not exist!" << endl;
		return 1;
	}*/

	ifstream fi(indexFileName, ios::in);//ֻ�����ļ�
	if (fi)//�жϴ򿪵��ļ��Ƿ�ɹ�
	{
		ostringstream os;
		os << fi.rdbuf();//�����������͵�ostringstream��
		result += os.str();
		point = 0;//strstr(os,tableName);
		while (result[point] >= '0'&&result[point] <= '9') {
			Sum += result[point];
			point++;
		}
		outResult += SubSum(Sum, Sum.size());
		//outResult += "\n";
		point2 = result.find(indexName);
		for (i = point; i < point2; i++) outResult += result[i];
		point = point2 + indexName.size() + 1;
		while (result[point] != ' '&&result[point] != '\0') {
			point++;
		}	//��tablename����
		point++;
		while (result[point] != ' '&&result[point] != '\0') {
			point++;
		}	//��attrname����
		point++; 
		point++;
		outResult += &(result[point]);
	}
	else {
		cerr << "Catalog : CreateTable Open file error!" << endl;
		//return -1; 
	}
	fi.close();

	ofstream fo(indexFileName, ios::out);//д���ļ�
	fo << outResult;
	fo.close();

	//success
	return 0;
}
//���������Ƿ����
int Catalog::FindIndex(string tableName, string attrName)
{
	if (attrName == findAllColumn(tableName).primaryKey) return 0;//PK
	else {
		Table indexMessage;

		string result = "";
		string attrNumStr = "";
		string indexAttr;
		//string strtoNum = "";
		int point = 0;
		fstream fio;
		int i;

		//fio.open(tableFileName, ios::in | ios::out);
		ifstream in(indexFileName, ios::in);//ֻ�����ļ�
		if (in)//�жϴ򿪵��ļ��Ƿ�ɹ�
		{
			ostringstream os;
			os << in.rdbuf();//�����������͵�ostringstream��
			result = os.str();
			while (1) {
				indexAttr = "";
				point = result.find(tableName, point);
				if (point == -1) return -1;	//����û�г�pk���index
				point += tableName.size() + 1;
				while (result[point] != ' '&&result[point] != '\0') {
					indexAttr += result[point];
					point++;
				}
				if (indexAttr == attrName) return 0;
			}
		}
	}
}
//��ʼ����
int Catalog::InitTable()
{
	fstream fout;
	fout.open(tableFileName, ios::out);

	int TableHead=0;
	WriteTableHead(fout, TableHead);

	fout.close();

	return 0;
}
//д��ͷ��Ϣ
int Catalog::WriteTableHead(fstream & fout, int & TableHead)
{
	//fout.write((char *)&(TableHead), sizeof(int));
	fout << TableHead << endl;
	//fout.flush();

	return 0;
}
//�����ļ���ʼ��
int Catalog::InitIndex()
{
	fstream fout;
	fout.open(indexFileName, ios::out);

	int TableHead = 0;
	WriteTableHead(fout, TableHead);

	fout.close();

	return 0;
}

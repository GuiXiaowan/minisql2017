#include "interpreter.h"
#include "API.h"
#include "attribute.h"
#include "condition.h"
#include "table.h"
#include <iostream>
#include <string>

using namespace std;

int Interpreter::interpret() {//返回0时表示一次操作已完成(不困对错)，返回1表示quit命令,返回2表示文件
	int cursor = 0;
	int &a = cursor;
	string word;
	API api;
	vector<string> vc;
	vector<string>::iterator vi;

	vc = analysis(cmd);

	if (vc.size() == 0) {//语法错误
		return 0;
	}
	if (vc[0] == "create") {//create index/table ....
		/*just for dubugging
		vi = vc.begin();
		while (vi != vc.end()) {
			cout << *vi << endl;
			vi++;
		}
		*/
		vector<Attribute> attrs;
		Attribute attr;
		Table tb;

		vi = vc.begin();
		vi++;
		if (*vi == "index") {
			vi++;
			string indexName;
			string tableName;
			string attr;
			indexName = *vi;
			vi++;
			tableName = *vi;
			vi++;
			attr = *vi;
			api.createIndex(indexName, tableName, attr);
		}
		else {
			vi++;
			tb.tableName = *vi;
			vi++;
			while (vi != vc.end()) {
				if (*vi == "primary") {
					vi++;
					tb.primaryKey = *vi;
				}
				else {
					attr.name = *vi;//属性名
					vi++;
					if (*vi == "-1") {
						attr.type = -1;
					}
					else if (*vi == "0") {
						attr.type = 0;
					}
					else {
						attr.type = STN(*vi, 1);
					}//type
					vi++;
					if (*vi == "isUnique") {
						attr.isUnique = true;
					}
					else {
						attr.isUnique = false;
					}//unique
					attrs.push_back(attr);
				}
				vi++;
			}
			tb.attributes = attrs;
			cout << "Table " + tb.tableName + " has been created." << endl;
			tb.attrNum = attrs.size();
			api.createTable(tb);
			//tb.showTable();//dubug
		}
		return 0;
	}
	else if (vc[0] == "select") {
		/*vi = vc.begin();
		while (vi != vc.end()) {
			cout << *vi << endl;
			vi++;
		}
		just for debug*/
		Condition cd;
		vector<Condition> vcd;
		string tableName;

		vi = vc.begin();
		vi++; vi++;
		tableName = vc[1];
		if (vc.size() == 2) {
			api.selectAll(tableName);
			return 0;
		}
		while (vi != vc.end()) {
			cd.attr_name = *vi;
			vi++;
			cd.cmp_type = cd.convert(*vi);
			vi++;
			cd.value = *vi;
			vi++;
			if (*vi == "-1") {
				cd.type = -1;
			}
			else if (*vi == "0") {
				cd.type = 0;
			}
			else {
				cd.type = STN(*vi, 1);
			}
			vcd.push_back(cd);
			vi++;
		}
		api.selectRow(tableName, vcd);
		return 0;
	}
	else if (vc[0] == "insert") {
		/*vi = vc.begin();
		while (vi != vc.end()) {
		cout << *vi << endl;
		vi++;
		}
		//just for debug*/
		vi = vc.begin();
		vi++;
		string tableName = *vi;
		Attribute attr;
		vector<Attribute> attrs;
		vi++;
		while (vi != vc.end()) {
			attr.name = *vi;
			vi++;
			attr.type = STN((*vi), 1);
			attrs.push_back(attr);
			vi++;
		}
		api.insertRow(tableName, attrs);
		return 0;
	}
	else if (vc[0] == "delete") {
		/*vi = vc.begin();
		while (vi != vc.end()) {
		cout << *vi << endl;
		vi++;
		}
		//just for debug*/
		vi = vc.begin();
		vi++;
		string tableName = *vi;
		vi++;
		if (vi == vc.end()) {
			api.deleteAllTable(tableName);
		}
		else {
			Condition cd;
			vector<Condition> vcd;
			while (vi != vc.end()) {
				cd.attr_name = *vi;
				vi++;
				cd.cmp_type = cd.convert(*vi);
				vi++;
				cd.value = *vi;
				vi++;
				if (*vi == "-1") {
					cd.type = -1;
				}
				else if (*vi == "0") {
					cd.type = 0;
				}
				else {
					cd.type = STN(*vi, 1);
				}
				vcd.push_back(cd);
				vi++;
			}
			api.deleteRow(tableName, vcd);
		}
		return 0;
	}
	else if (vc[0] == "drop") {
		string str;
		if (vc[1] == "table") {
			str = vc[2];
			api.dropTable(str);
		}
		else {
			str = vc[2];
			api.dropIndex(str);
		}
		return 0;
	}
	else if (vc[0] == "quit") {
		return 1;
	}
	else if (vc[0] == "execfile") {
		cout << "File Read Mode:\t" << vc[1] << endl;
		fileName = vc[1];
		return 2;
	}
}

void Interpreter::setCommand(string str) {
	cmd = str;
}

bool Interpreter::punctuationCheck(char ch, int a) {
	char s[3];
	int top = -1;

	if (ch == '\'') {//用来查两个‘’之间有没有其他非法字符，或者是否有对应的‘’
		a++;
		while (a < cmd.length()) {
			if (cmd[a] == ch)
				return true;
			else if (!((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_')))
				break;
			a++;
		}
		return false;
	}
	else if (ch == '(') {//只来查找有没有多一个少一个括号
		s[++top] = ch;
		while (a < cmd.length()) {
			if (top >= 2) {
				cout << "Stack Overflow!" << endl;
				return false;
			}
			if (cmd[a] == '(')
				s[++top] = ch;
			else if (cmd[a] == ')')
				s[top--] = '\0';
			a++;
		}
		if (top > -1)
			return false;
		else
			return true;
	}
	else {
		cout << "Don't check this character!" << endl;
		return false;
	}
}

int Interpreter::STN(string str, int num) {//字符串转数字用clear
	strtonum << str;
	strtonum >> num;
	strtonum.clear();
	return num;
}

float Interpreter::STN(string str, float num) {
	strtonum << str;
	strtonum >> num;
	strtonum.clear();
	return num;
}

string Interpreter::NTS(int num) {//数字转字符串用ss.str("")
	numtostr << num;
	string temp = numtostr.str();
	numtostr.str("");
	return temp;
}

string Interpreter::NTS(float num) {
	numtostr << num;
	string temp = numtostr.str();
	numtostr.str("");
	return temp;
}

vector<string> Interpreter::analysis(string cmd) {
	string word;
	int cursor = 0;
	int &a = cursor;
	vector<string> vc;//

	word = getWord(a);
	if (word == "create") {// create table tableName 
		vc.push_back(word);
		word = getWord(a);
		if (word == "index") {
			vc.push_back("index");
			string indexName = getWord(a);
			string tableName;
			word = getWord(a);
			if (word != "on") {
				throwError(word);
				vc.clear();
				return vc;
			}
			tableName = getWord(a);
			word = getWord(a);
			if (word != "(") {//syntax error
				throwError(word);
				vc.clear();
				return vc;
			}
			if (!punctuationCheck('(', a)) {
				cout << "Punctuation Check failed!" << endl;
				vc.clear();
				return vc;
			}
			string attr = getWord(a);
			getWord(a);//)
			vc.push_back(indexName);
			vc.push_back(tableName);
			vc.push_back(attr);
			return vc;
		}
		else if(word != "table") {// syntax error template
			throwError(word);
			vc.clear();
			return vc;
		}
		vc.push_back("table");
		word = getWord(a);
		vc.push_back(word);//table name
		word = getWord(a);
		if (word != "(") {//syntax error
			throwError(word);
			vc.clear();
			return vc;
		}
		if (!punctuationCheck('(', a)) {
			cout << "Punctuation Check failed!" << endl;
			vc.clear();
			return vc;
		}
		while (word != ")") {//最大的那个括号，假设括号内部暂无语法错误
			word = getWord(a);
			if (word == "primary") {//primary key (id)
				getWord(a);//Key
				getWord(a);//(
				word = getWord(a);//name
				getWord(a);//)
				vc.push_back("primary");
				vc.push_back(word);
				word = getWord(a);//下一次循环
			}
			else {//普通的属性定义
				string name;
				name = word;//属性名
				vc.push_back(name);//name
				word = getWord(a);//类型名
				if (word == "float") {
					vc.push_back("-1");
				}
				else if (word == "int") {
					vc.push_back("0");
				}
				else {
					getWord(a);//(
					word = getWord(a);//数字，代表char多少
					vc.push_back(word);
					getWord(a);//)
				}
				word = getWord(a);//, or )， or unique
				if (word == "unique") {
					vc.push_back("isUnique");
					word = getWord(a);//, or )
				}
				else
					vc.push_back("notUnique");
			}
		}
		return vc;
	}
	else if (word == "select") {// select tableName aaa > 16 0 bbb < 1.22 -1 ttt = str 3
		vc.push_back(word);
		word = getWord(a);
		if (word != "*") {
			throwError(word);
			vc.clear();
			return vc;
		}
		word = getWord(a);//from
		if (word != "from") {
			throwError(word);
			vc.clear();
			return vc;
		}
		word = getWord(a);//table
		vc.push_back(word);
		word = getWord(a);//where
		if (word == "") {
			return vc;
		}
		if (word != "where") {
			throwError(word);
			vc.clear();
			return vc;
		}
		while (a < cmd.length()) {
			word = getWord(a);
			vc.push_back(word);//attr_name
			word = getWord(a);
			vc.push_back(word);//op
			word = getWord(a);
			if (word == "\'") {//字符串
				word = getWord(a);//value
				vc.push_back(word);
				vc.push_back(NTS((int)word.length()));//type
				getWord(a);//"'"
			}
			else {
				vc.push_back(word);//value
				if (word.find(".") == string::npos) {//int
					vc.push_back("0");
				}
				else
					vc.push_back("-1");
			}
			word = getWord(a);//and
		}
		return vc;
	}
	else if (word == "insert") {// insert tableName v1 t1 v2 t2...
		vc.push_back(word);
		string tableName;

		word = getWord(a);
		if (word != "into") {
			throwError(word);
			vc.clear();
			return vc;
		}
		tableName = getWord(a);
		vc.push_back(tableName);
		word = getWord(a);
		if (word != "values") {
			throwError(word);
			vc.clear();
			return vc;
		}
		word = getWord(a);
		if (word != "(") {//syntax error
			throwError(word);
			vc.clear();
			return vc;
		}
		if (!punctuationCheck('(', a)) {
			cout << "Punctuation Check failed!" << endl;
			vc.clear();
			return vc;
		}
		while (word != ")") {
			word = getWord(a);
			if (word == "\'") {//string
				word = getWord(a);
				vc.push_back(word);
				vc.push_back(NTS((int)word.length()));
				getWord(a);//'
			}
			else {
				vc.push_back(word);
				if (word.find('.') == string::npos) {
					vc.push_back("0");
				}
				else
					vc.push_back("-1");
			}
			word = getWord(a);//, or )
		}
		return vc;
	}
	else if (word == "delete") {
		vc.push_back(word);
		word = getWord(a);
		if (word != "from") {
			throwError(word);
			vc.clear();
			return vc;
		}
		word = getWord(a);
		vc.push_back(word);//table name
		word = getWord(a);
		if (word == "") {
			return vc;
		}
		else {
			if (word != "where") {
				throwError(word);
				vc.clear();
				return vc;
			}
			while (a < cmd.length()) {
				word = getWord(a);
				vc.push_back(word);//attr_name
				word = getWord(a);
				vc.push_back(word);//op
				word = getWord(a);
				if (word == "\'") {//字符串
					word = getWord(a);//value
					vc.push_back(word);
					vc.push_back(NTS((int)word.length()));//type
					getWord(a);//"'"
				}
				else {
					vc.push_back(word);//value
					if (word.find(".") == string::npos) {//int
						vc.push_back("0");
					}
					else
						vc.push_back("-1");
				}
				word = getWord(a);//and
			}
		}
		return vc;
	}
	else if (word == "drop") {
		vc.push_back(word);
		word = getWord(a);
		if (word == "table") {
			vc.push_back(word);
			word = getWord(a);
			vc.push_back(word);
		}
		else if (word == "index") {
			vc.push_back(word);
			word = getWord(a);
			vc.push_back(word);
		}
		else {
			throwError(word);
			vc.clear();
			return vc;
		}
		return vc;
	}
	else if (word == "quit") {
		vc.push_back(word);
		return vc;
	}
	else if (word == "execfile") {
		vc.push_back(word);
		string fileName;
		fileName = getWord(a);
		vc.push_back(fileName);
		return vc;
	}
	else if (word == "") {
		return vc;
	}
	else {
		cout << "This command cannot be interpreted." << endl;
		vc.clear();
		return vc;
	}
}

string Interpreter::getWord(int &a) {
	int begin = 0, end = 0;
	while ((cmd[a] == ' ' || cmd[a] == '\t' || cmd[a] == '\n') && a < cmd.length())
		a++;
	begin = a;
	if (a == cmd.length()) {//全是空白字符
		return "";
	}
	while (true) {
		if (cmd[a] == '\'' || cmd[a] == '(' || cmd[a] == ')' || cmd[a] == ',') {//以特殊符号开头
			a++;
			end = a;
			break;
		}
		else if (cmd[a] == ' ' || cmd[a] == '\t' || cmd[a] == '\n' || a == cmd.length() - 1) {//不以以上特殊符号开头而走到结尾
			if (a == cmd.length() - 1) {
				a++;
				end = a;
			}
			else
				end = a;
			break;
		}
		else {//不以特殊符号开头，要检查结尾是否是特殊符号
			a++;
			if (cmd[a] == '\'' || cmd[a] == '(' || cmd[a] == ')' || cmd[a] == ',') {
				end = a;
				break;
			}
			a--;
		}
		a++;
	}
	//cout << cmd.substr(begin, end - begin) << endl;//debug
	return cmd.substr(begin, end - begin);
}

/*
create table student(name char(20), id char(20), age int, grade float);

create student(name char(20), id char(20), age int, grade float);
create table student(name char(20, id char(20), age int, grade float);

create table student2(
id int,
name char(12) unique,
score float unique,
primary key(grade),
grade int
);

drop table student;

select * from student2 where id > '10000';
select * from student2 where id > '10000' and grade <= 123.4 and name = 'Sam';

insert into student values ('12345678', 'wy', 22, 'M');

delete from student where sno = '88888888';

execfile student.txt;
execfile test1.txt;
*/
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Interpreter {
public:
	
	string fileName;
	string cmd;
	stringstream strtonum;
	stringstream numtostr;

	int STN(string str, int num);
	float STN(string str, float num);
	string NTS(int num);
	string NTS(float num);

	int interpret();//0, 1, 2
	vector<string> getWord(int &a, int flag);//�����ҳ�������Ϊ��ʼ�ͽ�β�����������
	vector<string> analysis(string cmd);
	string getWord(int &a);
	void setCommand(string str);
	void throwError(string comment) {
		cout << "Syntax Error : unexpected word \"" << comment << "\"" << endl;
	}
	Interpreter(string cmd){
		this->cmd = cmd;
	};
	bool punctuationCheck(char ch, int a);
	Interpreter(){};
};

#endif // !INTERPRETER_H

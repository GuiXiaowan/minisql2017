#include"ALU.h"

//×Ö·û´®×ªÊý×Ö
int StrtoNum(string SumStr)
{
	int i = 0;
	int SumNum = 0;
	int flag = 0;

	if (SumStr[0] == '-') flag = 1;
	else SumNum = SumNum * 10 + SumStr[0] - '0';
	for (i = 1;; i++) {
		if (SumStr[i]>='0'&&SumStr[i]<='9') SumNum = SumNum * 10 + SumStr[i] - '0';
		else break;
	}
	if (flag == 0)return SumNum;
	else return -SumNum;
}
//Êý×Ö×ª×Ö·û´®
string numtoStr(int num)
{
	string str;
	char temp;
	int i=0;
	int j = 0;
	int flag = 0;

	if (num < 0) {
		str += '-';
		i++;
		flag = 1;
		num = -num;
	}
	for (;; i++) {
		str += '0' + num % 10;
		num = num / 10;
		if (num == 0)break;
	}
	if(flag==0)
		for (; j < (i+1) / 2; j++) {
			temp = str[j];
			str[j] = str[i - j];
			str[i - j] = temp;
		}
	else {
		for(j=1; j <= i / 2; j++) {
			temp = str[j];
			str[j] = str[i - j + 1];
			str[i - j + 1] = temp;
		}
	}
	//str += '\0';

	return str;
}
//×Ö·û´®¼ÓÒ»
string AddSum(string sum, int length)
{
	string sumAfter = sum;
	int i = length-1;

	while (i != 0) {
		if (sumAfter[i] != '9') {
			sumAfter[i]++;
			return sumAfter;
		}
		else {
			sumAfter[i] = '0';
			i--;
		}
	}
	if (i == 0) {
		if (sumAfter[i] != '9') {
			sumAfter[i]++;
		}
		else {
			sumAfter[0] = '1';
			sumAfter += '0';
			//sumAfter[length+1] = '\0';
		}
	}

	return sumAfter;
}
//×Ö·û´®¼õÒ»
string SubSum(string sum, int length)
{
	string sumAfter = sum;
	int i = length - 1;
	int j;

	while (i != 0) {
		if (sumAfter[i] != '0') {
			sumAfter[i]--;
			break;
		}
		else {
			sumAfter[i] = '9';
			i--;
		}
	}
	if (i == 0) {
		if (sumAfter[i] != '1'||sumAfter[0]=='1'&&length==1) {
			sumAfter[i]--;
		}
		else {
			for (j = 0; j < length-1; j++) {
				sumAfter[j] = sumAfter[j + 1];
			}
			sumAfter[length - 1] = '\0';
		}
	}

	return sumAfter;
}
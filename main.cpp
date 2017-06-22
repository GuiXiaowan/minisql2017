#include <iostream>
#include <fstream>
#include "interpreter.h"
#include "API.h"
#include "attribute.h"
#include "minisql.h"

using namespace std;

void fileRead(string fileName);

Catalog cm;
Record rm;

int main(void) {
	string temp;
	int state = 0;
	cm.InitTable();
	cm.InitIndex();
	cout << "Welcome to minisql!" << endl;
	Interpreter inter;
	while (1) {
		if (state == 0) {
			cout << "minisql>>>";
			getline(cin, temp, ';');
			//cout << temp << endl;//debug
			inter.setCommand(temp);
			state = inter.interpret();
			if (state == 1) {//quit
				cout << "Goodbye!" << endl;
				break;
			}
			else if (state == 2) {
				fileRead(inter.fileName);
			}
			state = 0;
		}
	}

	return 0;
}

void fileRead(string fileName) {
	ifstream fin;
	Interpreter inter;
	int state;

	fin.open(fileName);
	if (!fin.is_open()) {//�ļ�δ��
		cout << "Opening file " << fileName << " failed.";
		cout << "switch to cmd mode, please enter 0, if you want to quit, please enter other numbers." << endl;
		cin >> state;
		if (state == 0) {
			return;
		}
		else {
			cout << "Goodbye!" << endl;
			exit(0);
		}
	}
	string temp;
	while (getline(fin, temp, ';')) {
		inter.setCommand(temp);
		state = inter.interpret();
		if (state == 1) {
			exit(0);
		}
		if (state == 2) {
			fileRead(inter.fileName);
		}
	}
	cout << "Script " + fileName + " has been executived successfully." << endl;
}

/*
create table student(name char(20), id char(20), age int, grade float);

create table student2(
id int,
name char(12) unique,
score float,
primary key(id)
);

insert into student2 values(1080100001,'name1',99);
insert into student2 values(1080100002,'name2',52.5);
insert into student2 values(1080100003,'name3',98.5);
insert into student2 values(1080100004,'name4',91.5);
insert into student2 values(1080100005,'name5',72.5);
insert into student2 values(1080100006,'name6',89.5);
insert into student2 values(1080100007,'name7',63);
insert into student2 values(1080100008,'name8',73.5);
insert into student2 values(1080100009,'name9',79.5);
insert into student2 values(1080100010,'name10',70.5);
insert into student2 values(1080100011,'name11',89.5);
insert into student2 values(1080100012,'name12',62);
insert into student2 values(1080100013,'name13',57.5);
insert into student2 values(1080100014,'name14',70.5);
insert into student2 values(1080100015,'name15',93.5);
insert into student2 values(1080100016,'name16',80);
insert into student2 values(1080100017,'name17',71.5);
insert into student2 values(1080100018,'name18',81.5);
insert into student2 values(1080100019,'name19',55);
insert into student2 values(1080100020,'name20',71.5);
insert into student2 values(1080100021,'name21',93.5);
insert into student2 values(1080100022,'name22',93.5);
insert into student2 values(1080100023,'name23',69.5);
insert into student2 values(1080100024,'name24',62.5);
insert into student2 values(1080100025,'name25',63);
insert into student2 values(1080100026,'name26',73.5);
insert into student2 values(1080100027,'name27',52);
insert into student2 values(1080100028,'name28',57.5);
insert into student2 values(1080100029,'name29',57.5);
insert into student2 values(1080100030,'name30',81.5);
insert into student2 values(1080100031,'name31',51.5);
insert into student2 values(1080100032,'name32',67.5);
insert into student2 values(1080100033,'name33',86);
insert into student2 values(1080100034,'name34',52);
insert into student2 values(1080100035,'name35',71.5);
insert into student2 values(1080100036,'name36',52.5);
insert into student2 values(1080100037,'name37',92);
insert into student2 values(1080100038,'name38',80.5);
insert into student2 values(1080100039,'name39',87);
insert into student2 values(1080100040,'name40',63.5);
insert into student2 values(1080100041,'name41',82.5);
insert into student2 values(1080100042,'name42',85.5);
insert into student2 values(1080100043,'name43',85.5);
insert into student2 values(1080100044,'name44',91);
insert into student2 values(1080100045,'name45',52.5);
insert into student2 values(1080100046,'name46',98.5);
insert into student2 values(1080100047,'name47',66.5);
insert into student2 values(1080100048,'name48',94.5);
insert into student2 values(1080100049,'name49',97);
insert into student2 values(1080100050,'name50',76.5);
insert into student2 values(1080100051,'name51',86.5);
insert into student2 values(1080100052,'name52',97);
insert into student2 values(1080100053,'name53',79.5);
insert into student2 values(1080100054,'name54',64.5);
insert into student2 values(1080100055,'name55',53.5);
insert into student2 values(1080100056,'name56',70.5);
insert into student2 values(1080100057,'name57',90);
insert into student2 values(1080100058,'name58',65.5);
insert into student2 values(1080100059,'name59',63);
insert into student2 values(1080100060,'name60',85.5);
insert into student2 values(1080100061,'name61',55);
insert into student2 values(1080100062,'name62',55);
insert into student2 values(1080100063,'name63',74.5);
insert into student2 values(1080100064,'name64',63);
insert into student2 values(1080100065,'name65',93);
insert into student2 values(1080100066,'name66',99);
insert into student2 values(1080100067,'name67',80.5);
insert into student2 values(1080100068,'name68',76.5);
insert into student2 values(1080100069,'name69',72.5);
insert into student2 values(1080100070,'name70',88.5);
insert into student2 values(1080100071,'name71',94);
insert into student2 values(1080100072,'name72',93.5);
insert into student2 values(1080100073,'name73',89);
insert into student2 values(1080100074,'name74',84);
insert into student2 values(1080100075,'name75',55.5);
insert into student2 values(1080100076,'name76',59.5);
insert into student2 values(1080100077,'name77',72);
insert into student2 values(1080100078,'name78',61.5);
insert into student2 values(1080100079,'name79',74);
insert into student2 values(1080100080,'name80',53.5);
insert into student2 values(1080100081,'name81',59.5);
insert into student2 values(1080100082,'name82',71.5);
insert into student2 values(1080100083,'name83',89.5);
insert into student2 values(1080100084,'name84',60.5);
insert into student2 values(1080100085,'name85',98.5);
insert into student2 values(1080100086,'name86',62);
insert into student2 values(1080100087,'name87',74.5);
insert into student2 values(1080100088,'name88',87.5);
insert into student2 values(1080100089,'name89',50.5);
insert into student2 values(1080100090,'name90',96.5);
insert into student2 values(1080100091,'name91',64);
insert into student2 values(1080100092,'name92',61.5);
insert into student2 values(1080100093,'name93',53);
insert into student2 values(1080100094,'name94',99.5);
insert into student2 values(1080100095,'name95',85);
insert into student2 values(1080100096,'name96',83.5);
insert into student2 values(1080100097,'name97',52.5);
insert into student2 values(1080100098,'name98',85.5);
insert into student2 values(1080100099,'name99',61);
insert into student2 values(1080100100,'name100',51);

select * from student2 where id > 1080100003;

drop table student;
*/
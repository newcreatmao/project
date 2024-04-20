#pragma once
#include<mysql.h>
#include<sstream>
#include<iostream>
using namespace std;

class Mysql {
private:
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	bool Link_flag;
public:
	void Connection(const char* host,const char* use,const char* passwd,const char* database,int port);
	void Show_Table_Data(const char* table);
	void Call_Message(const char* command);
	void Get_Table_struct(const char* table);
	~Mysql();
};
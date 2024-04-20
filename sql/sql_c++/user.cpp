#include "user.hpp"

void Mysql::Connection(const char* host,const char* use, const char* passwd,const char* database,int port) {
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	if (mysql_real_connect(&mysql,host,use,
		passwd,database, port, NULL, 0) == NULL) {
		cout<<"错误原因: "<< mysql_error(&mysql);
		cout<<"连接失败" << endl;
		Link_flag = false;
		}
	else {
		Link_flag = true;
	}
}

void Mysql::Show_Table_Data(const char* table) {
	if (Link_flag == false) {
		cout << "数据库未连接";
		return;
	}
	stringstream Link;
	Link << "select * from " << table << ";";
	string con = Link.str();
	int ret = mysql_query(&mysql, con.c_str());
	cout << ret <<endl;
	res = mysql_store_result(&mysql);
	while (row = mysql_fetch_row(res)) {
		for (int i = 0; i < mysql_num_fields(res); i++) {
			if (row[i] == 0) { cout << "NULL" << "\t"; continue; }//读到null返回0
			cout << row[i] << "\t";
		}
		cout << endl;
	}
	mysql_free_result(res);
}

void Mysql::Call_Message(const char* command) {
	if (Link_flag == false) {
		cout << "数据库未连接";
		return;
	}
	mysql_query(&mysql, command);
}

void Mysql::Get_Table_struct(const char* table) {
	if (Link_flag == false) {
		cout << "数据库未连接";
		return;
	}
	stringstream Link;
	Link << "select * from " << table << ";";
	string con = Link.str();
	int ret = mysql_query(&mysql, con.c_str());
	cout << ret << endl;
	res = mysql_store_result(&mysql);
	int num = mysql_num_fields(res);
	cout << num << endl;
	for (int i = 0; i < num; i++) {
		cout << mysql_fetch_field(res)->name << endl;
	}
}

Mysql::~Mysql() {
	mysql_close(&mysql);
	system("pause");
}
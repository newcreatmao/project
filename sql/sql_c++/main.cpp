#include<iostream>
#include<mysql.h>
#include "user.hpp"
using namespace std;

int main() {
	Mysql use;
	use.Connection("192.168.142.131", "root","123456", "JINRONG", 3306);
	use.Show_Table_Data("fund");
	use.Get_Table_struct("fund");
	use.Show_Table_Data("client");
	return 0;
}

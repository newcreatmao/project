//#include<mysql.h>
//#include<stdio.h>//mysql �ļ�
//#include<iostream>
//#include<sstream>
//#include<string>
//using namespace std;
//
//int main()
//{
//	MYSQL mysql;//���ݿ���
//	MYSQL_RES* res;//��ѯ�����
//	MYSQL_ROW row;//��¼�ṹ��
//
//	��ʼ�����ݿ�
//	mysql_init(&mysql);
//
//	�����ַ�����
//	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
//
//	�������ݿ�
//������Ҫ�����Լ��ı����������룬��ȫΪĬ�ϣ�ֻ�����*��Ϊ�Լ��������Լ���xsgl�����ĳ��Լ����������ݿ⼴��
	//if (mysql_real_connect(&mysql, "127.0.0.1", "root",
	//	"093000", "y", 3306, NULL, 0) == NULL) {
	//	printf("����ԭ��: %s\n", mysql_error(&mysql));
	//	printf("����ʧ�ܣ�\n");
	//	exit(-1);
//	}
//	stringstream ss;
//	char x[100],y[100];
//	string sql;
//	cin.getline(x,100);//���ճ���Ϊ100���ַ������Դ��ո�
//	��ѯ����
//	ss << x << y;
//	sql = ss.str();
// studentΪxsgl���ݿ��д��ڵı�
//	int ret = mysql_query(&mysql,sql.c_str());
//	int ret = mysql_query(&mysql, "select * from emp;");
//	printf("ret: %d\n", ret);
//
//	��ȡ�����
//	res = mysql_store_result(&mysql);
//
//	��ROW��ֵ,�ж�ROW�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
//	while (row = mysql_fetch_row(res))
//	{
//		printf("%s ", row[0]);//ѧ��
//		printf("%s ", row[1]);//����
//		printf("%s ", row[2]);//�Ա�
//		printf("%s ", row[3]);//����
//		printf("%s ", row[4]);//����
//		printf("%s ", row[5]);//����
//		printf("%s\n", row[6]);//����
//
//	}
//	�ͷŽ����
//	mysql_free_result(res);
//
//	�ر����ݿ�
//	mysql_close(&mysql);
//
//	system("pause");
//	return 0;
//}
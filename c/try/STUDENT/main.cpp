#include <iostream>
#include"User.hpp"
using namespace std;
int main() {
    system("title student");//���ô�����
    system("color 70");
    Funtion_select();
    system("pause");
    cout<<"�����������"<<endl;
    return 0;
}


// system()��ͷ�ļ�stdlib.h��

// system()��C������Ϊ�˵���windowsϵͳ���������á�

// ����

// system(��color Xx��);//��һ������������Ʊ���ɫ���ڶ���������������ɫ

// system(��cls��);//����

// system(��pause��);//��ͣ



// system(��start ��ַ��);//��ĳ����

// system(��mode ����1,����2��);//���ƴ��ڵĴ�С������1���Ƴ�������2���Ƹߡ�

// system(��mode con cols=����1 lines=����2��);//���ƴ��ڵĴ�С������1���Ƴ�������2���Ƹߡ�
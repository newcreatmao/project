#pragma once//���ظ�����,�൱��ifndef�����Ƕ������ļ�����
#include <cstdio>
#include<string>
using namespace std;
class Student
{
    private:
    string st_name;
    int st_age;
    string st_locate;
    string st_schoolnum;
    string st_profession;
    
    public:
    //Student(string name,int age,string location,string schoolnum,string profession);���캯�������ڴ�������ʱ�������Ӧ����
    void Look_information();
    void Name_change(string name);
    void Age_change(int age);
    void Location_change(string locate);
    void Num_change(string nschoolnum);
    void Profession_change(string profession);
};
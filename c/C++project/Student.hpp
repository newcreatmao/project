#pragma once//防重复调用,相当与ifndef，但是对整个文件而言
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
    //Student(string name,int age,string location,string schoolnum,string profession);构造函数，即在创建对象时就输入对应参数
    void Look_information();
    void Name_change(string name);
    void Age_change(int age);
    void Location_change(string locate);
    void Num_change(string nschoolnum);
    void Profession_change(string profession);
};
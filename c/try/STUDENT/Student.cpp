#include<iostream>
#include<string>
#include"Student.hpp"
using namespace std;

void Student::Age_change(int age){
    st_age=age;
};

void Student::Location_change(string locate){
    st_locate=locate;
}

void Student::Name_change(string name){
    st_name=name;
}

void Student::Num_change(string nschoolnum){
    st_schoolnum=nschoolnum;
}

void Student::Profession_change(string profession){
    st_profession=profession;
}

void Student::Look_information(){
    cout<<"name:"<<st_name<<"\nage:"<<st_age<<"\nlocation:"<<st_locate<<"\nschoolnum:"<<st_schoolnum<<"\nprofession is:"<<st_profession<<endl;
}

//Student::Student(string name,int age,string location,string schoolnum,string profession):
//   st_name(name),st_age(age),st_locate(location),st_schoolnum(schoolnum),st_profession(profession)
//{};

int Student::Get_age(){
    return st_age;
}

string Student::Get_name(){
    return st_name;
}

string Student::Get_location(){
    return st_locate;
}

string Student::Get_Num(){
    return st_schoolnum;
}

string Student::Get_Profession(){
    return st_profession;
}

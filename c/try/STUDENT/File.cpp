#include <cstdio>
#include<fstream>
#include <iostream>
#include <ostream>
#include <string>
#include"link.hpp"
using namespace std;
void Save_data_file(C*header,string filename){
    C*p=header;
    ofstream fp;
    fp.open(filename,ios::app);
    while(fp.is_open()&&!IsNULL_link(p)){
        fp<<"¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n"<<"name is£º "<<p->student->Get_name()<<"\nage is£º "<<p->student->Get_age()<<endl;
        fp<<"location is£º "<<p->student->Get_location()<<"\nschoolnum is£º "<<p->student->Get_Num()<<"\nprofession is£º "<<p->student->Get_Profession()<<endl;
        p=Go_next_link(p);
    }
    fp.close();
    cout<<"save over!"<<endl;
}

int Musure_file_data(string filename){
    int count=0;
    string data;
    ifstream fp;
    fp.open(filename,ios::in);
    while(fp.is_open() && getline(fp,data)){
        count++;
    }
    fp.close();
    return count/5;
}

void Output_data_file(string filename){
    ifstream fp;
    string data;
    fp.open(filename,ios::in);
    while(getline(fp,data)){
        cout<<data<<endl;
    }
    fp.close();
}

void Delete_file(string filename){
    ofstream fp;
    fp.open(filename,ios::trunc);
    fp.close();
}

#include<iostream>
#include<string>
#include "Student.hpp"
#include "User.hpp"
#include"link.hpp"
#include"File.hpp"
using namespace std;


void Menu_st()
{
    cout<<"This is Student_funtion introduction"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"look the funtions , you can input menu"<<endl;
    cout<<"the Student include some imformation"<<endl;
    cout<<"name age location schoolnum profession"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"if you want to input togetther ,you can input input"<<endl;
    cout<<"change the name , you can input change_name"<<endl;
    cout<<"change the age , you can input change_age"<<endl;
    cout<<"change the schoolnum , you can input change_schoolnum"<<endl;
    cout<<"change the location , you can input change_location"<<endl;
    cout<<"change the profession , you can input change_profession"<<endl;
    cout<<"if you want to look the imformation ,you can input look"<<endl;
    cout<<"if you want to clear windows ,you can input cls"<<endl;
    cout<<"----------------------------------"<<endl;
} 

void Menu_link()
{
    cout<<"This is link_funtion introduction"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"look the funtions , you can input menu"<<endl;
    cout<<"creat a link , you can input creat"<<endl;
    cout<<"delete a item , you can input delete"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"add a item , you can input add"<<endl;
    cout<<"   add have three choice funtion"<<endl;
    cout<<"      add end;   add mid;   add head"<<endl;
    cout<<"----------------------------------"<<endl;
    cout<<"search a item , you can input search"<<endl;
    cout<<"search the link length , you can input measure"<<endl;
    cout<<"if you want to look all imformation ,you can input look"<<endl;
    cout<<"save the data , you can input save "<<endl;
    cout<<"look the data , you can input outputfile"<<endl;
    cout<<"look the datanum , you can input measurefile"<<endl;
    cout<<"delete  a file , you can input deletefile"<<endl;
    cout<<"if you want to clear windows ,you can input cls"<<endl;
    cout<<"----------------------------------"<<endl;
}

void Look_all_st(C*&header){
    if(header==NULL){
        cout<<"please creat a link!"<<endl;
        return;
    }
    int i=0;
    C*p=header;
    while(p!=NULL)
    {
        cout<<"----------------------------------------------"<<endl;
        cout<<"the "<<++i<<endl;
        p->student->Look_information();
        cout<<"----------------------------------------------"<<endl;
        p=Go_next_link(p);
    }
    cout<<"output over"<<endl;
}

void St_funtion(C*p){
    Menu_st();
    while(1)
    {
        string funtion_name;
        cout<<"please input your st_choose!"<<endl;
        cin>>funtion_name;

        if(funtion_name=="menu"){
            Menu_st();
        }

        else if(funtion_name=="input"){
            string input;int age;
            cout<<"input name"<<endl;
            cin>>input;
            p->student->Name_change(input);
            cout<<"input age"<<endl;
            cin>>age;
            p->student->Age_change(age);
            cout<<"input location"<<endl;
            cin>>input;
            p->student->Location_change(input);
            cout<<"input schoolnum"<<endl;
            cin>>input;
            p->student->Num_change(input);
            cout<<"input Profession"<<endl;
            cin>>input;
            p->student->Profession_change(input);
        }
         
        else if(funtion_name=="look"){
            p->student->Look_information();
        }

        else if(funtion_name=="change_name"){
            string input;
            cout<<"input change_name"<<endl;
            cin>>input;
            p->student->Name_change(input);
        }

        else if(funtion_name=="change_schoolnum"){
            string input;
            cout<<"input change_schoolnum"<<endl;
            cin>>input;
            p->student->Num_change(input);
        }

        else if(funtion_name=="change_profession"){
            string input;
            cout<<"input change_profession"<<endl;
            cin>>input;
            p->student->Profession_change(input);
        }

        else if(funtion_name=="change_location"){
            string input;
            cout<<"input change_location"<<endl;
            cin>>input;
            p->student->Location_change(input);
        }

        else if(funtion_name=="change_age"){
            int input;
            cout<<"input change_age"<<endl;
            cin>>input;
            p->student->Age_change(input);
        }

        else if(funtion_name=="end"){
            break;
        }

        else if(funtion_name=="cls"){
            system("cls");
        }

        else {
            cout<<"no this choose!"<<endl;
            continue;
        }
    }
}

void Funtion_select(){
    Menu_link();
    C*header=NULL;
    while(1){
        system("time /T");//显示当前时间
        system("date /T");//显示当前日期
        string funtion_name;
        cout<<"please input your Link_choose!"<<endl;
        cin>>funtion_name;

        if(funtion_name=="creat"){
            header = Create_link();
        }

        else if(funtion_name=="menu"){
            Menu_link();
        }

        else if(funtion_name=="delete"){
            cout<<"please input the index that you want to delete"<<endl;
            int index;
            cin>>index;
            Delete_index_data(header, index);
        }

        else if(funtion_name=="search"){
            cout<<"please input the index that you want to search"<<endl;
            int index;
            cin>>index;
            C*p=Find_index_data(header, index);
            if(p!=NULL){
                St_funtion(p);
            }
        }

        else if(funtion_name=="measure"){
            cout<<Measure_index(header)<<endl;
        }

        else if(funtion_name=="look"){
            Look_all_st(header);
        }

        else if(funtion_name=="add"){
            cout<<"please input the location where you want to add the data!"<<endl;
            cout<<"head,mid,end,if you want to add in the mid you should input index!"<<endl;
            string input;
            cin>>input;
            if(input=="head"){
                header=Add_mate_head(header);
            }
            else if (input=="end") {
                Add_mate_end(header);
            }
            else if (input=="mid") {
                int index;
                cin>>index;
                Add_mate_locate(header,index);
            }
            else {
                cout<<"add error! not have the location!"<<endl;
                continue;
            }
        }

        else if(funtion_name=="end"){
            break;
        }

        else if(funtion_name=="cls"){
            system("cls");
        }

        else if(funtion_name=="save"){
            cout<<"please input your filename"<<endl;
            string filename;
            cin>>filename;
            Save_data_file(header,filename);
        }

        else if(funtion_name=="measurefile"){
            cout<<"please input your filename"<<endl;
            string filename;
            cin>>filename;
            cout<<"have "<<Musure_file_data(filename)<<" data"<<endl;
        }

        else if(funtion_name=="outputfile"){
            cout<<"please input your filename"<<endl;
            string filename;
            cin>>filename;
            Output_data_file(filename);
        }

        else if(funtion_name=="deletefile"){
            cout<<"please input your filename"<<endl;
            string filename;
            cin>>filename;
            Delete_file(filename);
        }

        else {
            cout<<"no this choose!"<<endl;
            continue;
        }

    }
}
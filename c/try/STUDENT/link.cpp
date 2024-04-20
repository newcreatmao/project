#include <cstddef>
#include<iostream>
#include"Student.hpp"
#include"link.hpp"
using namespace std;

C* Create_link(void){
    C*header = new C;
    if(header!=NULL){
        cout<<"create success!"<<endl;
        header->next=NULL;
        return header;
    }
    else {
        cout<<"create error!"<<endl;
        delete header;
        return NULL;
    }
}

C*& Go_next_link(C*&q){
    return q->next; 
}

bool IsNULL_link(C*p){
    return (p==NULL);
}

bool Next_isNULL_link(C*p){
    C*q;
    q=p->next;
    return (q==NULL);
}

int Measure_index(C*&header){
    if(header==NULL){
        return 0;
    }

    int count=1;
    C*p = header;
    while(!Next_isNULL_link(p)){
        p=Go_next_link(p);
        count++;
    }
    return count;
}

void Add_mate_end(C*&header){//尾插
    C*p = header;
    if(IsNULL_link(p))
    {
        cout<<"please create a link"<<endl;
        return;
    }
    while(!Next_isNULL_link(p)){
        p=Go_next_link(p);
    }
    C*item = new C;
    p->next = item;
    item->next=NULL;
    if(Next_isNULL_link(p))
        cout<<"Add error!"<<endl;
    else 
        cout<<"Add success!"<<endl;
}

C* Add_mate_head(C*&header){//头插
    if(IsNULL_link(header))
    {
        cout<<"please create a link"<<endl;
        return NULL;
    }

    C*m = header;

    C*newhead = new C;
    newhead->next = m;
    if(newhead->next != header){
        cout<<"Add error"<<endl;
        return NULL;
    }
    else{
         cout<<"Add success!"<<endl;
        return newhead;
    }
}

void Add_mate_locate(C*&header,int locate){
    C*p = header;
    if(IsNULL_link(p))
    {
        cout<<"please create a link"<<endl;
        return;
    }

    if(Measure_index(header)<locate||locate<=0){
        cout<<"not have the index!"<<endl;
        return;
    }

    if(locate==1){
        Add_mate_end(header);
        return;
    }

    p = header;
    for(int i=1;i<locate-1;i++){
        p=Go_next_link(p);
    }//到达locate上一个

    C*item = new C;
    C*q = p->next;
    p->next = item;
    item->next =q;
    if(p->next->next == q)
        cout<<"Add success!"<<endl;
    else
        cout<<"Add error!"<<endl;
}

C* Find_index_data(C*header,int locate){
    C*p = header;
    if(IsNULL_link(p))
    {
        cout<<"please create a link"<<endl;
        return NULL;
    }

    if(Measure_index(header)<locate||locate<=0){
        cout<<"not have the index!"<<endl;
        return NULL;
    }

    if(locate==1){
        return header;
    }

    p = header;
    for(int i=1;i<locate;i++){
        p=Go_next_link(p);
    }
    return p;
}

void Delete_index_data(C*&header,int locate){
    if(header==NULL)
    {
        cout<<"please create a link"<<endl;
        return;
    }

    C*p = header;
    if(Measure_index(header)<locate||locate<=0){
        cout<<"not have the index!"<<endl;
        return;
    }

    if(locate==1){
        header=p->next;
        delete p;
        p=NULL;
        cout<<"Delete success!"<<endl;
        return;
    }

    for(int i=1;i<locate-1;i++){
        p=Go_next_link(p);
    }
    C*q = p->next;
    C*l = q->next;
    p->next = q->next;
    delete q;
    q = NULL;
    if(p->next == l && q==NULL)
        cout<<"Delete success!"<<endl;
    else
        cout<<"Delete error!"<<endl;
}
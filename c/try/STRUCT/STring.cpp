#include<stdio.h>
#include<stdlib.h>
#include"STring.hpp"

struct String_Node{
    char data;
    String_Node* next;
};

struct String_end{
    String_Node* end;
};

struct String_Link{
    String_Node* head;
    String_Node* tail;
};

String_end* Get_end_Flag(){
    String_end*flag;
    flag = (String_end*)malloc(sizeof(String_end));
    flag->end = (String_Node*)malloc(sizeof(String_Node*));
    flag->end->data = '\0';
    flag->end->next = NULL;
    return flag;
}

String_Link* Create_String_link(){
    String_Link*link;
    link = (String_Link*)malloc(sizeof(String_Link));
    if(link==NULL){
        printf("Is NULL!\n");
    }
    else{
        link->head=NULL;
        link->tail=NULL;
    }
    return link;
}

String_Node* Add_Node_String(String_Node*frent,char data){
    String_Node*node;
    node = (String_Node*)malloc(sizeof(String_Node*));
    node->data=data;
    node->next=NULL;
    frent->next=node;
    return node;
}

void Create_String(String_Link* link){
    char c;
    c=getchar();
    link->head = (String_Node*)malloc(sizeof(String_Node));
    link->head->data = c;
    link->tail = link->head;
    while(c=getchar()){
        if(c=='\n'){break;}
        link->tail = Add_Node_String(link->tail,c);
    }
    String_end* end = Get_end_Flag();
    link->tail->next = end->end;
}

void Output_String(String_Link*link){
    String_Node*Go;
    Go=link->head;
    while(Go!=link->tail->next){
        printf("%c",Go->data);
        Go=GO_Next_String(Go);
    }
    printf("\n");
}

String_Node* GO_Next_String(String_Node*frent){
    return (frent->next);
}

int String_Lenth(String_Link*link){
    String_Node*Go;
    int i=0;
    Go=link->head;
    while(Go!=link->tail->next){
        Go=GO_Next_String(Go);
        i++;
    }
    return i;
}

String_Link* String_Cat(String_Link*link1,String_Link*link2){
    String_Node*node = link1->tail;
    node->next = link2->head;
    link1->tail = link2->tail;
    return link1;
}

String_Link* String_Copy_Shallow(String_Link*link){
    String_Link*newlink = Create_String_link();
    newlink->head = link->head;
    newlink->tail = link->tail;
    return newlink;
}

String_Link* String_Copy_Dept(String_Link*link){
    String_Link*newlink = Create_String_link();
    String_Node*Go;
    Go=link->head;
    newlink->head = (String_Node*)malloc(sizeof(String_Node));
    newlink->head->data = Go->data;
    newlink->tail = newlink->head;
    Go=GO_Next_String(Go);
    while(Go!=link->tail->next){
        newlink->tail = Add_Node_String(newlink->tail,Go->data);
        Go=GO_Next_String(Go);
    }
    return newlink;
}

int String_Compare(String_Link*link1,String_Link*link2){
    if(String_Lenth(link1)>String_Lenth(link2)){
        return 1;
    }
    if(String_Lenth(link1)<String_Lenth(link2)){
        return -1;
    }
    if(String_Lenth(link1)==String_Lenth(link2)){
        String_Node*Go1;String_Node*Go2;
        Go1=link1->head;Go2=link2->head;
        while(Go1!=link1->tail->next){
            if(Go1->data>Go2->data){return 1;}
            if(Go1->data<Go2->data){return -1;}
            Go1 = GO_Next_String(Go1);Go2 = GO_Next_String(Go2);
        }
        return 0;
    }
    return 0;
}

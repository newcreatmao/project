#include <stdio.h>
#include <stdlib.h>
#include "Set.hpp"

struct Set{
    Set_data data;
    Set * next;
};

bool Is_NULL_Set(Set*p){
    return (p==NULL);
}

Set* Go_Next_Set(Set*p){
    return p->next;
}

bool Is_New_data(Set*head,Set_data data){
    Set*p=head;
    while(!Is_NULL_Set(p)){
        if(data==p->data){
            return false;
        }
        p=Go_Next_Set(p);
    }
    return true;
}

Set* Create_NULL_Set(){
    Set*head;
    if(head==NULL){
        printf("out of space!\n");
        return NULL;
    }
    head = (Set*)malloc(sizeof(Set*));
    head->next = NULL;
    return head;
}

void Add_data_Set(Set*head,Set_data data){
    if(Is_New_data(head,data)){
        Set *p =head;
        while(!Is_NULL_Set(p->next)){
            p = Go_Next_Set(p);
        }
        p->next = (Set*)malloc(sizeof(Set*));
        p->next->data = data;
        p->next->next = NULL;
    }
    else{
        printf("exist the data!\n");
    }
}


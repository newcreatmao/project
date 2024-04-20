#include"List.hpp"
#include<stdio.h>
#include<stdlib.h>

struct List{
    List_data data;
    List*next;
};

List* Create_NULL_List(){
    List*head;
    if(head == NULL){
        printf("create error!\n");
        return NULL;
    }
    head = (List*)malloc(sizeof(List*));
    head->next = NULL;
    return head;
}

List* Insert_Head_List(List* head,List_data data){
    List*newhead;
    if(newhead == NULL){
        printf("error!\n");
    }
    newhead = (List*)malloc(sizeof(List*));
    newhead->data = data;
    newhead->next = head;
    return newhead;
}

void Insert_Mid_List(List* head,List_data data,int locate){
    if(locate <= 1 || locate > Get_Listlen(head)){
        printf("error index!\n");
    }
    List*p = head;
    int i=0;
    for(i=1;i<locate;i++){
        p = Go_NextNode_List(p);
    }
    List* node = (List*)malloc(sizeof(List*));
    node->data = data;
    node->next = p->next;
    p->next = node;
}

void Insert_End_List(List* head,List_data data){
    List*p = head;
    while(!Is_NULLNode_List(p->next)){
        p = Go_NextNode_List(p);
    }
    List* node = (List*)malloc(sizeof(List*));
    node->data = data;
    node->next = NULL;
    p->next = node;
}

List_data Get_Value_List(List*head,int locate){
    if(locate < 1 || locate > Get_Listlen(head)){
        printf("error index!\n");
    }
    List*p = head;
    int i=0;
    for(i=1;i<locate;i++){
        p = Go_NextNode_List(p);
    }
    return p->data;
}

List* Go_NextNode_List(List*p){
    return p->next;
}

bool Is_NULLNode_List(List*p){
    return (p == NULL);
}

List* Delete_Head_List(List* head){
    List*p = head->next;
    free(head);
    head=NULL;
    return p;
}

void Delete_Node_List(List*head,int locate){
    if(locate <= 1 || locate > Get_Listlen(head)){
        printf("error index!\n");
    }
    List*p = head;
    int i=0;
    for(i=1;i<locate;i++){
        p = Go_NextNode_List(p);
    }
    List* node = p->next->next;
    free(p->next);
    p->next=NULL;
    p->next=node;
}

int Get_Listlen(List*head){
    int i=0;
    List*p = head;
    while(!Is_NULLNode_List(p)){
        p = Go_NextNode_List(p);
        i++;
    }
    return i;
}
#include <stdio.h>
#include <stdlib.h>
#include "Queue.hpp"

struct Node{
    Datatype_Queue data;
    Node* next;
};

struct Queue{
    Node* head;
    Node* tail;
};

Queue* Create_Empty_Linkqueue(){
    Queue* plgu = (Queue*)malloc(sizeof(Queue*));
    if(plgu!=NULL){
        plgu->head = NULL;
        plgu->tail = NULL;
    } 
    else 
        printf("out of space!\n");
    return plgu;
}

bool Is_Empty_Queue(Queue* Q){
    return (Q->head==NULL);
}

void En_Queue(Queue*Q,Datatype_Queue data){
    Node*node;
    node = (Node*)malloc(sizeof(Node*));
    node->data = data;
    node->next = NULL;
    if(Q->head==NULL){
        Q->head = Q->tail = node;
        return;
    }
    Q->tail->next = node;
    Q->tail = node;
}

Datatype_Queue De_Queue(Queue*Q){
    if(Is_Empty_Queue(Q)){
        printf("Is empty!\n");
        Datatype_Queue data;
        return data;
    }
    else{
        Datatype_Queue data;
        data = Q->head->data;
        Node*p;
        p=Q->head;
        Q->head = p->next;
        free(p);
        p = NULL;
        return data;
    }
}

Datatype_Queue Front_Queue_Link(Queue*Q){
    if(Is_Empty_Queue(Q)){
        printf("Is empty!\n");
        return Q->head->data;
    }
    else return Q->head->data;
}
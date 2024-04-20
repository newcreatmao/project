#ifndef __QUEUE_H_
#define __QUEUE_H_
#include "Datatypeclass.hpp"
typedef Datatype_Queue Queue_data;
typedef struct Queue Queue;
typedef struct Node Node;

Queue* Create_Empty_Linkqueue();
bool Is_Empty_Queue(Queue* Q);
void En_Queue(Queue*Q,Datatype_Queue data);
Datatype_Queue De_Queue(Queue*Q);
Datatype_Queue Front_Queue_Link(Queue*Q);
#endif
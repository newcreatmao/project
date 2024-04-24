#ifndef __USER_H
#define __USER_H

#include<stdio.h>

typedef void DataType;
typedef struct Stack Stack;
typedef struct Stack Node;

struct Stack{
    DataType(*data);
    Node*next;
};

void swap(int*a,int*b);

#endif
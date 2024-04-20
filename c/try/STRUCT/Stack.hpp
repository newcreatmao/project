#ifndef __STACK_H_
#define __STACK_H_
#include "Datatypeclass.hpp"
typedef Datatype_Stack Stack_data;
typedef struct Stack Stack;

Stack* Creat_NULLStack(void);
Stack* Go_Next_Stack(Stack*S);
bool IsNULL_Stack(Stack*S);
void Push_data(Stack*S,Stack_data data);
Stack_data Pop_data(Stack*S);
Stack_data Top_data(Stack*S);
int Get_Stacklen(Stack*S);

#endif
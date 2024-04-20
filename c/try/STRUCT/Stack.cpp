#include <stdlib.h>
#include <stdio.h>
#include "Stack.hpp"

struct Stack{
    Stack_data data;
    Stack*next;
};

Stack* Creat_NULLStack(void){
    Stack * head;
    if(head == NULL){
        printf("error creat!\n");
        return NULL;
    }
    head = (Stack*)malloc(sizeof(Stack*));
    head->next = NULL;
    return head;
}

Stack* Go_Next_Stack(Stack*S){
    return (S->next);
}

bool IsNULL_Stack(Stack* S){
    return (S==NULL);
}

void Push_data(Stack*S,Stack_data data){
    Stack*p = S;
    while(!IsNULL_Stack(p->next)){
        p = Go_Next_Stack(p);
    }
    p->next = (Stack*)malloc(sizeof(Stack*));
    p->next->data = data;
    p->next->next = NULL;
}

Stack_data Pop_data(Stack*S){
    if(IsNULL_Stack(S->next)){
       return Top_data(S);
    }
    Stack*p = S;
    while(!IsNULL_Stack(p->next->next)){
        p = Go_Next_Stack(p);
    }
    Stack_data data = p->next->data;
    free(p->next);
    p->next = NULL;
    return data;
}

Stack_data Top_data(Stack*S){
    Stack_data data = S->data;
    free(S);
    S = NULL;
    return data;
}

int Get_Stacklen(Stack*S){
    int i=0;
    Stack*p =S;
    while(!IsNULL_Stack(p)){
        p = Go_Next_Stack(p);
        i++;
    }
    return i;
}
#ifndef __LIST_H_
#define __LIST_H_

#include "Datatypeclass.hpp"
typedef Datatype_List List_data;
typedef struct List List;

List* Create_NULL_List();
List* Insert_Head_List(List* head,List_data data);
void Insert_Mid_List(List* head,List_data data,int locate);
void Insert_End_List(List* head,List_data data);
List_data Get_Value_List(List*head,int locate);
List* Go_NextNode_List(List*p);
bool Is_NULLNode_List(List*p);
void Delete_Node_List(List*head,int locate);
int Get_Listlen(List*head);
List* Delete_Head_List(List* head);

#endif
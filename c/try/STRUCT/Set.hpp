#ifndef __SET_H_
#define __SET_H_
#include "Datatypeclass.hpp"
typedef Datatype_Set Set_data;
typedef struct Set Set;

bool Is_NULL_Set(Set*p);
Set* Go_Next_Set(Set*p);
bool Is_New_data(Set*head,Set_data data);
Set* Create_NULL_Set();
void Add_data_Set(Set* head,Set_data data);

#endif
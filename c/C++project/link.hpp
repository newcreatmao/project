#pragma once

#include"Student.hpp"
typedef  struct ban
{
    Student *student = new Student;
    struct ban* next;
}C;

C* Create_link(void);

C*& Go_next_link(C*&q);

bool IsNULL_link(C*p);
bool Next_isNULL_link(C*p);

int Measure_index(C*headr);

void Add_mate_end(C*&header);
C* Add_mate_head(C*&header);
void Add_mate_locate(C*&header,int locate);

C* Find_index_data(C*header,int locate);

void Delete_index_data(C*&header,int locate);
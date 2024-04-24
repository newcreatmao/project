#ifndef __FUNTION_H
#define __FUNTION_H

#include<stdio.h>

#define Length(x) sizeof(x)/sizeof(x[0])

void Print_data(int*a,int len);
void Insert_sort(int*a,int len);
void MERGE_sort(int*a,int begin,int end);
#endif
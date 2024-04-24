#include<stdio.h>
#include<stdlib.h>
#include"user.hpp"
#include"Funtion.hpp"
#include<time.h>

// int main(){
//     clock_t start,end;
//     start=clock();
//     float Total_time;
//     int a[9]={150,42,54,42,342,65,45,34,21};
//     printf("%d\n",Length(a));
//     MERGE_sort(a,0,7);
//     Print_data(a,Length(a));
//     end=clock();
//     Total_time = (double)(end - start) / CLOCKS_PER_SEC; //µ¥Î»»»Ëã³ÉÃë
// 	printf("\n%f seconds\n", Total_time);
//     return 0;
// }

int main(){
    Stack*top=(Node*)malloc(sizeof(Node));
    top->data=&swap;
    top->next=NULL;
    int a=11,b=22;
    printf("%d %d\n",a,b);
    top->data(&a,&b);
    printf("%d %d\n",a,b);
}

// float ADD_float(float a,float b){
//     return a+b;
// }

// int ADD_int(int a,int b){
//     return a+b;
// }

// #define ADD(x,y) _Generic((x),int :ADD_int(x,y),float:ADD_float(x,y))

// int main(){
//     printf("%f",ADD(321.32,31.12));
// }
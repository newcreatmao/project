#include<stdio.h>
#include<stdlib.h>

struct stack{
	int MAX;
	int top;
	int *element;
};
typedef struct stack m;

m*Creat_Stack(int num){
	m*s=(m*)malloc(sizeof(m));
	if(s==NULL){
		return NULL;	
	}
	s->element=(int *)malloc(sizeof(int)*num);
	s->MAX=num;
	s->top=0;
	return s;
}

void Push_data(m*stack,int data){
	*(stack->element+stack->top)=data;
	stack->top++;
}

int Pop_data(m*s){
	s->top--;
	return *(s->element+s->top);
}

void Clear_stack(m*s,int save){
	s->top=save;
}

int result(int num,int end,int begin,int n){
	m*up=Creat_Stack(num),*off=Creat_Stack(num);
	int sum=0,i,j,k;
	Push_data(up,begin);
	Push_data(off,0);
	for(i=1;sum!=end;i++){
		sum=begin;
		Clear_stack(up,1);Clear_stack(off,1);
		Push_data(up,i);Push_data(off,i);
		for(j=0;j<5;j++){
			sum=sum+*(up->element+up->top-1)+*(up->element+up->top-2)-*(off->element+off->top-1);
			Push_data(off,*(up->element+up->top-1));
			Push_data(up,*(up->element+up->top-1)+*(up->element+up->top-2));
		}
	}
	return 1;
}

int main(){
	printf("%d",result(7,32,5,6));
}

//火车从始发站（称为第1站）开出，在始发站上车的人数为a，然后到达第2站，在第2站有人上、下车，但上、下车的人数相同，因此在第2站开出时（即在到达第3站之前）车上的人数保持为a人。从第3站起（包括第3站）上、下车的人数有一定规律：上车的人数都是上两站上车人数之和，而下车人数等于上一站上车人数，一直到终点站的前一站（第n-1站
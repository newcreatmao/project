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

//�𳵴�ʼ��վ����Ϊ��1վ����������ʼ��վ�ϳ�������Ϊa��Ȼ�󵽴��2վ���ڵ�2վ�����ϡ��³������ϡ��³���������ͬ������ڵ�2վ����ʱ�����ڵ����3վ֮ǰ�����ϵ���������Ϊa�ˡ��ӵ�3վ�𣨰�����3վ���ϡ��³���������һ�����ɣ��ϳ���������������վ�ϳ�����֮�ͣ����³�����������һվ�ϳ�������һֱ���յ�վ��ǰһվ����n-1վ
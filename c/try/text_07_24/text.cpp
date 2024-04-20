// // #include<stdio.h>
// // #include<stdlib.h>
// // #include<string.h>
// // #include<stdarg.h>
// // #include<string>
// // #include<iostream>
// // using namespace std;
// // double Try(int count,...);
// // int myprintf (const char *__format, ...);
// // void Use(double (*p)(int count,...),int num,...);


// // int main(){
// // 	double(*p)(int count,...);
// // 	p = Try;
// // 	Use(Try,3,2,34,4);
// // 	myprintf("%lf\n",(*p)(5,1.2,3.6,2.2,4.1,9,"hsksahda"));
// // 	return 0;
// // }

// // double Try(int count,...){
// // 	va_list arrs;
// // 	va_start(arrs,count);
// // 	double sum=0;int i;
// // 	for(i=0;i<count-1;i++){
// // 		sum+=va_arg(arrs,double);
// // 	}
// // 	sum+=va_arg(arrs,int);
// // 	printf("%s\n",va_arg(arrs,char*));
// // 	va_end(arrs);

// // 	return sum;
// // }

// // void Use(double (*p)(int count,...),int num,...){
// // 	va_list mm;
// // 	va_start(mm,num);
// // 	int i;
// // 	for(i=0;i<num;i++){
// // 		printf("%d\n",va_arg(mm,int));
// // 	}
// // 	va_end(mm);
// // 	printf("%.2lf\n1\n",(*p)(5,1.2,3.6,2.2,4.1,9,"hsksahda"));
// // }



 
// // void printch(const char ch)   //输出字符
// // {  
// //     putchar(ch);  
// // }  
 
 
// // void printint(const int dec)     //输出整型数
// // {  
// //     if(dec == 0)  
// //     {  
// //         return;  
// //     }  
// //     printint(dec / 10);  
// //     putchar((char)(dec % 10 + '0'));  
// // }  
 
 
// // void printstr(const char *ptr)        //输出字符串
// // {  
// //     while(*ptr)  
// //     {  
// //         putchar(*ptr);  
// //         ptr++;  
// //     }  
// // }  
 
 
// // void printfloat(const float flt)     //输出浮点数，小数点第5位四舍五入
// // {  
// //     int tmpint = (int)flt;  
// //     int tmpflt = (int)(100000 * (flt - tmpint));  
// //     if(tmpflt % 10 >= 5)  
// //     {  
// //         tmpflt = tmpflt / 10 + 1;  
// //     }  
// //     else  
// //     {  
// //         tmpflt = tmpflt / 10;  
// //     }  
// //     printint(tmpint);  
// //     putchar('.');  
// //     printint(tmpflt);  
 
// // }  
 
 
// // void my_printf(const char *format,...)  
// // {  
// //     va_list ap;  
// //     va_start(ap,format);     //将ap指向第一个实际参数的地址
// //     while(*format)  
// //     {  
// //         if(*format != '%')  
// //         {  
// //             putchar(*format);  
// //             format++;  
// //         }  
// //         else  
// //         {  
// //             format++;  
// //             switch(*format)  
// //             {  
// //                 case 'c':  
// //                 {  
// //                     char valch = va_arg(ap,int);  //记录当前实践参数所在地址
// //                     printch(valch);  
// //                     format++;  
// //                     break;  
// //                 }  
// //                 case 'd':  
// //                 {  
// //                     int valint = va_arg(ap,int);  
// //                     printint(valint);  
// //                     format++;  
// //                     break;  
// //                 }  
// //                 case 's':  
// //                 {  
// //                     char *valstr = va_arg(ap,char *);  
// //                     printstr(valstr);  
// //                     format++;  
// //                     break;  
// //                 }  
// //                 case 'f':  
// //                 {  
// //                     float valflt = va_arg(ap,double);  
// //                     printfloat(valflt);  
// //                     format++;  
// //                     break;  
// //                 }  
// //                 case 'p':
// //                 {
                  
// //                 }
// //                 default:  
// //                 {  
// //                     printch(*format);  
// //                     format++;  
// //                 }  
// //             }    
// //         }  
// //     }
// //     va_end(ap);         
// // }  



// // #include<stdio.h>
// // #include<stdlib.h>

// // struct Node;
// // struct link;
// // typedef struct link link;
// // typedef struct Node Node;
// // typedef int DataType; 

// // struct Node{
// //     DataType data;
// //     Node*left,*right;
// // };

// // struct link{
// //     Node*head;
// //     Node*tail;
// // };

// // link* Create_link(){
// //     link*Link;
// //     Link=(link*)malloc(sizeof(link));
// //     if(Link!=NULL){
// //         Node*head;
// //         head=(Node*)malloc(sizeof(Node));
// //         if(head!=NULL){
// //             head->data=0;
// //             head->left=head->right=NULL;
// //             Link->head=Link->tail=head;
// //             return Link;
// //         }
// //         return NULL;
// //     }
// //     return NULL;
// // }

// // void Insert_data(link*user,DataType data){
// //     Node*newnode=(Node*)malloc(sizeof(Node));
// //     link*p=user;
// //     printf("%d %d\n",p->head->data,p->tail->data);
// //     newnode->data=data;
// //     newnode->right=p->head;
// //     newnode->left=p->tail;
// //     p->head->left=newnode;
// //     p->head=newnode;
// //     p->tail->right=newnode;
// //     printf("%d %d\n",p->head->right->data,p->tail->left->data);
// // }

// // void Print(link*user){
// //     link*p;
// //     for(p=user;p->head!=p->tail;p->head=p->head->right){
// //         printf("%d %d",p->head->data,p->tail->data);
// //     }
// //     printf("\n");
// // }

// // int main(){
// //     link*user;
// //     user=Create_link();
// //     int a;
// //     for(int i=0;i<5;i++){
// //         scanf("%d",&a);
// //         Insert_data(user,a);
// //         printf("%p  %p\n",user->head,user->tail);
// //         Print(user);
// //     }
// //     return 0;
// // }


// // #include<bits/stdc++.h>
// // using namespace std;
// // struct node{
// // 	long long x;
// // 	long long y;
// // }wc[114515];
// // long long cw[114514];
// // int main()
// // {
// // 	//freopen("railway.in","r",stdin);
// // 	//freopen("railway.out","w",stdout);
// // 	int n,m,xx,q;
// // 	scanf("%d%d%d%d",&n,&m,&xx,&q);
// // 	wc[1].x=n;wc[1].y=0;wc[2].y=1;wc[2].x=0;
// // 	for(int i=3;i<=m-1;i++)
// // 	{
// // 		wc[i].x=wc[i-2].x+wc[i-1].x;
// // 		wc[i].y=wc[i-2].y+wc[i-1].y;
// // 	}
// // 	int ww=xx-n-wc[m-1].x;
// // 	int cc=wc[m-1].y-1;
// // 	if(ww%cc!=0)
// // 	{
// // 		cout<<"No answer.";
// // 		return 0;
// // 	}
// // 	xx=ww/cc;
// // 	long long h=n;
// // 	cw[1]=n;cw[2]=xx;
// // 	for(int i=3;i<=q;i++)
// // 	{
// // 		cw[i]=cw[i-1]+cw[i-2];
// // 		h+=cw[i-2];
// // 	};
// // 	return h;
// // }

// #include<stdio.h>
// #include<stdlib.h>

// struct Node{
//     char data;
//     struct Node*next;
// };
// typedef struct Node node;

// node * Creat_stack(){
//     node*head=(node*)malloc(sizeof(node));
//     if(head==NULL){
//         return NULL;
//     }
//     head->data='#';
//     head->next=NULL;
//     return head;
// }

// int Isempty(node*head){
//     return (head->next==NULL);
// }

// void Push(node*head,char data){
//     node*p=head;
//     node*newnode=(node*)malloc(sizeof(node));
//     newnode->data=data;
//     newnode->next=NULL;
//     p->next=newnode;
// }

// char Pop(node*head){
//     node*p;
//     if(Isempty(head)==0){
//         p=head->next;
//         char c=head->data;
//         head->next=p->next;
//         free(p);
//         return c;
//     }
// }

// char top(node* s) 
// {
// 	if(Isempty(s)==0)
//   	{
//     	return s->next->data ;
//   	}
// }
// //123*3/2+3*45
// //31*5
// DataType pop(Stack s) 
// {
// 	PtrToNode temp;
// 	int t;
// 	if(isEmpty(s)==0)
//   	{
//   		temp = s->next;
//   		t = temp->element;
//   		s->next = temp->next;
//   		free(temp);
//  		 return t;
//  	}
// }

// DataType top(Stack s) 
// {
// 	if(isEmpty(s)==0)
//   	{
//     	return s->next->element ;
//   	}
// }

// Stack inToPost(char *expression)
// {
//    int i = 0;
//    char ch;
//    Stack s = createStack();
//    push('#',s);
//    while(expression[i+1]!='\0')
//    {
//    		ch = expression[i];
//    		if(ch>='0'&&ch<='9'){
// 			while(ch>='0'&&ch<='9'){
// 				printf("%c",ch);
// 				i++;
// 				ch=expression[i];
// 				if(expression[i]=='\0')break;
// 			}
// 			printf(" ");
// 			if(expression[i]=='\0')break;
// 		}
// 		if(ch=='('){
// 			push(ch,s);
// 		}else if(ch=='*' || ch == '/'){
// 			push(ch,s);
// 		}else if(ch == '+'  || ch == '-'){
// 			while(s->next->element!='#' && s->next->element!='(' && s->next->element!=')'){
// 				printf("%c ",pop(s));
// 			}
// 			push(ch,s);
// 		}else if(ch==')'){
// 			while(s->next->element!='('){
// 				printf("%c ",pop(s));
// 			}
// 			pop(s);
// 		}
// 		i++;
// 		if((expression[i])=='\0')
// 			break;
// 	} 
// 	if(expression[i]>='0'&&expression[i]<='9')
// 		printf("%c ",expression[i]);
// 	while(!isEmpty(s->next)){
// 		printf("%c ",pop(s));
// 	}
//    /**********  End  **********/
//    return s;
// }

// void print(){

// }

#include <stdio.h>
#define Maxsize 100

typedef struct
{
	float x[Maxsize];
	float y[Maxsize];
	int size;
}Seqlist;

void CreateList(Seqlist*L)
{
	L = new Seqlist;
	L->size = 0;
	int i;

	for (i = 0;i<3;i++)
	{
		scanf("%f%f", &L->x[i], &L->y[i]);
	}
	L->size = i;
	return;
}

void Printf(Seqlist*L)
{
	int i;
	for (i = 0;L->x;i++)
		printf("%-5.8f%-5.8f\n", L->x[i], L->y[i]);
	return;
}

void Reverse(Seqlist* L)
{
	int i, t = L->size;
	float p, q;
	for (i = 0;i < t/2;i++)
	{
		p = L->x[i];
		L->x[i] = L->x[t - i - 1];
		L->x[t - i - 1] = p;

		q = L->y[i];
		L->y[i] = L->y[t - i - 1];
		L->y[t - i - 1] = q;
	}
	return;
}

int main()
{
	Seqlist* L=NULL; 
	CreateList(L);
	printf("原坐标数据为：\n");
	Printf(L);
	return 0;
}
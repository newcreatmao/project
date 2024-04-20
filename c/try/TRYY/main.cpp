// #include<stdio.h>
// #include<string.h>
// struct data{
// 	char coursename[20];
// 	int num;
// 	void walk (int mm)
// 	{
// 		printf("%s走了%d步\n",coursename,mm);
// 	};
// };
 

// double hfkas(int a){
// 	return a;
// }

// int main(){
// 	struct data stu1;
// 	stu1.num=10;
// 	scanf("%s",stu1.coursename);
// 	stu1.walk(30);
// 	printf("%s %d",stu1.coursename,stu1.num);
// }


// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<string>
// #include<iostream>
// using namespace std;

// /*在此处定义存储课程信息的数据结构，课程信息包括：课程名称、学分、讲授学时、实践学时、课程类别、开课学期。*/
// typedef struct course
// {
//     char coursename[50];
//     float credit;
//     int Tperiod;
//     int Operiod;
//     char classes[10];
//     int term;

// } DataType;

// struct seqList //顺序线性表结构定义
// {//有3个数据成员
//   int MAXNUM;//用于记录顺序线性表中能存放的最大元素个数的 整型 MAXNUM   
//   int curNum;//用于存放顺序线性表中数据元素的个数  整型  curNum
//   DataType *element;//用于存放顺序线性表数据元素的连续空间的起始地址  
// };

// typedef struct seqList *PseqList;  
// typedef struct seqList User;

// //实验一：第1关
// PseqList createNullList_seq(int m)
// {//此处填写代码，创建一个空的顺序线性表，能存放的最大元素个数为 m
//  //若m=0，则返回NULL 
//     if(m==0){return NULL;}
//     PseqList head=(PseqList)malloc(sizeof(User));
//     if(head==NULL){
      
//         return NULL;}
//     head->MAXNUM=m;
//     head->curNum=0;
//     head->element=(DataType*)malloc(sizeof(DataType)*head->MAXNUM);
//     return head;
// }

// void printList_seq(PseqList L)
// {//逐个输出线性表的元素，每门课程信息一行，课程信息的若干元素之间以一个空格为分隔符隔开
//     for(int i=0;i<L->curNum;i++){
//         printf("%s %f %d %d %s %d\n",(L->element+i)->coursename,(L->element+i)->credit,(L->element+i)->Tperiod,(L->element+i)->Operiod,(L->element+i)->classes,(L->element+i)->term);
//     }
// }


// int readFromFile(PseqList L) 
// //从文件course.txt 读取课程信息，放入线性表L中，直接在线性表表尾插入，返回值为读取的课程信息数
// {
// //读取文件时的文件名路径/data/workspace/myshixun/src/course.txt
//     FILE*fp;
//     fp=fopen("data.txt","r");
//     char buf[1024];int i=0;
//     while(fgets(buf,1024,fp)){
// 		sscanf(buf, "%s %f %d %d %s %d",(L->element+i)->coursename,&(L->element+i)->credit,&(L->element+i)->Tperiod,&(L->element+i)->Operiod,(L->element+i)->classes,&(L->element+i)->term);
// 		if((L->element+i)->term==0){continue;}
// 		i++;
// 	}
// 	L->curNum=i;
//     return L->curNum;
// }

// //实验一：第2关
// int isFullList_seq(PseqList &L)
// {
//   //判断顺序线性表是否已满，若已满，返回值为1，否则返回值为0
//  if(L->curNum>=L->MAXNUM){
// 	return 1;
//  }
//  return 0;
// }


// int insertP_seq(PseqList &L , int p ,DataType x)
// {// 在线性表L中下标为p的位置插入数据元素x，若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
//    //如果线性表满了， 还需输"list is full"的提示
//   //如果插入位置非法，需输出提示"position is illegel" 
//   if(isFullList_seq(L)){
// 	cout<<"list is full"<<endl;
// 	return 0;
//   }
//   else if(p>L->MAXNUM||p<0){
// 	cout<<"position is illegel"<<endl;
// 	return 0;
//   }
//   for(int i=L->curNum+1;i>p;i--){
// 	*(L->element+i)=*(L->element+i-1);
//   }
//   *(L->element+p)=x;
//   L->curNum++;
//   return 1;
// }

// int insertPre_seq(PseqList &L , int p ,DataType x)
// {
//  // 在线性表L中下标为p的位置的前面插入数据元素x，若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
// //提示：直接调用insertP函数实现即可    
//     return insertP_seq(L,p-1,x);
// }

// int insertPost_seq(PseqList &L , int p ,DataType x)
// {
//  // 在线性表L中下标为p的位置的后面插入数据元素x，若下标p非法或线性表已满无法插入数据，返回0；插入成功返回值为1
// //提示：直接调用insertP函数实现即可    
//     return insertP_seq(L,p+1,x);
// }
// int findPos(PseqList &L, DataType x)
// {//根据要插入的课程名称 查找在顺序表中插入的位置，返回值是插入课程信息的下标位置
// 	for(int i=0;i<L->curNum;i++){
// 		if(strcmp(L->element[i].coursename,(x.coursename))==0){
// 			return i;
// 		}
// 	}
// 	return 0;
// }

// int insertFromFile(string filename,PseqList &L )
// {
//   //从filename为文件名的文件中读取课程信息，按学期、课程名称顺序插入线性表L，使课程信息按学期、课程名称有序
//   //返回值是插入课程信息的条数
//     FILE*fp;
// 	char coursename[filename.length()];
// 	filename.copy(coursename,filename.length());
//     fp=fopen(coursename,"r");
//     char buf[1024];int i=L->curNum;
// 	int c=1;
// 	DataType U;
//     while(fgets(buf,1024,fp)&&c==1){
// 		int j=0;
// 		if(strlen(buf)<=2){continue;}
// 		sscanf(buf, "%s %f %d %d %s %d",U.coursename,&U.credit,&U.Tperiod,&U.Operiod,U.classes,&U.term);
// 		if(L->curNum==0){L->element[0]=U;}
// 		for(j=0;j<L->curNum;j++){
// 			if(U.term<=L->element[j].term){
// 				if(strcmp(U.coursename,L->element[j].coursename)==-1){
// 					c=insertP_seq(L,j,U);
// 					break;
// 				}
// 			}
// 		}
// 		if(j<L->curNum){continue;}
// 		c=insertP_seq(L,L->curNum,U);
// 	}
// 	return L->curNum-i;
// }


// void writeToFile(PseqList &L)
// {//将线性表L中的课程信息写入 /data/workspace/myshixun/src/course1.txt
// 	FILE*fp;
//     fp=fopen("data1.txt","w");
// 	for(int i=0;i<L->curNum;i++){
// 		fprintf(fp,"%s %f %d %d %s %d\n",(L->element+i)->coursename,(L->element+i)->credit,(L->element+i)->Tperiod,(L->element+i)->Operiod,(L->element+i)->classes,(L->element+i)->term);
// 	}
// 	fclose(fp);
// }

// int destroyList_seq(PseqList &L)
// {
//     //返回值为销毁的线性表中现有数据元素的个数，若待销毁的线性表不存在，则返回0
// 	if(L==NULL){return 0;}
// 	int data=L->curNum;
// 	free(L->element);
// 	L->element=NULL;
// 	return data;
// }

// //实验一：第4关
// int locate_seq(PseqList &L,char* x)
// {//在顺序表L中查与x相同的课程名称的课程信息的下标位置，若不存在给定值，则返回-1
// 	for(int i=0;i<L->curNum;i++){
// 		if(strcmp(L->element[i].coursename,x)==0){
// 			return i;
// 		}
// 	}
// 	return -1;
// }

// DataType locatePos_seq(PseqList &L,int pos)
// {// 在顺序表L中查找指定位置pos处的数据元素，若位置非法，则返回第0个数据元素
//     if(pos>L->curNum||pos<0) { return *(L->element+0);}
// 	return *(L->element+pos);
// }

// //实验一：第5关
// int deletePos_seq(PseqList &L,int pos)
// {//在顺序表L中删除与下标pos处的数据元素，若pos非法，则返回-1；否则返回1
//     if(pos>L->curNum||pos<0) { return -1;}
// 	for(int i=pos;i<L->curNum;i++){
// 		*(L->element+i)=*(L->element+i+1);
// 	}
// 	L->curNum--;
// 	return 1;
// }

// int delete_seq(PseqList &L,char* x)
// {//在顺序表L中删除与参数x值相同的课程信息，返回删除数据元素的个数
//   //可以使用之前已完成的操作
//   int count=0;
//   	for(int i=0;i<L->curNum;i++){
// 		if(strcmp(L->element[i].coursename,x)==0){
// 			deletePos_seq(L,i);
// 			count++;i--;
// 		}
// 	}
// 	return count;
// }

// void analyse(PseqList &L)
// {//完成2个统计信息并输出统计结果
// 	float score[8]={0};
// 	int time[8]={0};
// 	for(int i=0;i<L->curNum;i++){
// 		score[(L->element+i)->term]+=(L->element+i)->credit;
// 		time[(L->element+i)->term]+=(L->element+i)->Tperiod;
// 	}
// 	for(int i=0;i<8;i++){printf("%d %f %d",i,score[i],time[i]);}
// }
// // 本关要求完成以下数据统计分析功能：
// // 1.能统计每个学期所开课程的学分、学时，并按1-8学期顺序输出；
// // 2.能统计每个类别课程的学时和学分，并统计学分占比

// //  输出样式参看预期输出
// //  统计信息1：
// //  学期 学分 学时（各属性间1个空格，每个学期一行）

// //  统计信息2
// //  课程类别 学分 学时（各属性间1个空格，每个课程类别一行）
// void bubble_sort(PseqList &L)
// {
//     DataType x;
//     for(int i=0;i<L->curNum;i++){
//         for(int j=0;j<L->curNum;j++){
//             if(strcmp(L->element[j].coursename,L->element[j+1].coursename)==1){
//                 x=L->element[j+1];
//                 L->element[j+1]=L->element[j];
//                 L->element[j]=x;
//             }
//         }
//     }
// }
// int binary_search(PseqList &L,char* x)
// {//在有序顺序表L中查找与x相同的课程名称的课程信息，若不存在给定值，则返回0
// //在函数中输出每次查找比较的顺序表中对应的数据元素（课程名称），观察和体验折半查找的过程
//     int left=0,right=L->curNum,mid=(left+right)/2;
//     for(;left<right;){
//         printf("%s\n",L->element[mid].coursename);
//         if(strcmp(L->element[mid].coursename,x)==0){return mid;}
//         if(strcmp(L->element[mid].coursename,x)==1){left=mid;}
//         if(strcmp(L->element[mid].coursename,x)==-1){right=mid;}
//         mid=(left+right)/2;
//     }
//     return 0; 
// }

// int main(){
//      PseqList head = createNullList_seq(50);
//      insertFromFile("data.txt",head);
//      writeToFile(head);
// 	bubble_sort(head);
//     printList_seq(head); printf("%d",binary_search(head,"离散数学"));
// };

// // #include<mysql.h>

// // int main(){};

#include<stdio.h>

int mystrlen(char*str){
    int len=0;
    while(str[len++]!='\0');
    return len;
}

int main(){
    printf("%d",mystrlen("mao"));
}
// #include<stdio.h>
// #include<string.h>
// struct data{
// 	char coursename[20];
// 	int num;
// 	void walk (int mm)
// 	{
// 		printf("%s����%d��\n",coursename,mm);
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

// /*�ڴ˴�����洢�γ���Ϣ�����ݽṹ���γ���Ϣ�������γ����ơ�ѧ�֡�����ѧʱ��ʵ��ѧʱ���γ���𡢿���ѧ�ڡ�*/
// typedef struct course
// {
//     char coursename[50];
//     float credit;
//     int Tperiod;
//     int Operiod;
//     char classes[10];
//     int term;

// } DataType;

// struct seqList //˳�����Ա�ṹ����
// {//��3�����ݳ�Ա
//   int MAXNUM;//���ڼ�¼˳�����Ա����ܴ�ŵ����Ԫ�ظ����� ���� MAXNUM   
//   int curNum;//���ڴ��˳�����Ա�������Ԫ�صĸ���  ����  curNum
//   DataType *element;//���ڴ��˳�����Ա�����Ԫ�ص������ռ����ʼ��ַ  
// };

// typedef struct seqList *PseqList;  
// typedef struct seqList User;

// //ʵ��һ����1��
// PseqList createNullList_seq(int m)
// {//�˴���д���룬����һ���յ�˳�����Ա��ܴ�ŵ����Ԫ�ظ���Ϊ m
//  //��m=0���򷵻�NULL 
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
// {//���������Ա��Ԫ�أ�ÿ�ſγ���Ϣһ�У��γ���Ϣ������Ԫ��֮����һ���ո�Ϊ�ָ�������
//     for(int i=0;i<L->curNum;i++){
//         printf("%s %f %d %d %s %d\n",(L->element+i)->coursename,(L->element+i)->credit,(L->element+i)->Tperiod,(L->element+i)->Operiod,(L->element+i)->classes,(L->element+i)->term);
//     }
// }


// int readFromFile(PseqList L) 
// //���ļ�course.txt ��ȡ�γ���Ϣ���������Ա�L�У�ֱ�������Ա��β���룬����ֵΪ��ȡ�Ŀγ���Ϣ��
// {
// //��ȡ�ļ�ʱ���ļ���·��/data/workspace/myshixun/src/course.txt
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

// //ʵ��һ����2��
// int isFullList_seq(PseqList &L)
// {
//   //�ж�˳�����Ա��Ƿ�������������������ֵΪ1�����򷵻�ֵΪ0
//  if(L->curNum>=L->MAXNUM){
// 	return 1;
//  }
//  return 0;
// }


// int insertP_seq(PseqList &L , int p ,DataType x)
// {// �����Ա�L���±�Ϊp��λ�ò�������Ԫ��x�����±�p�Ƿ������Ա������޷��������ݣ�����0������ɹ�����ֵΪ1
//    //������Ա����ˣ� ������"list is full"����ʾ
//   //�������λ�÷Ƿ����������ʾ"position is illegel" 
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
//  // �����Ա�L���±�Ϊp��λ�õ�ǰ���������Ԫ��x�����±�p�Ƿ������Ա������޷��������ݣ�����0������ɹ�����ֵΪ1
// //��ʾ��ֱ�ӵ���insertP����ʵ�ּ���    
//     return insertP_seq(L,p-1,x);
// }

// int insertPost_seq(PseqList &L , int p ,DataType x)
// {
//  // �����Ա�L���±�Ϊp��λ�õĺ����������Ԫ��x�����±�p�Ƿ������Ա������޷��������ݣ�����0������ɹ�����ֵΪ1
// //��ʾ��ֱ�ӵ���insertP����ʵ�ּ���    
//     return insertP_seq(L,p+1,x);
// }
// int findPos(PseqList &L, DataType x)
// {//����Ҫ����Ŀγ����� ������˳����в����λ�ã�����ֵ�ǲ���γ���Ϣ���±�λ��
// 	for(int i=0;i<L->curNum;i++){
// 		if(strcmp(L->element[i].coursename,(x.coursename))==0){
// 			return i;
// 		}
// 	}
// 	return 0;
// }

// int insertFromFile(string filename,PseqList &L )
// {
//   //��filenameΪ�ļ������ļ��ж�ȡ�γ���Ϣ����ѧ�ڡ��γ�����˳��������Ա�L��ʹ�γ���Ϣ��ѧ�ڡ��γ���������
//   //����ֵ�ǲ���γ���Ϣ������
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
// {//�����Ա�L�еĿγ���Ϣд�� /data/workspace/myshixun/src/course1.txt
// 	FILE*fp;
//     fp=fopen("data1.txt","w");
// 	for(int i=0;i<L->curNum;i++){
// 		fprintf(fp,"%s %f %d %d %s %d\n",(L->element+i)->coursename,(L->element+i)->credit,(L->element+i)->Tperiod,(L->element+i)->Operiod,(L->element+i)->classes,(L->element+i)->term);
// 	}
// 	fclose(fp);
// }

// int destroyList_seq(PseqList &L)
// {
//     //����ֵΪ���ٵ����Ա�����������Ԫ�صĸ������������ٵ����Ա����ڣ��򷵻�0
// 	if(L==NULL){return 0;}
// 	int data=L->curNum;
// 	free(L->element);
// 	L->element=NULL;
// 	return data;
// }

// //ʵ��һ����4��
// int locate_seq(PseqList &L,char* x)
// {//��˳���L�в���x��ͬ�Ŀγ����ƵĿγ���Ϣ���±�λ�ã��������ڸ���ֵ���򷵻�-1
// 	for(int i=0;i<L->curNum;i++){
// 		if(strcmp(L->element[i].coursename,x)==0){
// 			return i;
// 		}
// 	}
// 	return -1;
// }

// DataType locatePos_seq(PseqList &L,int pos)
// {// ��˳���L�в���ָ��λ��pos��������Ԫ�أ���λ�÷Ƿ����򷵻ص�0������Ԫ��
//     if(pos>L->curNum||pos<0) { return *(L->element+0);}
// 	return *(L->element+pos);
// }

// //ʵ��һ����5��
// int deletePos_seq(PseqList &L,int pos)
// {//��˳���L��ɾ�����±�pos��������Ԫ�أ���pos�Ƿ����򷵻�-1�����򷵻�1
//     if(pos>L->curNum||pos<0) { return -1;}
// 	for(int i=pos;i<L->curNum;i++){
// 		*(L->element+i)=*(L->element+i+1);
// 	}
// 	L->curNum--;
// 	return 1;
// }

// int delete_seq(PseqList &L,char* x)
// {//��˳���L��ɾ�������xֵ��ͬ�Ŀγ���Ϣ������ɾ������Ԫ�صĸ���
//   //����ʹ��֮ǰ����ɵĲ���
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
// {//���2��ͳ����Ϣ�����ͳ�ƽ��
// 	float score[8]={0};
// 	int time[8]={0};
// 	for(int i=0;i<L->curNum;i++){
// 		score[(L->element+i)->term]+=(L->element+i)->credit;
// 		time[(L->element+i)->term]+=(L->element+i)->Tperiod;
// 	}
// 	for(int i=0;i<8;i++){printf("%d %f %d",i,score[i],time[i]);}
// }
// // ����Ҫ�������������ͳ�Ʒ������ܣ�
// // 1.��ͳ��ÿ��ѧ�������γ̵�ѧ�֡�ѧʱ������1-8ѧ��˳�������
// // 2.��ͳ��ÿ�����γ̵�ѧʱ��ѧ�֣���ͳ��ѧ��ռ��

// //  �����ʽ�ο�Ԥ�����
// //  ͳ����Ϣ1��
// //  ѧ�� ѧ�� ѧʱ�������Լ�1���ո�ÿ��ѧ��һ�У�

// //  ͳ����Ϣ2
// //  �γ���� ѧ�� ѧʱ�������Լ�1���ո�ÿ���γ����һ�У�
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
// {//������˳���L�в�����x��ͬ�Ŀγ����ƵĿγ���Ϣ���������ڸ���ֵ���򷵻�0
// //�ں��������ÿ�β��ұȽϵ�˳����ж�Ӧ������Ԫ�أ��γ����ƣ����۲�������۰���ҵĹ���
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
//     printList_seq(head); printf("%d",binary_search(head,"��ɢ��ѧ"));
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
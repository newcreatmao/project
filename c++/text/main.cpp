#include<stdio.h>
int fun(int n){                    //�ж��Ƿ�Ϊ�������Ǿ���������Ƿ���1�� 
    int i,temp;
    int ans=0;
    temp=n;
    for(i=2;i<=n/2;i++)
        if(n%i==0)
          ans=1;
    if(ans==0)
        printf("%d=%d\n",temp,temp);
       return ans;
}
void fun1(int n){           //�������������ֽ⣻ 
    int num[100];int i,j,temp;
    int k=0,ans=1,sum=1;
    temp=n;
        for(i=2;i<=n;i++){         //���ѭ�����ҳ�����Ϊ������������
            if(n%i==0){
                num[k]=i;
                sum*=i;
                n=temp/sum;
                if(n==1)
                break;
                i=1;                       //i=1��������һ�ֵ�ѭ����2��ʼ��
                k++;
            }         
        }
    printf("%d=",temp);
    for(i=0;i<=k;i++){
        printf("%d",num[i]);
        if(i<k) printf("*");
    }
    printf("\n");
}
int main(){
    int  a,b,i;
    scanf("%d %d",&a,&b);
    for(i=a;i<=b;i++)
       if(fun(i))
          fun1(i);
}       



#include"Funtion.hpp"

void Print_data(int*a,int len){
    for(int i=0;i<len;i++){
        printf("%d ",*(a+i));
    }
    printf("\n");
}

void Insert_sort(int*a,int len){
    for(int i=1,key,j;i<len;i++){
        key=*(a+i);
        j=i-1;
        while(j>-1&&*(a+j)>key){
            *(a+j+1)=*(a+j);
            j--;
        }
        *(a+j+1)=key;
    }
}

void Merge(int *a, int p, int q, int r) {
//		n1和n2分别表示左边序列和右边序列的长度。左边从p开始包括q，右边从q+1开始
		int n1 = q-p+1;
		int n2 = r-q;
		int L[n1];
		int R[n2];
//		k用来表示当前遍历的数组a的索引
		int i=0,j=0,k=0;
//		分别给L和R赋值
		for(i=0,k=p; i<n1; i++,k++){
			L[i] = *(a+k);
		}
//		从右边开始
		for(j=0,k=q+1; j<n2; j++,k++){
			R[j] = *(a+k);
		}
//		比较大小,从小到大排列
		for(i=0,j=0,k=p; i<n1&&j<n2; k++){
			if(L[i] > R[j]){
				*(a+k) = R[j];
				j++;
			}else{
				*(a+k) = L[i];
				i++;
			}
		}
//		将两个数组中剩下的数放到a中
		if(i<n1){
			for(j=i; j<n1; j++,k++){
				*(a+k) = L[j];
			}
		}
		if(j<n2){
			for(i=j; i<n2; i++,k++){
				*(a+k) = R[i];
			}
		}
}

void MERGE_sort(int*a,int begin,int end){
    if(end<=begin){return;}
    else if(begin<end){
        int page=(begin+end)/2;
        MERGE_sort(a,begin,page);
        MERGE_sort(a,page+1,end);
        Merge(a,begin,page,end);

    }
}


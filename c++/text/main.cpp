// #include<iostream>
// using namespace std;

// int main(){
//     int n,locate,max=0,count,back,count1,count2;
//     cin>>n;
//     int a[n+1];a[0]=0;int recode[n+1];
//     for(int i=1;i<n+1;i++){
//         cin>>a[i];
//     }
//     for(int i=1;i<n+1;i++){
//         count=0;back=i;
//         recode[back]=1;
//         for(int k=0;k<n+1;k++){recode[k]=0;}
//         while(recode[back]<=1){
//             recode[a[back]]++;
//             back=a[back];
//             count++;
//         }
//         count1=count2=count;
//         if(count>max){max=count;}
//         if(recode[back-1]<=1&&back-1>0){
//             while(recode[back]<=1){
//             recode[a[back]]++;
//             back=a[back];
//             count1++;
//         }
//         }
//         if(recode[back+1]<=1&&back+1<n+1){
//             while(recode[back]<=1){
//             recode[a[back]]++;
//             back=a[back];
//             count2++;
//         }
//         }
//         if(count1>max){max=count1;}if(count2>max){max=count2;}
//     }
//     cout<<max;
// }

// #include<iostream>
// #include<string>
// using namespace std;
// int Get_p(string str1,string str2){
//     int count=0;
//     for(int i=0;i<str1.length()>str2.length()?str2.length():str1.length();i++){
//         if(str1[i]!=str2[i]){break;}
//         count++;
//     }
//     return count;
// }

// int main(){
//     int n,max=0;char use;
//     cin>>n;
//     string str[n];
//     for(int i=0;i<n;i++){
//         cin>>str[i];
//     }
//     for(int i=0;i<n;i++)
//     {
//         for(int k=0;k<str[i].length();k++){
//             for(int m=0;m<26;m++){
//                 use=str[i][k];
//                 str[i][k]='a'+m;
//                 int sum=0;
//                 for(int i=0;i<n-1;i++){
//                     sum+=Get_p(str[i],str[i+1]);
//                 }
//                 str[i][k]=use;
//                 if(max<sum){max=sum;}
//             }
//         }
//     }
//     cout<<max;
// }


// #include<iostream>
// using namespace std;

// int main(){
//     int n,m,l,count=0,max=0,update=0;
//     cin>>n>>m>>l;
//     char s[n],t[m];
//     cin>>s;
//     cin>>t;
//     char p;
//     for(int k=0;k<m;k++){
//     p=t[k];count=1;
//     int way[26];for(int i=0;i<26;i++){way[i]=100;}
//     way[p-'a']=0;
//     for(int i=1;i<n;i++){
//         if(way[s[i]-'a']>s[i]-p){
//            way[s[i]-'a']=s[i]-p;
//         }
//     }
//     int sum=0;
//     for(int i=0;i<m;i++){
//         if(sum>l){break;}
//         sum+=abs(way[t[i]-'a'])+update;
//         update+=way[t[i]-'a'];
//         count++;
//     }
//     if(count>max){max=count;}
//     }
//     cout<<max;
// }

// #include<bits/stdc++.h>
// using namespace std;

// int main(){
//     int n,m;
//     cin>>n>>m;

// }

// string use;
// next_permutation(use.begin(),use.end());
// sort(use.begin(),use.end());


// #include<iostream>
// using namespace std;

// int main(){
//     int n;
//     cin>>n;
//     int a[n];
//     for(int i=0;i<n;i++){
//         cin>>a[i];
//     }
//     int max1=0,max2=0,locate1,locate2;
//     locate1=locate2=0;
//     for(int i=0;i<n;i++){
//         if(max1<a[i]){max1=a[i];locate1=i;}
//     }
//         for(int i=1;i<n;i++){
//         if(max2<a[i]&&a[i]!=max1){max2=a[i];locate2=i;}
//     }
//     cout<<abs(locate1-locate2)+1;
// }


// #include<iostream>
// using namespace std;
// int main(){
//     int n,m;
//     cin>>n>>m;
//     int c[n];
//     int rd[n-1][2],cat[m][2];
//     for(int i=0;i<n;i++){
//         cin>>c[n];
//     }
//     for(int i=0;i<n-1;i++){
//         cin>>rd[i][0]>>rd[i][1];
//     }
//     for(int i=0;i<n-1;i++){
//         cin>>cat[i][0]>>cat[i][1];
//     }
//     return 0;
// }

// #include<iostream>
// using namespace std;

// int is_pre(int n){
//     n=abs(n);
//     for(int i=2;i<n;i++){
//         if(n%i==0){
//             return 0;
//         }
//     }
//     return 1;
// }

// void command(int a[],int op,int k,int x,int n){
//     if(op==1){
//         for(int i=0;i<n;i++){
//             if((i+1)%k==0){
//                 int j=0,count=x;
//                 for(j=0;j<10000;j++){
//                     if(is_pre(j+a[i])){
//                         count--;
//                         if(count==0) break;
//                     }
//                 }
//                 a[i]=j+a[i];
//             }
//         }
//     }
//     if(op==2){
//         for(int i=0;i<n;i++){
//             if((i+1)%k==0){
//                 int j=0,count=x;
//                 for(j=0;j<10000;j++){
//                     if(is_pre(a[i])-j){
//                         count--;
//                         if(count==0) break;
//                     }
//                 }
//                 a[i]=a[i]-j;
//             }
//         }
//     }
// }

// int main(){
//     int n,q;
//     cin>>n>>q;
//     int a[n],op[q],k[q],x[q];
//     for(int i=0;i<n;i++){
//         cin>>a[i];
//     }
//     for(int i=0;i<q;i++){
//         cin>>op[i]>>k[i]>>x[i];
//     }
//     for(int i=0;i<q;i++){
//         command(a,op[i],k[i],x[i],n);
//     }
//     for(int i=0;i<n;i++){
//         if(a[i]<0){a[i]=0;}
//         if(a[i]>1000000){a[i]=1;}
//         cout<<a[i]<<' ';
//     }
// }
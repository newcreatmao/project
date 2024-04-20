#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
// int main(){
//     pid_t pid;
//     pid=fork();
//     if(pid==-1){
//         printf("error\n");
//         return 0;
//     }
//     else if(pid==0){
//         printf("son\n");
//     }
//     else{
//         printf("father!son id:%d\n",pid);
//     }
//     return 0;
// }

// int main(){
//     pid_t pid,pid_wait;
//     pid=fork();
//     if(pid==-1){
//         printf("error\n");
//         return 0;
//     }
//     else if(pid==0){
//         printf("son\n");
//     }
//     else{
//         printf("father!son id:%d\n",pid);
//         pid_wait = waitpid(pid,&status,0);
//         printf("process %d return\n",pid_wait);
//     }
//     return 0;
// }

#include<iostream>
#include<stack>
#include<queue>
using namespace std;
typedef struct Bintree{
    int data;
    Bintree *lchild,*rchild;
}tree;


void visit(tree*t){
    printf("%d",t->data);
}

//栈
void npreorder(tree *t){
    stack <tree*>s;
    tree*c;
    if(t==NULL) return;
    s.push(t);
    while(!s.empty()){
        c=s.top();s.pop();
        if(c!=NULL){
            visit(c);
            s.push(c->lchild);
            s.push(c->rchild);
        }
    }
}//先序遍历

void ninorder(tree *t){ 
    stack <tree*>s;
    tree*c=t;
    if(t==NULL) return;
    while(!s.empty()||c!=NULL){
        while(c!=NULL){
           s.push(c);c=c->lchild;
        }
        c=s.top();s.pop();visit(c);
        c=c->rchild;
    }
}//中序遍历

void npostorder(tree *t){
    stack <tree*>s;
    tree*p=t;
    while(p!=NULL||!s.empty()){
        while(p!=NULL){
            s.push(p);
            p=p->lchild?p->rchild:p->rchild;
        }
        p=s.top();s.pop();visit(p);
        if(!s.empty()&&s.top()->lchild==p){
            p=p->rchild;
        }
        else p=NULL;
    }
}//后续遍历

//广度
void levelorder(tree *t){
    tree*c,*cc;
    queue<tree*>q;
    if(t==NULL) return;
    c=t;q.push(c);
    while(!q.empty()){
        c=q.front();q.pop();visit(c);
        cc=c->lchild;
        if(cc!=NULL){q.push(cc);}
        cc=c->rchild;
        if(cc!=NULL){q.push(cc);}
    }
}
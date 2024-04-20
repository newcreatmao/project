#include <stdlib.h>
#include <stdio.h>
#include "Tree.hpp"

struct Tree{
    char Flag;
    Tree_data data;
    Tree* Left;
    Tree* Right;
};

Tree* Creat_tree(){
    Tree*root;
    char flag;
    scanf("%c",&flag);
    getchar();
    if(flag=='#'){
        root=NULL;
    }
    else{
        root=(Tree*)malloc(sizeof(Tree*));
        root->Flag=flag;
        printf("请输入%c的左子树\n",root->Flag);
        root->Left=Creat_tree();
        printf("请输入%c的右子树\n",root->Flag);
        root->Right=Creat_tree();
    }
    return root;
}

void PreOrderTraverse(Tree* root){  //先序遍历
    if(root!=NULL){
        printf("%c ",root->Flag);
        PreOrderTraverse(root->Left);
        PreOrderTraverse(root->Right); 
    }
}

void InOrderTraverse(Tree* root){  //中序遍历
     if(root!=NULL){
        InOrderTraverse(root->Left);
        printf("%c ",root->Flag);
        InOrderTraverse(root->Right); 
    }
}

void PostOrderTraverse(Tree* root){  //后序遍历
    if(root!=NULL){
        PostOrderTraverse(root->Left);
        PostOrderTraverse(root->Right); 
        printf("%c ",root->Flag);
    }
}

Tree_data Get_Value_Tree(char Flag,Tree*node){
    Tree*p = Get_Node_Tree(Flag,node);
    if(p==NULL){
        printf("error Flag!\n");
    }
    return p->data;
}

Tree* Get_Node_Tree(char Flag,Tree*node){
    if(node->Flag!=Flag && node!=NULL){
        Get_Value_Tree(Flag,node->Left);
        Get_Value_Tree(Flag,node->Right);
    }
    return node;
}

void Delete_Node_Tree(char Flag,Tree*node){
    Tree*p = Get_Node_Tree(Flag,node);
    if(p==NULL){
        printf("error Flag!\n");
    }
    else{
        free(p);
        p = NULL;
        printf("Delete success!\n");
    }
}

void Put_Value_Tree(char Flag,Tree*node,Tree_data data){
    Tree* main = Get_Node_Tree(Flag,node);
    main->data = data;
}
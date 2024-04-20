#ifndef __TREE_H_
#define __TREE_H_

#include "Datatypeclass.hpp"
typedef Datatype_Tree Tree_data;
typedef struct Tree Tree;

Tree* Creat_tow_Tree(void);
void PreOrderTraverse(Tree* root);//先序遍历
void InOrderTraverse(Tree* root); //中序遍历
void PostOrderTraverse(Tree* root);//后序遍历
Tree_data Get_Value_Tree(char Flag,Tree*node);
Tree* Get_Node_Tree(char Flag,Tree*node);
void Delete_Node_Tree(char Flag,Tree*node);
void Put_Value_Tree(char Flag,Tree*node,Tree_data data);

#endif
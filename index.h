#ifndef INDEX_H_INCLUDED
#define INDEX_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct treeNode
{
    char data[20];
    int arrloc;
    void *listloc;
    struct treeNode *left;
    struct treeNode *right;
};
typedef struct treeNode treeNode;
void preOrder(treeNode *root);
/*create a new node*/
treeNode *BSI_NewNode(char *item,int arrloc,void *listloc);
/*插入节点*/
treeNode *BSI_Insert(treeNode *root,char *key,int arrloc,void *listloc);
/*到左下找最小节点*/
treeNode *BSI_Min(treeNode *root);
/*删除某个节点*/
treeNode *BSI_Delete(treeNode *root,char *key);
/*二叉搜索，用于更新索引*/
treeNode *BSI_Search(treeNode *root,char *key);
/*销毁index*/
void BSI_Destory(treeNode *root);
#endif // INDEX_H_INCLUDED

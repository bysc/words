#include "index.h"
void preOrder(treeNode *root)
{
    if(NULL==root) return;
    puts(root->data);
    preOrder(root->left);
    preOrder(root->right);
}
treeNode *BSI_NewNode(char *item,int arrloc,void *listloc)
{
    treeNode *temp=(treeNode *)malloc(sizeof(treeNode));
    strcpy(temp->data,item);
    temp->arrloc=arrloc;
    temp->listloc=listloc;
    temp->left=temp->right=NULL;
    return temp;
}

/*BSI结点插入，该方式作为叶子节点插入，返回树*/
treeNode *BSI_Insert(treeNode *root,char *key,int arrloc,void *listloc)
{
    if(NULL==root) return BSI_NewNode(key,arrloc,listloc);//插到叶子节点，但形式并不唯一，只是一种可行的方法
    if(strcmp(key,root->data)<0) root->left=BSI_Insert(root->left,key,arrloc,listloc);
    else if(strcmp(key,root->data)>0) root->right =BSI_Insert(root->right, key,arrloc,listloc);
    return root;//相等的话什么也不做
}
/*BSI的最小值，即为最左下角的节点，返回该节点*/
treeNode *BSI_Min(treeNode *root)
{
    treeNode *current=root;
    while(current&&current->left!=NULL) current=current->left;//不断移到左子树
    return current;
}
/*删除某个节点，返回树的节点*/
treeNode *BSI_Delete(treeNode *root,char *key)
{
    if(NULL==root) return root;//空树不动
    //常见的递归

    if(strcmp(key,root->data)<0) root->left=BSI_Delete(root->left,key);
    else if(strcmp(key,root->data)>0) root->right=BSI_Delete(root->right,key);
    //删除节点就是当前（子）树根节点时
    else
    {
        //只有一个孩子或者没有孩子，把孩子拿过来即可
        //没有左孩子返回右子树
        if(NULL==root->left)
        {
            treeNode *temp=root->right;//右子树
            free(root);
            return temp;
        }
        //没有右孩子返回左子树
        else if(root->right==NULL)
        {
            treeNode *temp=root->left;//左子树
            free(root);
            return temp;
        }
        //有两个孩子，用右子树最小值覆盖被删节点，再删掉右子树最小值
        else
        {
            treeNode *temp=BSI_Min(root->right);
            strcpy(root->data,temp->data);
            root->arrloc=temp->arrloc;
            root->listloc=temp->listloc;
            //不能直接free，因为最小节点不一定是叶子，而且不知道父节点
            root->right=BSI_Delete(root->right,temp->data);
        }
    }
    return root;
}
treeNode *BSI_Search(treeNode *root,char *key)
{
    treeNode *ret=root;
    if(root==NULL) return NULL;
    if(strcmp(root->data,key)>0) ret=BSI_Search(root->left,key);
    else if(strcmp(root->data,key)<0) ret=BSI_Search(root->right,key);
    return ret;
}
void BSI_Destory(treeNode *root)
{
    if(root==NULL) return;
    BSI_Destory(root->left);
    BSI_Destory(root->right);
    free(root);
}

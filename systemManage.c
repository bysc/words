#include "systemManage.h"
void test_words()
{
    WORDS *words=words_Init();
    words_Add(words,"push",VERB,"推动");
    words_Add(words,"pop",VERB,"弹");
    words_Add(words,"cherry",NOUN,"樱花");
    words_Add(words,"girl",NOUN,"女孩");
//    words_Show(words);
//    system("pause");
//    words_Delete(words,2);
    words_Show(words);
    system("pause");
    words_Save(words);
    words_Destroy(words);
}
void test_phrases()
{
    PHRASES *phrases=phrases_Init();
    printf("\n**********************\n");
    phrases_Add(phrases,"good","have a good day","玩得开心");
    phrases_Add(phrases,"nice","nice to meet you","你好");
    phrases_Add(phrases,"love","i love you","我爱你");
    phrases_Show(phrases);
    printf("\n-------------------\n");
    phrases_Delete(phrases,"love");
    phrases_Add(phrases,"good","good good study","好好学习");
    phrases_Show(phrases);
    phrases_Save(phrases);
    phrases_Destroy(phrases);
}

void sys_Init(WORDS *words,PHRASES *phrases,treeNode *root)
{
    words=words_Init();
    phrases=phrases_Init();
    words_QuickSortByTime(words,0,words->datasize);//字典乱序，防止索引树退化
    for(int i=0;i<=words->datasize;i++)
    {
        root=BSI_Insert(root,words->arr[i].spell,i,NULL);
    }
    //更新链表索引
    struct phrase *left=phrases->head,*right=phrases->head->next;
    while(right!=NULL)
    {
        if(strcmp(left->spell,right->spell)!=0)//right入索引
        {
            treeNode *location=BSI_Search(root,right->spell);
            if(location!=NULL) location->listloc=(void*)right;
        }
        else //相同往后走
        {
            left=right;
            right=right->next;
        }
    }
}
void sys_AddWord(WORDS *words,treeNode *root)
{
    return;
}

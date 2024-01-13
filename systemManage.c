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

void sys_Init(TOPCON *topcon)
{
    TOPCON *tc=topcon;
    tc->words=words_Init();
    tc->phrases=phrases_Init();
    tc->root=NULL;
    if(tc->words->datasize<0) return;
    words_QuickSortByTime(tc->words,0,tc->words->datasize);//字典乱序，防止索引树退化
    for(int i=0; i<=tc->words->datasize; i++)
    {
        tc->root=BSI_Insert(tc->root,tc->words->arr[i].spell,i,NULL);
    }
//  更新链表索引
    struct phrase *left=(tc->phrases)->head,*right=(tc->phrases)->head->next;
    while(right!=NULL)
    {
        if(strcmp(left->spell,right->spell)!=0)//right入索引
        {
            treeNode *location=BSI_Search(tc->root,right->spell);
            if(location!=NULL) location->listloc=(void*)right;
        }
//相同往后走，不同也往后走
        left=right;
        right=right->next;
    }
}
void sys_AddWord(TOPCON *topcon)
{
    TOPCON *tc=(TOPCON*)topcon;
    words_Add(tc->words,tc->spell,tc->part,tc->meaning);
    tc->root=BSI_Insert(tc->root,tc->spell,tc->words->datasize,NULL);
    return;
}
void sys_DelWord(TOPCON *topcon)
{
    treeNode *temp=BSI_Search(topcon->root,topcon->spell);
    //delete the word by index
    words_Delete(topcon->words,temp->arrloc);
    //delete the phrases
    //理论索引更快，定位到第一个节点，但不知道上一个节点地址，不更新算法的话不能用
    phrases_Delete(topcon->phrases,topcon->spell);
    //delete the index
    topcon->root=BSI_Delete(topcon->root,topcon->spell);
}
void sys_AddPhrase(TOPCON *topcon)
{
    //待更新内容
    treeNode *location=BSI_Search(topcon->root,topcon->spell);

    void *ret=phrases_Add(topcon->phrases,topcon->spell,topcon->item,topcon->meaning);
    location->listloc=ret;
}
void sys_DelPhrase(TOPCON *topcon)
{
    //待更新内容
    treeNode *location=BSI_Search(topcon->root,topcon->spell);
    phrases_Delete(topcon->phrases,topcon->spell);
    location->listloc=NULL;
}


//==================================================
char *sys_ShowWords(TOPCON *topcon)
{
    int count=topcon->words->exactsize;
    char *ret=(char*)malloc(count*50+100);
    strcpy(ret,"\tWORDS ARE AS FOLLOWS:\t\nspell\tpart.\tmeaning\n");
    if(count<0) return ret;
    for(int i=0; i<=count; i++)
    {
        if(topcon->words->arr[i].part==0) continue;
        strcat(ret,topcon->words->arr[i].spell);
        switch(topcon->words->arr[i].part)
        {
        case 1:
            strcat(ret,"\tnoun.\t");
            break;
        case 2:
            strcat(ret,"\tpron.\t");
            break;
        case 3:
            strcat(ret,"\tadj.\t");
            break;
        case 4:
            strcat(ret,"\tadv.\t");
            break;
        case 5:
            strcat(ret,"\tverb.\t");
            break;
        case 6:
            strcat(ret,"\tnum.\t");
            break;
        case 7:
            strcat(ret,"\tart.\t");
            break;
        case 8:
            strcat(ret,"\tprep.\t");
            break;
        case 9:
            strcat(ret,"\tconj.\t");
            break;
        case 10:
            strcat(ret,"\tinterj.\t");
            break;
        }
        strcat(ret,topcon->words->arr[i].meaning);
        strcat(ret,"\n");
    }
    return ret;
}
char *sys_ShowPhrases(TOPCON *topcon)
{
    int count=topcon->phrases->size;
    char *ret=(char*)malloc(count*60+160);
    strcpy(ret,"\tPHRASES ARE AS FOLLOWS:\nspell\t\titem\t\tmeaning\n");
    if(count<0) return ret;
    for(struct phrase *tmp=topcon->phrases->head->next;tmp!=NULL;tmp=tmp->next)
    {
        strcat(ret,tmp->spell);
        strcat(ret,"\t\t");
        strcat(ret,tmp->item);
        strcat(ret,"\t\t");
        strcat(ret,tmp->meaning);
        strcat(ret,"\n");
    }
    return ret;
}
char *sys_SearchWord(TOPCON *topcon)
{
    char *ret=(char*)malloc(1000);
    strcpy(ret,"the first line is word, and the others are phrases\n");
    treeNode *location=BSI_Search(topcon->root,topcon->spell);
    int i=location->arrloc;
    strcat(ret,topcon->words->arr[i].spell);
    switch(topcon->words->arr[i].part)
    {
    case 1:
        strcat(ret,"\tnoun.\t");
        break;
    case 2:
        strcat(ret,"\tpron.\t");
        break;
    case 3:
        strcat(ret,"\tadj.\t");
        break;
    case 4:
        strcat(ret,"\tadv.\t");
        break;
    case 5:
        strcat(ret,"\tverb.\t");
        break;
    case 6:
        strcat(ret,"\tnum.\t");
        break;
    case 7:
        strcat(ret,"\tart.\t");
        break;
    case 8:
        strcat(ret,"\tprep.\t");
        break;
    case 9:
        strcat(ret,"\tconj.\t");
        break;
    case 10:
        strcat(ret,"\tinterj.\t");
        break;
    }
    strcat(ret,topcon->words->arr[i].meaning);
    strcat(ret,"\n");
    struct phrase *tmp=(struct phrase*)(location->listloc);
    while(tmp!=NULL)
    {
        if(strcmp(tmp->spell,topcon->spell)) break;
        strcat(ret,tmp->spell);
        strcat(ret,"\t");
        strcat(ret,tmp->item);
        strcat(ret,"\t");
        strcat(ret,tmp->meaning);
        strcat(ret,"\n");
        tmp=tmp->next;
    }
    return ret;
}

void sys_SortWord(TOPCON *topcon)
{
    words_QuickSortByTime(topcon->words,0,topcon->words->datasize);
}

void sys_Save(TOPCON *topcon)
{
    words_Save(topcon->words);
    phrases_Save(topcon->phrases);
    words_Destroy(topcon->words);
    phrases_Destroy(topcon->phrases);
    BSI_Destory(topcon->root);
}

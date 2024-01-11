#ifndef PHRASESMANAGE_H_INCLUDED
#define PHRASESMANAGE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct phrase
{
    char spell[20];//单词
    char item[20];//短语
    char meaning[20];//意思
    struct phrase *next;
};
struct phrasesManage
{
    struct phrase *head;//头结点无数据
    struct phrase *tail;
    int size;//按数组下标计算，只有头结点为-1
};
typedef struct phrasesManage PHRASES;

PHRASES* phrases_Init();
/*有序链表的添加总是在有序单词的头部，返回单词的该单词短语首地址*/
void* phrases_Add(PHRASES *phrases,char *spell,char *item,char *meaning);
void phrases_Delete(PHRASES *phrases,char *spell);
void phrases_Show(PHRASES *phrases);
void phrases_Save(PHRASES *phrases);
void phrases_Destroy(PHRASES *phrases);
#endif // PHRASESMANAGE_H_INCLUDED

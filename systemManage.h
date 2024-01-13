#ifndef SYSTEMMANAGE_H_INCLUDED
#define SYSTEMMANAGE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "wordsManage.h"
#include "phrasesManage.h"
#include "index.h"
typedef struct
{
    WORDS *words;
    PHRASES *phrases;
    treeNode *root;
    char spell[20];
    unsigned char part;
    char item[20];
    char meaning[20];

}TOPCON;//顶层控制，用于gtk传参
void test_words();
void test_phrases();
void sys_Init(TOPCON *topcon);
void sys_AddWord(TOPCON *topcon);
void sys_DelWord(TOPCON *topcon);
void sys_AddPhrase(TOPCON *topcon);
void sys_DelPhrase(TOPCON *topcon);

//=================================
char *sys_ShowWords(TOPCON *topcon);
char *sys_ShowPhrases(TOPCON *topcon);
char *sys_SearchWord(TOPCON *topcon);
//====================================
void sys_SortWord(TOPCON *topcon);
void sys_Save(TOPCON *topcon);
#endif // SYSTEMMANAGE_H_INCLUDED

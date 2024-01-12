#ifndef SYSTEMMANAGE_H_INCLUDED
#define SYSTEMMANAGE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "wordsManage.h"
#include "phrasesManage.h"
#include "index.h"
void test_words();
void test_phrases();
void sys_Init(WORDS *words,PHRASES *phrases,treeNode *root);
void sys_AddWord(WORDS *words,treeNode *root);
#endif // SYSTEMMANAGE_H_INCLUDED

#ifndef WORDSMANAGE_H_INCLUDED
#define WORDSMANAGE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGE 255
/*
**parts define
*/
#define NOUN 1
#define PRON 2
#define ADJ 3
#define ADV 4
#define VERB 5
#define NUM 6
#define ART 7
#define PREP 8
#define CONJ 9
#define INTERJ 10
/*
**words structure define
*/
struct word{
    char spell[20];
    unsigned int time;//不重复的模拟时间戳
    unsigned char part;//词性，0表示已删除
    char meaning[20];//意思
};
struct wordsManage
{
    //以下包括文件都以下标计量
    struct word *arr;
    int exactsize;//实际数据空间
    int datasize;//数据空间，包括删除的
    int spacesize;//变量空间大小
};
typedef struct wordsManage WORDS;
WORDS* words_Init();
/*参数检测放到外面*/
void words_Add(WORDS *words,char *spell,unsigned char part, char *meaning);
/*删除数据，仅把part置0*/
void words_Delete(WORDS *words,int location);
void words_Show(WORDS *words);
void words_Swap(struct word *pa,struct word *pb);
/*按时间顺序排序*/
void words_QuickSortByTime(WORDS *words,int begin,int end);
//数据结构销毁
void words_Destroy(WORDS *words);
/*文件保存*/
void words_Save(WORDS *words);
#endif // WORDSMANAGE_H_INCLUDED

#include "wordsManage.h"
WORDS* words_Init()
{
    FILE *fp=fopen("words.bin","rb");
    WORDS *words=(WORDS*)malloc(sizeof(WORDS));
    if(fp==NULL)
    {
        words->arr=(struct word*)malloc(sizeof(struct word)*PAGE);
        words->exactsize=-1;
        words->datasize=-1;
        words->spacesize=PAGE-1;
    }
    else
    {
        fread(&(words->datasize),sizeof(int),1,fp);//读出的是下标
        words->arr=(struct word*)malloc(sizeof(struct word)*(PAGE+words->datasize));
        words->exactsize=words->datasize;
        words->spacesize=words->datasize+PAGE;
        if(words->datasize>=0)
        fread(words->arr,sizeof(struct word),words->datasize+1,fp);
        fclose(fp);
    }
    printf("%d\n",words->datasize);
    return words;
}
void words_Add(WORDS *words,char *spell,unsigned char part, char *meaning)
{
    if(words->datasize==words->spacesize-1)//内存扩展
    {
        words=(WORDS*)realloc((void*)words,words->spacesize+PAGE);
    }
    words->datasize++;
    words->exactsize++;
//赋值
    words->arr[words->datasize].time=(words->datasize==0)?0:(words->arr[words->datasize-1].time+1);
    strcpy(words->arr[words->datasize].spell,spell);
    words->arr[words->datasize].part=part;
    strcpy(words->arr[words->datasize].meaning,meaning);
    return;
}
void words_Delete(WORDS *words,int location)
{
    words->arr[location].part=0;//为0表示删除
    words->exactsize--;
}
void words_Show(WORDS *words)
{
    for(int i=0; i<=words->datasize; i++)
    {
        if(words->arr[i].part==0) continue;
        printf("%d\t%s\t",words->arr[i].time,words->arr[i].spell);
        switch(words->arr[i].part)
        {
        case 1:
            printf("noun.\t");
            break;
        case 2:
            printf("pron.\t");
            break;
        case 3:
            printf("adj.\t");
            break;
        case 4:
            printf("adv.\t");
            break;
        case 5:
            printf("verb.\t");
            break;
        case 6:
            printf("num.\t");
            break;
        case 7:
            printf("art.\t");
            break;
        case 8:
            printf("prep.\t");
            break;
        case 9:
            printf("conj.\t");
            break;
        case 10:
            printf("interj.\t");
            break;
        }
        printf("%s\n",words->arr[i].meaning);
    }
}
void words_Destroy(WORDS *words)
{
    free(words->arr);
    free(words);
}
void words_Save(WORDS *words)
{
    FILE *fp=fopen("words.bin","wb");
    fwrite(&(words->exactsize),sizeof(int),1,fp);
    for(int i=0;i<=words->datasize;i++)
    {
        if(words->arr[i].part==0) continue;
        fwrite(&(words->arr[i]),sizeof(struct word),1,fp);
    }
    fclose(fp);
}


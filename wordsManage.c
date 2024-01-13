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
void words_Swap(struct word *pa,struct word *pb)
{
    struct word tmp=(*pa);
    (*pa)=(*pb);
    (*pb)=tmp;
}
void words_QuickSortBySpell(WORDS *words,int begin,int end)
{
    if(begin>=end) return;//只有一个数不做处理
    int left=begin;
    int right=end;
    int key=begin;//判断标准，key在左边right先移动
    //目的是为了保证最后是由right走向left，而right移动时left指向的是比key指向值小的
    while(left<right)//退出循环时right走向left，且left指向比key小
    {
        //right移动时left是不大于key的
        while(strcmp(words->arr[right].spell,words->arr[key].spell)>=0&&left<right)//降序就更改right和key的比较
        {
            --right;
        }
        while(strcmp(words->arr[left].spell,words->arr[key].spell)<=0&&left<right)
        {
            ++left;
        }
        words_Swap(&(words->arr[left]),&(words->arr[right]));//大于key和小于key互换
    }
    words_Swap(&(words->arr[key]),&(words->arr[right]));//把key放到中间来，把right指向的小于key的放到前面去
    key=right;//key位置变换到中间
    words_QuickSortByTime(words,begin,key-1);//左边快速排序
    words_QuickSortByTime(words,key+1,end);//右边快速排序
}
void words_QuickSortByTime(WORDS *words,int begin,int end)
{
    if(begin>=end) return;//只有一个数不做处理
    int left=begin;
    int right=end;
    int key=begin;//判断标准，key在左边right先移动
    //目的是为了保证最后是由right走向left，而right移动时left指向的是比key指向值小的
    while(left<right)//退出循环时right走向left，且left指向比key小
    {
        //right移动时left是不大于key的
        while(words->arr[right].time>=words->arr[key].time&&left<right)//降序就更改right和key的比较
        {
            --right;
        }
        while(words->arr[left].time<=words->arr[key].time&&left<right)
        {
            ++left;
        }
        words_Swap(&(words->arr[left]),&(words->arr[right]));//大于key和小于key互换
    }
    words_Swap(&(words->arr[key]),&(words->arr[right]));//把key放到中间来，把right指向的小于key的放到前面去
    key=right;//key位置变换到中间
    words_QuickSortByTime(words,begin,key-1);//左边快速排序
    words_QuickSortByTime(words,key+1,end);//右边快速排序
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
    if(words->exactsize>=0)
    for(int i=0;i<=words->datasize;i++)
    {
        if(words->arr[i].part==0) continue;
        fwrite(&(words->arr[i]),sizeof(struct word),1,fp);
    }
    fclose(fp);
}


#include "phrasesManage.h"
PHRASES* phrases_Init()
{
    FILE *fp=fopen("phrases.bin","rb");
    //有头结点链表
    PHRASES *phrases=(PHRASES*)malloc(sizeof(PHRASES));
    phrases->head=(struct phrase*)malloc(sizeof(struct phrase));
    phrases->head->next=NULL;
    phrases->tail=phrases->head;
    phrases->head->spell[0]=0;//头结点spell最小
    if(fp==NULL)
    {
        phrases->size=-1;
    }
    else
    {
        fread(&(phrases->size),sizeof(int),1,fp);
        if(phrases->size>=0)
        for(int i=0;i<=phrases->size;i++)
        {
            struct phrase *new_item=(struct phrase*)malloc(sizeof(struct phrase));
            fread(new_item,sizeof(struct phrase),1,fp);
            new_item->next=NULL;
            phrases->tail->next=new_item;
            phrases->tail=new_item;
            /*写入的next指针现在全是错的，需要重新连接*/
        }
    }
    return phrases;
}
void* phrases_Add(PHRASES *phrases,char *spell,char *item,char *meaning)
{
    struct phrase *new_item=(struct phrase*)malloc(sizeof(struct phrase));
    strcpy(new_item->spell,spell);
    strcpy(new_item->item,item);
    strcpy(new_item->meaning,meaning);
    new_item->next=NULL;
    phrases->size++;
//    phrases->tail->next=new_item;
    /*有序链表*/
    struct phrase *travel=phrases->head;
    while(travel->next!=NULL)
    {
        if(strcmp(travel->spell,spell)<0&&strcmp(travel->next->spell,spell)>=0)
        {
            new_item->next=travel->next;
            travel->next=new_item;
            return new_item;
        }
        travel=travel->next;
    }
    travel->next=new_item;//作为尾结点
    return new_item;
}
void phrases_Delete(PHRASES *phrases,char *spell)
{
    struct phrase *left=phrases->head,*right=phrases->head;
    //left和right都指向已访问结点
    while(right->next!=NULL)
    {
        right=right->next;
        if(strcmp(right->spell,spell)==0)//匹配成功
        {
            left->next=right->next;
            free(right);
            right=left;
            phrases->size--;
        }
        else
        {
            left=right;//left右移
        }
    }
}
void phrases_Show(PHRASES *phrases)
{
    struct phrase *travel=phrases->head->next;
    while(travel!=NULL)
    {
        printf("%s\t\t%s\t\t%s\n",travel->spell,travel->item,travel->meaning);
        travel=travel->next;
    }
}
void phrases_Save(PHRASES *phrases)
{
    FILE *fp=fopen("phrases.bin","wb");
    fwrite(&(phrases->size),sizeof(int),1,fp);
    struct phrase *travel=phrases->head->next;
    if(phrases->size>=0)
    for(int i=0; i<=phrases->size; i++)
    {
        fwrite(travel,sizeof(struct phrase),1,fp);
        travel=travel->next;
    }
    fclose(fp);
}
void phrases_Destroy(PHRASES *phrases)
{
    while(phrases->head!=NULL)
    {
        phrases->tail=phrases->head->next;
        free(phrases->head);
        phrases->head=phrases->tail;
    }
    free(phrases);
}

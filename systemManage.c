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

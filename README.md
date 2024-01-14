# 功能
- 登录
- 添加单词
- 删除单词
- 添加已有单词的短语
- 删除已有单词的全部短语
- 显示全部单词
- 显示全部短语
- 单词按字典顺序全部显示（初始化按添加顺序显示）
- 搜索已有单词以及其全部短语
- 退出并保存文件
# 实现
- 单词表：动态数组，单词为主键
- 短语表：有序链表，单词为外键
- 索引：二叉搜索树，以单词字典顺序构件索引，包含单词表下标和短语表对应单词部分的首地址
# 封装
将三个表的封装再封装在一个结构体中，用于gtk的回调函数传参
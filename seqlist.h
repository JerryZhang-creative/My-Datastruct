#ifndef SEQLIST_H
#define SEQLIST_H

#define MaxiSize 15
typedef int ElementType;
typedef struct
{
    ElementType* data;
    int last_ptr;
    int capacity;
} Seqlist;

// 创建并初始化顺序表
Seqlist* seqCreate();
// 扩充顺序表的大小
int seqExpend(Seqlist* list);
// 往顺序表指定位置插入元素
void insertElement(Seqlist* list, ElementType val, int index);
// 往顺序表追加元素
void appendElement(Seqlist* list, ElementType val);
// 拷贝顺序表
Seqlist* copy(Seqlist* list);
// 反转顺序表
Seqlist* seqReverse(Seqlist* list);
// 删除第一个匹配的元素
void deleteElement(Seqlist* list, ElementType val);
// 删除指定索引的值并返回
ElementType deleteIndexElement(Seqlist* list, int index);
// 清空顺序表
void clear(Seqlist* list);
// 销毁顺序表
void seqDestroy(Seqlist* list);
// 获取给定索引的元素
ElementType getElement(Seqlist* list, int index);
// 获取元素的索引
int getIndex(Seqlist* list, ElementType val);
// 获取顺序表的长度
int seqLength(Seqlist* list);
// 遍历顺序表中的元素
void seqTraverse(Seqlist* list);
// 判断顺序表是否已满
int isFull(Seqlist* list);
// 判断顺序表是否为空表
int isEmpty(Seqlist* list);
// 更改顺序表中指定索引的值
void changeByIndex(Seqlist* list, int index, ElementType val);
// 更改顺序表中所有匹配的值并返回修改次数
int changeByValue(Seqlist* list, ElementType old_val, ElementType new_val);
#endif

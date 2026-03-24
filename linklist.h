#ifndef LINKLIST_H
#define LINKLIST_H

typedef int ElementType;
typedef struct node {   // 定义节点
    ElementType val;    // 定义数据域
    struct node* next;  // 定义指针域
} Node;
typedef struct Linklist {  // 定义链表
    Node* head;            // 定义首元结点
    Node* tail;            // 定义尾指针
    long length;           // 定义链表长度
} Linklist;

// 创建节点并初始化
Node* nodeCreate();
// 创建并初始化链表
Linklist* linklistCreate();
// 反转链表
Linklist* linklistReverse(Linklist* list);
// 拷贝链表
Linklist* linklistCopy(Linklist* list);
// 往链表的指定位置添加元素
void insertElement(Linklist* list, ElementType val, int index);
// 往链表追加元素
void appendElement(Linklist* list, ElementType val);
// 往链表前添加元素
void prevpendElement(Linklist* list, ElementType val);
// 合并链表
Linklist* linklistMerge(Linklist* list_1, Linklist* list_2);
// 删除第一个匹配的元素
void deleteByElement(Linklist* list, ElementType val);
// 删除指定索引的值并返回
ElementType deleteByIndex(Linklist* list, int index);
// 清空链表
void linklistClear(Linklist* list);
// 销毁链表
void linklistDestroy(Linklist* list);
// 获取给定索引的元素
ElementType getElement(Linklist* list, int index);
// 获取元素第一次出现时的索引
int getIndex(Linklist* list, ElementType val);
// 获取链表的长度
int linklistLength(Linklist* list);
// 遍历链表中的元素
void linklistTraverse(Linklist* list);
// 判断链表是否为空表
int isEmpty(Linklist* list);
// 更改链表中指定索引的值
void changeByIndex(Linklist* list, int index, ElementType val);
// 更改链表中所有匹配的值并返回修改次数
int changeByValue(Linklist* list, ElementType old_val, ElementType new_val);
#endif

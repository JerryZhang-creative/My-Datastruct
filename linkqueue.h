#ifndef LINKQUEUE_H
#define LINKQUEUE_H

typedef int ElementType;
typedef struct queueNode {
    struct queueNode* prev;
    struct queueNode* next;
    ElementType val;
} queueNode;

typedef struct linkQueue {
    queueNode* head;
    queueNode* tail;
    int length;
} linkQueue;

// 创建并初始化节点
queueNode* queueNodeCreate(ElementType val);
// 创建并初始化链队
linkQueue* linkQueueCreate();
// 前置插入
int linkQueuePrevpend(linkQueue* queue, ElementType val);
// 后置插入
int linkQueueAppend(linkQueue* queue, ElementType val);
// 前置出队
void linkQueueGetTop(linkQueue* queue, ElementType* result);
// 后置出队
void linkQueueGetLast(linkQueue* queue, ElementType* result);
// 查看首元素的值
void linkQueueCheckTop(linkQueue* queue, ElementType* result);
// 查看尾元素的值
void linkQueueCheckLast(linkQueue* queue, ElementType* result);
// 销毁链队
void linkQueueDestroy(linkQueue* queue);
#endif

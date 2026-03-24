#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#define MAXISIZE 15

typedef int ElementType;
typedef struct seqQueue {
    ElementType* data;
    int tail;
    int front;
    int length;
    int capacity;
} seqQueue;

// 创建并初始化顺序队列
seqQueue* seqQueueCreate();
// 扩充顺序队列
int seqQueueExpend(seqQueue* queue);
// 往顺序队列添加值
void seqQueuePush(seqQueue* queue, ElementType val);
// 取出顺序队列的首元素
ElementType seqQueuePop(seqQueue* queue);
// 查看顺序队列的首元素
ElementType seqQueueCheck(seqQueue* queue);
//销毁顺序队列
void seqQueueDestroy(seqQueue* queue);
#endif

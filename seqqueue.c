#include "seqqueue.h"

#include <stdlib.h>

// 创建并初始化顺序队列
seqQueue* seqQueueCreate() {
    seqQueue* queue = (seqQueue*)malloc(sizeof(seqQueue));  // 为顺序队列申请空间
    if (queue == NULL) return NULL;                         // 如果空间申请失败, 返回NULL

    ElementType* data = (ElementType*)malloc(sizeof(ElementType) * MAXISIZE);  // 为数据域申请空间
    if (data == NULL) {                                                        // 如果申请失败, 释放顺序队列的空间, 返回NULL
        free(queue);
        return NULL;
    }

    /*初始化顺序队列*/
    queue->capacity = MAXISIZE;
    queue->data = data;
    queue->front = 0;
    queue->tail = 0;
    queue->length = 0;

    return queue;  // 返回顺序队列
}

// 扩充顺序队列
int seqQueueExpend(seqQueue* queue) {
    if (queue == NULL || queue->data == NULL) return 0;  // 如果顺序队列为空, 或者数据域为空, 返回0表示扩充失败

    int newCapacity = queue->capacity * 2;                                        // 将新数据域的大小扩大至原来的2倍
    ElementType* data = (ElementType*)malloc(sizeof(ElementType) * newCapacity);  // 为新数据域申请空间
    if (data == NULL) return 0;                                                   // 如果申请失败, 返回0表示扩充失败

    /*复制旧数据至新的数据域*/
    for (int i = 0; i < queue->length; ++i) {
        data[i] = queue->data[(i + queue->front) % queue->capacity];
    }

    free(queue->data);  // 释放旧数据域

    /*更新顺序队列*/
    queue->data = data;
    queue->capacity = newCapacity;
    queue->front = 0;
    queue->tail = queue->length;

    return 1;  // 返回1表示扩充成功
}

// 往顺序队列添加值
void seqQueuePush(seqQueue* queue, ElementType val) {
    if (queue == NULL || queue->data == NULL) return;  // 如果顺序队列为空, 或者数据域为空, 返回

    /*如果顺序队列已满, 扩充队列*/
    if (queue->length == queue->capacity) {
        if (!seqQueueExpend(queue)) return;
    }

    /*更新顺序队列*/
    queue->data[queue->tail] = val;
    queue->tail = (queue->tail + 1) % queue->capacity;
    ++queue->length;
}

// 取出顺序队列的首元素
ElementType seqQueuePop(seqQueue* queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0) return -1;  // 如果顺序队列为空, 数据域为空, 或者数据域中没有元素, 返回-1

    /*取出队首元素, 并更新顺序队列*/
    ElementType val = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    --queue->length;

    return val;  // 返回首元素的值
}

// 查看顺序队列的首元素
ElementType seqQueueCheck(seqQueue* queue) {
    if (queue == NULL || queue->data == NULL || queue->length == 0) return -1;  // 如果顺序队列为空, 数据域为空, 或者数据域中没有元素, 返回-1

    return queue->data[queue->front];  // 返回队首元素
}

// 销毁顺序队列
void seqQueueDestroy(seqQueue* queue) {
    if (queue == NULL) return;  // 如果顺序队列为空, 返回

    /*如果数据域为空,
    释放队列结构的空间, 返回*/
    if (queue->data == NULL) {
        free(queue);
        return;
    }

    /*释放数据域空间,
    释放队列空间*/
    free(queue->data);
    free(queue);
}

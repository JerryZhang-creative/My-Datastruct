#include "linkqueue.h"

#include <stdlib.h>

// 创建并初始化节点
queueNode* queueNodeCreate(ElementType val) {
    queueNode* node = (queueNode*)malloc(sizeof(queueNode));  // 为节点申请空间
    if (node == NULL) return NULL;                            // 如果申请失败, 返回NULL

    /*初始化节点*/
    node->next = NULL;
    node->prev = NULL;
    node->val = val;

    return node;  // 返回节点
}

// 创建并初始化链队
linkQueue* linkQueueCreate() {
    linkQueue* queue = (linkQueue*)malloc(sizeof(linkQueue));  // 为链队申请空间
    if (queue == NULL) return NULL;                            // 如果申请失败, 返回NULL

    /*初始化链队*/
    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;

    return queue;  // 返回链队
}

// 前置插入
int linkQueuePrevpend(linkQueue* queue, ElementType val) {
    if (queue == NULL) return 0;  // 如果链队为空, 返回0表示失败

    queueNode* node = queueNodeCreate(val);  // 创建节点
    if (node == NULL) return 0;              // 如果创建失败, 返回0表示失败

    /*插入节点*/
    if (queue->length == 0) {
        queue->tail = node;
        queue->head = node;
    } else {
        node->next = queue->head;
        queue->head->prev = node;
        queue->head = node;
    }

    ++queue->length;  // 更新链队长度

    return 1;  // 返回1表示成功
}

// 后置插入
int linkQueueAppend(linkQueue* queue, ElementType val) {
    if (queue == NULL) return 0;             // 如果链队为空, 返回0表示失败

    queueNode* node = queueNodeCreate(val);  // 创建节点
    if (node == NULL) return 0;              // 如果创建失败, 返回0表示失败
    
    /*插入节点*/
    if (queue->length == 0) {
        queue->tail = node;
        queue->head = node;
    } else {
        node->prev = queue->tail;
        queue->tail->next = node;
        queue->tail = node;
    }
    
    ++queue->length;  // 更新链队长度

    return 1;  // 返回1表示成功
}

// 前置出队
void linkQueueGetTop(linkQueue* queue, ElementType* result) {
    if (queue == NULL || queue->length == 0) return;
    *result = queue->head->val;
    queueNode* tmp = queue->head;
    if (queue->length == 1) {
        queue->tail = NULL;
        queue->head = NULL;
    } else {
        queue->head = tmp->next;
        queue->head->prev = NULL;
    }
    tmp->next = NULL;
    free(tmp);
    --queue->length;
}

// 后置出队
void linkQueueGetLast(linkQueue* queue, ElementType* result) {
    if (queue == NULL || queue->length == 0) return;
    *result = queue->tail->val;
    queueNode* tmp = queue->tail;
    if (queue->length == 1) {
        queue->tail = NULL;
        queue->head = NULL;
    } else {
        queue->tail = tmp->prev;
        queue->tail->next = NULL;
        tmp->prev = NULL;
    }
    free(tmp);
    --queue->length;
}

// 查看首元素的值
void linkQueueCheckTop(linkQueue* queue, ElementType* result) {
    if (queue == NULL || queue->length == 0) return;
    *result = queue->head->val;
}

// 查看尾元素的值
void linkQueueCheckLast(linkQueue* queue, ElementType* result) {
    if (queue == NULL || queue->length == 0) return;
    *result = queue->tail->val;
}

// 销毁链队
void linkQueueDestroy(linkQueue* queue) {
    if (queue == NULL) return;
    queueNode* currentNode = NULL;
    while (queue->head != NULL) {
        currentNode = queue->head;
        queue->head = currentNode->next;
        if (queue->head != NULL) queue->head->prev = NULL;
        currentNode->next = NULL;
        free(currentNode);
    }
    queue->tail = NULL;
    free(queue);
}

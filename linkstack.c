#include "linkstack.h"

#include <stdlib.h>

// 创建并初始化链栈
linkStack* linkStackCreate() {
    linkStack* stack = (linkStack*)malloc(sizeof(linkStack));  // 为链栈申请空间
    if (stack == NULL) {                                       // 如果申请失败, 返回NULL
        return NULL;
    }

    /*链栈初始化*/
    stack->head = NULL;
    stack->length = 0;

    return stack;  // 返回链栈
}

// 往链栈中添加元素
void linkStackPush(linkStack* stack, ElementType val) {
    if (stack == NULL) return;  // 如果链栈为空, 返回

    linkNode* node = (linkNode*)malloc(sizeof(linkNode));  // 为插入节点申请空间
    if (node == NULL) return;                              // 如果申请失败, 返回

    /*初始化节点*/
    node->val = val;
    node->next = stack->head;

    /*更新链栈数据*/
    stack->head = node;
    ++stack->length;
}

// 查看链栈中的首元素
ElementType linkStackGetTop(linkStack* stack) {
    if (stack == NULL || stack->length == 0) return -1;  // 如果链栈为空值, 或者链栈是空栈, 返回-1

    return stack->head->val;  // 返回首结点的值
}

// 取出栈顶元素
ElementType linkStackPop(linkStack* stack) {
    if (stack == NULL || stack->length == 0) return -1;  // 如果链栈为空值, 或者链栈是空栈, 返回-1

    /*获取链栈的头结点, 以及它的值*/
    linkNode* currentNode = stack->head;
    ElementType val = currentNode->val;

    /*更新链栈数据*/
    stack->head = currentNode->next;
    --stack->length;

    /*将节点的指针域置空, 并释放空间*/
    currentNode->next = NULL;
    free(currentNode);

    return val;  // 返回节点值
}

// 销毁栈
void linkStackDestroy(linkStack* stack) {
    if (stack == NULL) return;  // 如果链栈为空, 返回

    linkNode* currentNode = NULL;         //   记录当前节点
    while (stack->head != NULL) {         // 遍历链栈的节点
        currentNode = stack->head;        // 获取头节点
        stack->head = currentNode->next;  // 更新头节点
        currentNode->next = NULL;         // 将指针域置空
        free(currentNode);                // 释放空间
        --stack->length;                  // 更新链栈长度
    }

    free(stack);  // 释放链栈空间
}
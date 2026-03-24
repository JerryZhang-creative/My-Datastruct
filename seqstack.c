#include "seqstack.h"

#include <stdlib.h>
#define Volume 15

// 创建并初始化顺序栈
seqStack* seqStackCreate() {
    /*为顺序栈申请空间,
    如果申请失败, 返回NULL*/
    seqStack* stack = (seqStack*)malloc(sizeof(seqStack));
    if (stack == NULL) return NULL;

    /*为顺序栈数据域申请空间,
    如果申请失败, 释放栈的空间
    返回NULL*/
    ElementType* data = (ElementType*)malloc(sizeof(ElementType) * Volume);
    if (data == NULL) {
        free(stack);
        return NULL;
    }

    /*初始化顺序栈*/
    stack->capacity = Volume;
    stack->data = data;
    stack->tail = -1;

    return stack;  // 返回顺序栈
}

// 往顺序栈中添加元素
void seqStackPush(seqStack* stack, ElementType val) {
    if (stack == NULL || stack->data == NULL) return;  // 如果顺序栈为空或数据域为空, 直接返回

    /*判断顺序栈是否已满,
    已满则扩容, 扩容失败则返回*/
    if (isFull(stack)) {
        if (!seqStackExpand(stack)) {
            return;
        }
    }

    ++stack->tail;                   // 移动栈顶位置
    stack->data[stack->tail] = val;  // 添加元素
}

// 顺序栈扩容
int seqStackExpand(seqStack* stack) {
    if (stack == NULL) return 0;  // 如果顺序栈为空, 返回0表示失败

    /*翻倍扩容数据域,
    如果扩容失败,
    给出提示并返回*/
    ElementType* data = (ElementType*)malloc(sizeof(ElementType) * (stack->capacity * 2));
    if (data == NULL) {
        return 0;
    }

    /*复制数据域*/
    for (int i = 0; i <= stack->tail; ++i) {
        data[i] = stack->data[i];
    }

    free(stack->data);     // 释放旧数据域
    stack->data = data;    // 更新数据域
    stack->capacity *= 2;  // 更新容量

    return 1;  // 返回1表示成功
}
// 查看顺序栈中的首元素
ElementType seqStackGetTop(seqStack* stack) {
    if (isEmpty(stack)) return -1;  // 如果顺序栈为空, 或数据域为空, 返回-1

    return stack->data[stack->tail];
}

// 判断顺序栈是否已满
int isFull(seqStack* stack) {
    if (stack == NULL || stack->data == NULL) return 0;  // 如果顺序栈为空, 或数据域为空, 返回0
    return stack->tail == stack->capacity - 1;
}

// 判断顺序栈是否为空
int isEmpty(seqStack* stack) {
    return (stack == NULL || stack->tail != -1);
}

// 取出栈顶元素
ElementType seqStackPop(seqStack* stack) {
    if (stack == NULL || stack->data == NULL || stack->tail == -1) return -1;
    ElementType val = stack->data[stack->tail];
    --stack->tail;
    return val;
}

// 销毁栈
void seqStackDestroy(seqStack* stack) {
    if (stack == NULL) return;  // 如果顺序栈为空, 返回
    if (stack->data != NULL) {
        free(stack->data);  // 释放数据域
    }
    free(stack);  // 释放栈结构体
}

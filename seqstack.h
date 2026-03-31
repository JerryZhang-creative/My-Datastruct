#ifndef SEQSTACK_H
#define SEQSTACK_H

#define DefaultSize 15
typedef int ElementType;
typedef struct seqStack {
    ElementType* data;  // 定义数据域记录数据
    int tail;           // 记录栈顶位置
    int capacity;       // 记录顺序栈的容量
} seqStack;

// 创建并初始化顺序栈
seqStack* seqStackCreate();
// 往顺序栈中添加元素
void seqStackPush(seqStack* stack, ElementType val);
// 顺序栈扩容
int seqStackExpand(seqStack* stack);
// 查看顺序栈中的首元素
ElementType seqStackGetTop(seqStack* seqStack);
// 判断顺序栈是否为空
int isEmpty(seqStack* stack);
// 判断顺序栈是否已满
int isFull(seqStack* stack);
// 取出栈顶元素
ElementType seqStackPop(seqStack* stack);
// 销毁栈
void seqStackDestroy(seqStack* stack);
#endif
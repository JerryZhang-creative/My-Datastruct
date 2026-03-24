#ifndef LINKSTACK_H
#define LINKSTACK_H

typedef int ElementType;  // 定义数据类型
/*定义链栈节点*/
typedef struct linkNode {
    ElementType val;        // 定义数据域
    struct linkNode* next;  // 记录下一个节点的指针
} linkNode;

typedef struct {
    linkNode* head;
    int length;
} linkStack;

// 创建并初始化链栈
linkStack* linkStackCreate();
// 往链栈中添加元素
void linkStackPush(linkStack* stack, ElementType val);
// 查看链栈中的首元素
ElementType linkStackGetTop(linkStack* stack);
// 取出栈顶元素
ElementType linkStackPop(linkStack* stack);
// 销毁栈
void linkStackDestroy(linkStack* stack);
#endif
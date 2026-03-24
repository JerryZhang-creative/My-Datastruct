#include "linklist.h"

#include <stdio.h>
#include <stdlib.h>

// 创建节点并初始化
Node* nodeCreate() {
    Node* node = (Node*)malloc(sizeof(Node));  // 为节点申请空间
    if (node == NULL) return NULL;             // 如果申请失败, 返回NULL

    /*初始化节点*/
    node->next = NULL;
    node->val = 0;

    return node;  // 返回创建的节点
}

// 创建并初始化链表
Linklist* linklistCreate() {
    Linklist* list = (Linklist*)malloc(sizeof(Linklist));  // 为链表申请空间
    if (list == NULL) {                                    // 如果申请失败, 给出提示并返回NULL
        return NULL;
    }

    /*初始化链表*/
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;  // 返回创建的链表
}

// 反转链表
Linklist* linklistReverse(Linklist* list) {
    if (list == NULL) return NULL;  // 如果原链表为空, 直接返回NULL

    Linklist* reverseList = linklistCreate();
    if (reverseList == NULL) return NULL;  // 如果链表创建失败, 直接返回NULL

    Node* srcNode = list->head;     // 记录原链表的结点
    while (srcNode != NULL) {       // 遍历原链表以获取结点的值
        Node* node = nodeCreate();  // 创建节点并初始化
        /*如果链表创建失败,
        销毁链表并直接返回NUULL*/
        if (node == NULL) {
            linklistDestroy(reverseList);
            return NULL;
        }

        node->val = srcNode->val;  // 将原链表的值赋值给新节点
        /*采用头插法的方式反转链表,
        更新链表的大小*/
        if (reverseList->head == NULL) {
            reverseList->head = node;
            reverseList->tail = node;
            ++reverseList->length;
        } else {
            node->next = reverseList->head;
            reverseList->head = node;
            ++reverseList->length;
        }

        srcNode = srcNode->next;  // 更新节点
    }

    return reverseList;  // 返回反转后的链表
}

// 拷贝链表
Linklist* linklistCopy(Linklist* list) {
    if (list == NULL) return NULL;  // 如果原链表为空, 直接返回NULL

    Linklist* copyList = linklistCreate();  // 创建链表并初始化
    if (copyList == NULL) return NULL;      // 如果创建失败, 直接返回NULL

    Node* srcNode = list->head;     // 获取原链表的结点
    while (srcNode != NULL) {       // 遍历原链表以获取结点的值
        Node* node = nodeCreate();  // 创建节点并初始化
        /*如果链表创建失败,
        销毁链表并直接返回NUULL*/
        if (node == NULL) {
            linklistDestroy(copyList);
            return NULL;
        }

        node->val = srcNode->val;  // 将原链表的值赋值给新节点
        if (copyList->head == NULL) {
            copyList->head = node;
            copyList->tail = node;
        } else {
            copyList->tail->next = node;  // 将节点插入链表
            copyList->tail = node;        // 更新尾节点
        }
        ++copyList->length;       // 更新链表的长度
        srcNode = srcNode->next;  // 更新原节点
    }

    return copyList;  // 返回复制的链表
}

// 往链表的指定位置添加元素
void insertElement(Linklist* list, ElementType val, int index) {
    if (list == NULL) return;  // 如果原链表为空, 直接返回

    if (index < 0 || index > list->length) {  // 如果索引不合法, 返回
        return;
    }

    Node* insertNode = nodeCreate();  // 创建插入节点
    if (insertNode == NULL) return;   // 如果节点创建失败, 直接返回

    insertNode->val = val;  // 为插入节点赋值

    /*插入节点*/
    if (index == 0) {
        insertNode->next = list->head;
        list->head = insertNode;
        if (list->length == 0) {  // 如果链表为空表, 更新尾指针
            list->tail = insertNode;
        }
    } else if (index == list->length) {
        list->tail->next = insertNode;
        list->tail = insertNode;
    } else {
        /*获取插入位置的前一个节点*/
        Node* prevNode = list->head;
        for (int i = 1; i < index; ++i) {
            prevNode = prevNode->next;
        }

        insertNode->next = prevNode->next;  // 更新插入节点的指针域
        prevNode->next = insertNode;        // 将节点插入
    }
    ++list->length;  // 更新链表的长度
}

// 往链表追加元素
void appendElement(Linklist* list, ElementType val) {
    if (list == NULL) return;  // 如果原链表为空, 直接返回

    Node* appendNode = nodeCreate();  // 创建节点
    if (appendNode == NULL) {         // 如果创建节点失败, 返回
        return;
    }

    appendNode->val = val;    // 为追加节点赋值
    if (list->length == 0) {  // 如果链表为空表, 更新头节点
        list->head = appendNode;
    } else {
        list->tail->next = appendNode;  // 追加节点
    }
    list->tail = appendNode;  // 更新尾指针
    ++list->length;           // 更新长度
}

// 往链表前添加元素
void prevpendElement(Linklist* list, ElementType val) {
    if (list == NULL) return;  // 如果原链表为空, 直接返回

    Node* prevpendNode = nodeCreate();  // 创建节点
    if (prevpendNode == NULL) {         // 如果创建失败, 返回
        return;
    }

    prevpendNode->val = val;  // 为节点赋值
    if (list->length == 0) {  // 如果链表为空表, 更新尾节点
        list->tail = prevpendNode;
    }
    prevpendNode->next = list->head;  // 插入节点
    list->head = prevpendNode;        // 更新头指针
    ++list->length;                   // 更新长度
}

// 合并链表
Linklist* linklistMerge(Linklist* list_1, Linklist* list_2) {
    /*创建链表1和链表2的副本,
    如果创建失败,
    释放空间, 返回NULL*/
    Linklist* prevList = linklistCopy(list_1);
    Linklist* tailList = linklistCopy(list_2);
    if (prevList == NULL || tailList == NULL) {
        free(prevList);
        free(tailList);
        return NULL;
    }

    /*如果其中一个为空链表,
    则直接返回另一个链表*/
    if (prevList->length == 0) return tailList;
    if (tailList->length == 0) return prevList;

    prevList->tail->next = tailList->head;  // 合并两个链表
    prevList->length += tailList->length;   // 更新长度
    prevList->tail = tailList->tail;        // 更新尾指针

    free(tailList);  // 释放空间

    return prevList;  // 返回合并后的链表
}

// 删除第一个匹配的元素
void deleteByElement(Linklist* list, ElementType val) {
    if (list == NULL) return;       // 如果链表为空, 直接返回
    if (list->length == 0) return;  // 如果链表为空表, 直接返回

    Node* currentNode = list->head;  // 记录当前节点
    Node* prevNode = NULL;           // 记录当前节点的前一个节点

    while (currentNode != NULL) {       // 遍历节点
        if (currentNode->val == val) {  // 节点的值与给定值匹配
            /*如果当前节点为头节点,
            更新头节点*/
            if (currentNode == list->head) {
                list->head = currentNode->next;
                /*如果链表的长度为一,
                更新尾节点*/
                if (list->length == 1) {
                    list->tail = NULL;
                }
            }
            /*如果当前节点为尾节点,
            更新尾指针*/
            else if (currentNode == list->tail) {
                prevNode->next = NULL;
                list->tail = prevNode;
            }
            /*更新链接,
            删除当前节点*/
            else {
                prevNode->next = currentNode->next;
            }

            free(currentNode);  // 释放空间
            --list->length;     // 更新长度
            return;
        }

        /*指针同步后移*/
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

// 删除指定索引的值并返回
ElementType deleteByIndex(Linklist* list, int index) {
    if (list == NULL) return -1;               // 如果链表为空, 返回-1
    if (list->length == 0) return -1;          // 如果链表为空表, 返回-1
    if (index < 0 || index >= list->length) {  // 如果索引不合法, 返回-1
        return -1;
    }

    Node* currentNode = list->head;  // 记录要删除的节点
    Node* prevNode = NULL;           // 记录删除结点的前驱

    /*移动指针到指定位置,
    prevNode为它的前驱*/
    for (int i = 0; i < index; ++i) {
        prevNode = currentNode;
        currentNode = currentNode->next;
    }

    /*更新链接*/
    if (index == 0) {  // 如果指定位置为头节点, 更新头指针
        list->head = currentNode->next;
        if (list->length == 1) {  // 如果链表长度为一, 更新尾指针
            list->tail = NULL;
        }
    } else if (index == list->length - 1) {  // 如果当前节点为尾节点
        prevNode->next = NULL;               // 更新前驱节点的指针域
        list->tail = prevNode;               // 更新尾节点
    } else {
        prevNode->next = currentNode->next;  // 更新链接, 删除当前节点
    }

    ElementType val = currentNode->val;  // 记录当前节点的值
    free(currentNode);                   // 释放空间
    --list->length;                      // 更新链表长度
    return val;                          // 返回删除节点的值域
}

// 清空链表
void linklistClear(Linklist* list) {
    if (list == NULL) return;  // 如果原链表为空, 直接返回

    Node* freeNode = list->head;    // 记录当前要释放的节点
    Node* nextNode = NULL;          // 记录当前节点的下一个节点
    while (freeNode != NULL) {      // 遍历链表
        nextNode = freeNode->next;  // 更新下一个节点
        free(freeNode);             // 释放空间
        freeNode = nextNode;        // 更新释放节点
    }
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
}

// 销毁链表
void linklistDestroy(Linklist* list) {
    if (list == NULL) return;  // 如果原链表为空, 直接返回

    Node* freeNode = list->head;    // 记录当前要释放的节点
    Node* nextNode = NULL;          // 记录当前节点的下一个节点
    while (freeNode != NULL) {      // 遍历链表
        nextNode = freeNode->next;  // 更新下一个节点
        free(freeNode);             // 释放空间
        freeNode = nextNode;        // 更新释放节点
    }

    free(list);  // 释放空间
}

// 获取给定索引的元素
ElementType getElement(Linklist* list, int index) {
    if (list == NULL) return -1;               // 如果链表为空, 返回-1
    if (list->length == 0) return -1;          // 如果链表为空表, 返回-1
    if (index < 0 || index >= list->length) {  // 如果索引不合法, 返回-1
        return -1;
    }

    Node* currentNode = list->head;   // 记录当前节点
    if (index == list->length - 1) {  // 如果索引为链表的长度-1, 直接返回尾结点的值
        return list->tail->val;
    }

    for (int i = 0; i < index; ++i) {  // 跳转至指定位置
        currentNode = currentNode->next;
    }
    return currentNode->val;  // 返回指定节点的值
}

// 获取元素第一次出现时的索引
int getIndex(Linklist* list, ElementType val) {
    if (list == NULL) return -1;       // 如果链表为空, 返回-1
    if (list->length == 0) return -1;  // 如果链表为空表, 返回-1

    int counter = 0;                    // 记录索引
    Node* currentNode = list->head;     // 记录当前节点
    while (currentNode != NULL) {       // 遍历节点
        if (currentNode->val == val) {  // 如果找到匹配的节点, 返回索引
            return counter;
        }
        /*更新索引和节点*/
        ++counter;
        currentNode = currentNode->next;
    }
    return -1;  // 元素不在链表中
}

// 获取链表的长度
int linklistLength(Linklist* list) {
    if (list == NULL) return -1;  // 如果链表为空, 返回-1

    return list->length;  // 返回链表长度
}

// 遍历链表中的元素
void linklistTraverse(Linklist* list) {
    if (list == NULL) return;       // 如果链表为空, 直接返回
    if (list->length == 0) return;  // 如果链表为空表, 直接返回

    Node* currentNode = list->head;  // 记录当前节点
    while (currentNode != NULL) {    // 遍历节点
        printf("%d ", currentNode->val);
        currentNode = currentNode->next;
    }
    printf("\n");
}

// 判断链表是否为空表
int isEmpty(Linklist* list) {
    if (list == NULL) return 0;  // 如果链表为空, 返回0

    return list->length == 0;
}
// 更改链表中指定索引的值
void changeByIndex(Linklist* list, int index, ElementType val) {
    if (list == NULL) return;                  // 如果链表为空, 直接返回
    if (list->length == 0) return;             // 如果链表为空表, 直接返回
    if (index < 0 || index >= list->length) {  // 如果索引不合法, 返回
        return;
    }

    Node* currentNode = list->head;    // 记录当前节点
    for (int i = 0; i < index; ++i) {  // 跳转至指定位置
        currentNode = currentNode->next;
    }
    currentNode->val = val;
}
// 更改链表中所有匹配的值并返回修改次数
int changeByValue(Linklist* list, ElementType old_val, ElementType new_val) {
    if (list == NULL) return 0;       // 如果链表为空, 返回0
    if (list->length == 0) return 0;  // 如果链表为空表, 返回0

    int counter = 0;                 // 记录更改次数
    Node* currentNode = list->head;  // 记录当前节点
    while (currentNode != NULL) {    // 遍历所有节点
        /*如果当前结点的值是需要更改的值,
        更改当前结点的值,
        更新计数器*/
        if (currentNode->val == old_val) {
            currentNode->val = new_val;
            ++counter;
        }

        currentNode = currentNode->next;  // 更新指针
    }
    return counter;  // 返回更改次数
}

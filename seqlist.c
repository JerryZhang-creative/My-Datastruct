#include "seqlist.h"

#include <stdio.h>
#include <stdlib.h>

// 创建并初始化顺序表
Seqlist* seqCreate() {
    Seqlist* list = (Seqlist*)malloc(sizeof(Seqlist));  // 创建顺序表
    if (list == NULL) {                                 // 如果顺序表不存在, 返回NULL
        return NULL;
    }

    /*为顺序表的数据域申请空间,
    如果申请失败, 释放顺序表的空间,
    返回NULL*/
    list->data = (ElementType*)malloc(sizeof(ElementType) * MaxiSize);
    if (list->data == NULL) {
        free(list);
        return NULL;
    }

    list->last_ptr = -1;        // 将顺序表的尾指针初始化为-1,表示为空表
    list->capacity = MaxiSize;  // 初始化顺序表的最大容量, 初始值为MaxiSize
    return list;                // 返回顺序表对象
}

// 扩充顺序表的大小
int seqExpend(Seqlist* list) {
    if (list == NULL) {  // 如果顺序表不存在, 返回0
        return 0;
    }

    ElementType* arr = (ElementType*)malloc(sizeof(ElementType) * (list->capacity * 2));  // 为顺序表的数据域重新分配内存
    if (arr == NULL) {                                                                    // 如果扩容失败, 返回0
        return 0;
    }

    for (int i = 0; i < list->last_ptr + 1; ++i) {
        arr[i] = list->data[i];  // 将旧数据域的元素迁移到新数据域
    }

    free(list->data);     // 释放旧的数据域
    list->data = arr;     // 更新顺序表的数据域
    list->capacity *= 2;  // 更新顺序表的最大容量

    return 1;
}

// 往顺序表指定位置插入元素
void insertElement(Seqlist* list, ElementType val, int index) {
    if (list == NULL) {  // 如果顺序表不存在, 返回
        return;
    }

    if (index < 0 || index > list->last_ptr + 1) {  // 如果索引不合法, 返回
        return;
    }

    if (isFull(list)) {
        if (!seqExpend(list)) return;  // 如果顺序表已满, 扩充顺序表
    }

    for (int i = list->last_ptr; i >= index; --i) {  // 将index之后的元素往后移
        list->data[i + 1] = list->data[i];
    }
    list->data[index] = val;  // 在index位置插入元素
    list->last_ptr++;         // 更新尾指针
}

// 往顺序表追加元素
void appendElement(Seqlist* list, ElementType val) {
    if (list == NULL) {  // 如果顺序表不存在, 返回
        return;
    }

    if (isFull(list))
        seqExpend(list);  // 如果顺序表已满, 扩充顺序表

    list->data[++list->last_ptr] = val;  // 在顺序表的末尾追加元素并更新尾指针
}

// 拷贝顺序表
Seqlist* copy(Seqlist* list) {
    if (list == NULL) {  // 如果顺序表不存在, 返回NULL
        return NULL;
    }

    /*为复制顺序表申请空间,
    如果申请失败, 返回NULL*/
    Seqlist* copy_list = (Seqlist*)malloc(sizeof(Seqlist));
    if (copy_list == NULL) {
        return NULL;
    }

    /*复制属性*/
    copy_list->capacity = list->capacity;
    copy_list->last_ptr = list->last_ptr;

    /*为顺序表的数据域申请空间,
    如果申请失败, 释放顺序表的空间
    返回NULL*/
    copy_list->data = (ElementType*)malloc(sizeof(ElementType) * copy_list->capacity);
    if (copy_list->data == NULL) {
        free(copy_list);
        return NULL;
    }

    for (int i = 0; i <= copy_list->last_ptr; ++i) {  // 拷贝顺序表数据域
        copy_list->data[i] = list->data[i];
    }

    return copy_list;  // 返回复制的顺序表
}

// 反转顺序表
Seqlist* seqReverse(Seqlist* list) {
    if (list == NULL) {  // 如果顺序表不存在, 返回NULL
        return NULL;
    }

    /*为反转顺序表申请空间,
    如果申请失败, 返回NULL*/
    Seqlist* rever_list = (Seqlist*)malloc(sizeof(Seqlist));
    if (rever_list == NULL) {
        return NULL;
    }

    /*复制属性*/
    rever_list->capacity = list->capacity;
    rever_list->last_ptr = list->last_ptr;

    /*为顺序表的数据域申请空间,
    如果申请失败, 释放顺序表的空间
    返回NULL*/
    rever_list->data = (ElementType*)malloc(sizeof(ElementType) * rever_list->capacity);
    if (rever_list->data == NULL) {
        free(rever_list);
        return NULL;
    }

    /*反转复制数据域*/
    for (int i = 0, j = list->last_ptr; j >= 0; ++i, --j) {
        rever_list->data[i] = list->data[j];
    }

    return rever_list;  // 返回反转的顺序表
}

// 删除第一个值匹配的元素
void deleteElement(Seqlist* list, ElementType val) {
    if (list == NULL) {  // 如果顺序表不存在, 返回
        return;
    }

    int index = -1;                              // 记录索引的值
    for (int i = 0; i <= list->last_ptr; ++i) {  // 获取值匹配的第一个元素的索引
        if (list->data[i] == val) {
            index = i;
            break;
        }
    }

    if (index == -1) return;  // 如果没有匹配的元素, 返回

    for (int j = index; j < list->last_ptr; ++j) {  // 将第index之后的元素前移
        list->data[j] = list->data[j + 1];
    }

    --list->last_ptr;  // 更新尾指针
}

// 删除指定索引的值并返回
ElementType deleteIndexElement(Seqlist* list, int index) {
    if (list == NULL) {  // 如果顺序表不存在, 返回-1
        return -1;
    }

    if (index < 0 || index > list->last_ptr) {  // 如果索引不合法, 返回-1
        return -1;
    }

    ElementType val;  // 用于记录数据
    val = list->data[index];

    for (int i = index; i < list->last_ptr; ++i) {  // 将index后面的值前移
        list->data[i] = list->data[i + 1];
    }
    --list->last_ptr;  // 更新末尾位置

    return val;  // 返回index位置的值
}

// 清空顺序表
void clear(Seqlist* list) {
    if (list == NULL) {  // 如果顺序表不存在, 返回
        return;
    }

    list->last_ptr = -1;  // 将尾指针重置
}

// 销毁顺序表
void seqDestroy(Seqlist* list) {
    if (list == NULL) return;  // 如果顺序表不存在, 返回

    if (list->data != NULL) {
        free(list->data);  // 释放顺序表的数据域
        list->data = NULL;
    }

    free(list);  // 将顺序表的存储空间释放
}

// 获取给定索引的元素
ElementType getElement(Seqlist* list, int index) {
    if (list == NULL || list->data == NULL) return -1;  // 如果顺序表不存在, 或者数据域为空, 返回-1

    return list->data[index];
}

// 获取指定元素的第一个索引
int getIndex(Seqlist* list, ElementType val) {
    if (list == NULL || list->data == NULL) return -1;  // 如果顺序表不存在, 或者数据域为空, 返回-1

    for (int i = 0; i <= list->last_ptr; ++i) {
        if (list->data[i] == val)
            return i;  // 如果元素存在于顺序表, 则返回对应索引
    }

    return -1;  // 如果元素不存在于顺序表, 则返回-1
}

// 获取顺序表的长度
int seqLength(Seqlist* list) {
    if (list == NULL || list->data == NULL) return -1;  // 如果顺序表不存在, 或者数据域为空, 返回-1

    return list->last_ptr + 1;
}

// 遍历顺序表中的元素
void seqTraverse(Seqlist* list) {
    if (list == NULL || list->data == NULL) return;  // 如果顺序表不存在, 或者数据域为空, 返回

    for (int i = 0; i < seqLength(list); ++i) {  // 逐一输出顺序表的元素
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 判断顺序表是否已满
int isFull(Seqlist* list) {
    if (list == NULL || list->data == NULL) return 0;  // 如果顺序表不存在, 或者数据域为空, 返回0

    return list->last_ptr == list->capacity - 1;  // 如果尾指针的值为最大容量-1, 则顺序表已满
}

// 判断顺序表是否为空表
int isEmpty(Seqlist* list) {
    if (list == NULL || list->data == NULL) return 0;  // 如果顺序表不存在, 或者数据域为空, 返回0

    return list->last_ptr == -1;  // 如果尾指针的值为-1, 则顺序表为空表
}

// 更改顺序表中指定索引的值
void changeByIndex(Seqlist* list, int index, ElementType val) {
    if (list == NULL || list->data == NULL) return;  // 如果顺序表不存在, 或者数据域为空, 返回

    if (index < 0 || index > list->last_ptr) {  // 如果索引不合法, 返回
        return;
    }

    list->data[index] = val;
}

// 更改顺序表中所有匹配的值并返回修改次数
int changeByValue(Seqlist* list, ElementType old_val, ElementType new_val) {
    if (list == NULL || list->data == NULL) return -1;  // 如果顺序表不存在, 或者数据域为空, 返回-1

    int count = 0;
    for (int i = 0; i <= list->last_ptr; ++i) {
        if (list->data[i] == old_val) {
            ++count;
            list->data[i] = new_val;
        }
    }
    return count;
}

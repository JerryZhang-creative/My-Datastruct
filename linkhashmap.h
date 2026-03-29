#ifndef LINKHASHMAP_H
#define LINKHASHMAP_H
#define DefaultSize 17

typedef int ValType;
typedef struct node {
    ValType val;
    struct node* next;
    struct node* prev;
} Node;
typedef struct linkHashMap {
    Node** buckets;
    unsigned int size;
    unsigned int capacity;
} linkHashMap;

// 定义哈希算法
int hash(linkHashMap* map, ValType val);
// 创建并初始化节点
Node* nodeCreate();
// 创建并初始化哈希表
linkHashMap* linkHashMapCreate();
// 扩充哈希表
int linkHashMapExpend(linkHashMap* map);
// 更新哈希表的值
void linkHashMapUpdate(linkHashMap* map, ValType val);
// 删除哈希表的值
void linkHashMapDelete(linkHashMap* map, ValType val);
// 清空哈希表
void linkHashMapClear(linkHashMap* map);
// 查询哈希表的值
int linkHashMapCheck(linkHashMap* map, ValType val);
// 销毁哈希表
void linkHashMapDestroy(linkHashMap* map);
#endif
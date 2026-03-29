#include "linkhashmap.h"

#include <stdlib.h>

// 定义哈希算法
int hash(linkHashMap* map, ValType val) {
    int buckt_index = (val ^ map->capacity) % map->capacity;
    return buckt_index;
}

// 创建并初始化节点
Node* nodeCreate() {
    /*为节点申请空间,
    申请失败则返回NULL*/
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) return NULL;

    /*初始化节点, 并返回节点*/
    node->next = NULL;
    node->prev = NULL;
    node->val = 0;
    return node;
}

// 创建并初始化哈希表
linkHashMap* linkHashMapCreate() {
    /*为哈希表申请空间, 申请失败则返回NULL*/
    linkHashMap* map = (linkHashMap*)calloc(1, sizeof(linkHashMap));
    if (map == NULL) return NULL;

    /*为哈希表申请空间,
    申请失败则释放map空间,
    返回NULL*/
    map->buckets = (Node**)calloc(DefaultSize, sizeof(Node*));
    if (map->buckets == NULL) {
        free(map);
        return NULL;
    }

    /*为每个桶的哨兵节点申请空间,
    如果申请失败则释放已经申请的空间
    返回NULL*/
    for (int i = 0; i < DefaultSize; ++i) {
        map->buckets[i] = nodeCreate();
        if (map->buckets[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(map->buckets[j]);
            }
            free(map->buckets);
            free(map);
            return NULL;
        }
    }

    /*初始化设置,
    返回map*/
    map->capacity = DefaultSize;
    return map;
}

// 扩充哈希表
int linkHashMapExpend(linkHashMap* map) {
    /*如果map为空, 则返回0表示失败*/
    if (map == NULL) return 0;

    /*申请新的桶空间,
    申请失败则释放空间,
    返回0*/
    Node** tmp = (Node**)calloc(map->capacity * 2, sizeof(Node*));
    if (tmp == NULL) return 0;
    for (int j = 0; j < map->capacity * 2; ++j) {
        tmp[j] = (Node*)calloc(1, sizeof(Node));
        if (tmp[j] == NULL) {
            for (int k = 0; k < j; ++k) {
                free(tmp[k]);
            }
            free(tmp);
            return 0;
        }
    }

    /*迁移数据域*/
    Node** oldBuckets = map->buckets;
    int oldCapacity = map->capacity;
    int newCapacity = oldCapacity * 2;
    map->capacity = newCapacity;
    for (int i = 0; i < oldCapacity; ++i) {
        if (oldBuckets[i]->val != 0) {
            Node* node = oldBuckets[i]->next;
            while (node != NULL) {
                Node* currentNode = node;
                int index = hash(map, currentNode->val);
                node = node->next;
                if (node != NULL) {
                    node->prev = currentNode->prev;
                }
                currentNode->next = NULL;
                currentNode->prev->next = node;
                currentNode->prev = tmp[index];
                currentNode->next = tmp[index]->next;
                if (tmp[index]->next != NULL) {
                    tmp[index]->next->prev = currentNode;
                }
                tmp[index]->next = currentNode;
                ++tmp[index]->val;
            }
        }
    }

    /*释放旧数据域*/
    for (int m = 0; m < oldCapacity; ++m) {
        free(map->buckets[m]);
    }
    free(map->buckets);

    /*更新数据域, 返回1表示成功*/
    map->buckets = tmp;
    return 1;
}

// 更新哈希表的值
void linkHashMapUpdate(linkHashMap* map, ValType val) {
    if (map == NULL) return;  // 如果map为空, 放回

    /*如果val已存在, 不做处理,
    不存在则添加val*/
    int bucketIndex = hash(map, val);
    if (map->buckets[bucketIndex]->val != 0) {
        Node* currentNode = map->buckets[bucketIndex]->next;
        while (currentNode) {
            if (currentNode->val == val) return;
            currentNode = currentNode->next;
        }
    }

    /*创建新的节点, 创建失败则返回*/
    Node* addNode = nodeCreate();
    if (addNode == NULL) return;

    /*负载因子大于5, 扩容,
    重新计算桶的位置*/
    if (map->size * 1.0 / map->capacity >= 5) {
        linkHashMapExpend(map);
        bucketIndex = hash(map, val);
    }

    /*初始化节点, 并更新信息*/
    addNode->val = val;
    addNode->next = map->buckets[bucketIndex]->next;
    addNode->prev = map->buckets[bucketIndex];
    if (map->buckets[bucketIndex]->next != NULL) {
        map->buckets[bucketIndex]->next->prev = addNode;
    }
    map->buckets[bucketIndex]->next = addNode;
    ++map->size;
    ++map->buckets[bucketIndex]->val;
}

// 删除哈希表的值
void linkHashMapDelete(linkHashMap* map, ValType val) {
    if (map == NULL) return;  // rugomap为空, 返回

    /*查找炸了,
    如果val存在于map中则删除*/
    int index = hash(map, val);
    Node* currentNode = map->buckets[index]->next;
    while (currentNode) {
        if (currentNode->val == val) {
            currentNode->prev->next = currentNode->next;
            if (currentNode->next != NULL) {
                currentNode->next->prev = currentNode->prev;
            }
            currentNode->next = NULL;
            currentNode->prev = NULL;
            free(currentNode);
            --map->size;
            --map->buckets[index]->val;
            return;
        }
        currentNode = currentNode->next;
    }
}

// 清空哈希表
void linkHashMapClear(linkHashMap* map) {
    if (map == NULL || map->size == 0) return;  // 如果map中没有数据, 返回

    /*由内到外释放空间,
    更新信息*/
    for (int i = 0; i < map->capacity; ++i) {
        if (map->buckets[i]->val == 0) continue;
        Node* currentNode = map->buckets[i]->next;
        while (currentNode) {
            Node* nextNode = currentNode->next;
            free(currentNode);
            currentNode = nextNode;
        }
        map->buckets[i]->next = NULL;
        map->buckets[i]->val = 0;
    }
    map->size = 0;
}

// 查询哈希表的值
int linkHashMapCheck(linkHashMap* map, ValType val) {
    if (map == NULL || map->size == 0) return 0;  // 如果map中没有数据, 返回0表示失败

    /*查找val, 如果存在则返回1*/
    int index = hash(map, val);
    if (map->buckets[index]->val == 0) return 0;
    Node* currentNode = map->buckets[index]->next;
    while (currentNode) {
        if (currentNode->val == val) return 1;
        currentNode = currentNode->next;
    }

    return 0;  // map中不存在val, 返回0
}

// 销毁哈希表
void linkHashMapDestroy(linkHashMap* map) {
    if (map == NULL) return;  // 如果map为空, 返回

    /*由内到外释放空间*/
    for (int i = 0; i < map->capacity; ++i) {
        Node* currentNode = map->buckets[i]->next;
        Node* nextNode = NULL;
        while (currentNode) {
            nextNode = currentNode->next;
            free(currentNode);
            currentNode = nextNode;
        }
        free(map->buckets[i]);
    }
    free(map->buckets);
    free(map);
}

#include "seqhashmap.h"

#include <stdlib.h>
#include <string.h>

// 获取对应插入位置
int hash(seqHashMap* map, KeyType key) {
    if (map == NULL || map->buckets == NULL) return -1;  // 判空, 返回-1

    /*采用开放寻址的方法查找插入索引*/
    int index = key % map->capacity;
    while (map->buckets[index]) {
        index = (++index) % map->capacity;
    }

    return index;  // 返回索引
}

// 解析位置
int dehash(seqHashMap* map, KeyType key) {
    if (map == NULL || map->buckets == NULL) return -1;  // 判空, 返回-1

    /*采用开放寻址的方法查找对应索引,
    如果查找对象存在哈希表中, 则返回对应索引,
    若查找对象不在哈希表中, 则跳出循环*/
    int index = key % map->capacity;
    int startIndex = index;
    while (map->buckets[index] != NULL) {
        if (map->buckets[index]->key == key) return index;
        index = (++index) % map->capacity;
        if (index == startIndex) break;
    }

    return -1;  // 返回-1, 查找对象不在哈希表中
}

// 创建键值对
pair* pairCreate(KeyType key, ValType val) {
    /*为键值对申请空间,
    如果申请失败, 返回NULL*/
    pair* item = (pair*)malloc(sizeof(pair));
    if (item == NULL) return NULL;

    /*初始化键值对*/
    item->key = key;
    item->val = strdup(val);

    return item;  // 返回键值对
}

// 创建哈希表
seqHashMap* hashMapCreate() {
    /*为哈希表申请空间,
   如果申请失败, 返回NULL*/
    seqHashMap* map = (seqHashMap*)malloc(sizeof(seqHashMap));
    if (map == NULL) return NULL;

    /*为哈希表数据域申请空间,
    如果申请失败, 释放哈希表空间
    返回NULL*/
    map->buckets = (pair**)calloc(DefaultSize, sizeof(pair*));
    if (map->buckets == NULL) {
        free(map);
        return NULL;
    }

    /*初始化哈希表*/
    map->capacity = DefaultSize;
    map->size = 0;

    return map;  // 返回哈希表
}

// 扩容哈希表
int hashMapExpend(seqHashMap* map) {
    if (map == NULL) return 0;  // 判空, 返回0表示失败

    /*申请新的数据域,
    申请失败, 返回0表示扩容失败*/
    pair** tempBuckets = (pair**)calloc(map->capacity * 2, sizeof(pair*));
    if (tempBuckets == NULL) return 0;

    /*记录哈希表的旧数据*/
    int oldCapacity = map->capacity;
    pair** oldBuckets = map->buckets;

    /*更新哈希表*/
    map->buckets = tempBuckets;
    map->capacity *= 2;

    /*迁移数据域*/
    for (int i = 0; i < oldCapacity; ++i) {
        if (oldBuckets[i] == NULL) continue;
        int index = hash(map, oldBuckets[i]->key);
        map->buckets[index] = oldBuckets[i];
    }

    free(oldBuckets);  // 释放旧数据域

    return 1;  // 返回1, 表示扩容成功
}

// 销毁哈希表
void hashMapDestroy(seqHashMap** map) {
    if (*map == NULL || map == NULL) return;  // 判空, 直接返回

    seqHashMap* tempMap = *map;  // 解第一层引用, 获取哈希表

    /*先释放每个键值对数据的空间,
    在释放每个键值对的空间,
    最后释放整个数据域的空间*/
    if (tempMap->buckets != NULL) {
        for (int i = 0; i < tempMap->capacity; ++i) {
            if (tempMap->buckets[i]) {
                free(tempMap->buckets[i]->val);
                free(tempMap->buckets[i]);
            }
        }
        free(tempMap->buckets);
    }

    /*释放哈希表的空间,
    将指针置空*/
    free(tempMap);
    *map = NULL;
}

// 删除哈希表中的键值对
void hashMapDeleteElement(seqHashMap* map, KeyType key) {
    /*解析位置, 如果不存在哈希表, 返回*/
    int index = dehash(map, key);
    if (index == -1) return;

    /*释放键值对的数据域空间,
    在释放键值对的空间,
    指针置空*/
    free(map->buckets[index]->val);
    free(map->buckets[index]);
    map->buckets[index] = NULL;

    /*将下一个键值对开始,
    直到遇到空桶前,
    采用重排法重新排列,
    更新哈希表大小*/
    index = (index + 1) % map->capacity;
    while (map->buckets[index]) {
        pair* rehash = map->buckets[index];
        map->buckets[index] = NULL;
        int newIndex = hash(map, rehash->key);
        map->buckets[newIndex] = rehash;
        index = (index + 1) % map->capacity;
    }
    --map->size;
}

// 更新哈希表元素
void hashMapUpdate(seqHashMap* map, KeyType key, ValType val) {
    if (map == NULL) return;  // 判空, 返回

    /*解析位置, 如果不存在哈希表中,
    则添加进哈希表中, 如果存在哈希表中,
    则更新数据域*/
    int index = dehash(map, key);
    if (index == -1) {
        if (map->size * 1.0 / map->capacity > 0.75) {
            int res = hashMapExpend(map);
            if (res == 0 && map->size == map->capacity) return;
        }
        pair* insertPair = pairCreate(key, val);
        if (insertPair == NULL) return;
        index = hash(map, key);
        map->buckets[index] = insertPair;
        ++map->size;
        return;
    }
    free(map->buckets[index]->val);
    map->buckets[index]->val = strdup(val);
}

// 查看对应键的值
void hashMapCheckVal(seqHashMap* map, KeyType key, ValType* result) {
    if (map == NULL || result == NULL) return;  // 判空, 返回

    /*解析位置, 如果不存在哈希表中, 返回,
    存在则更新result*/
    int index = dehash(map, key);
    if (index == -1) return;
    *result = map->buckets[index]->val;
}

// 获取所有的键
KeyType* keyTravese(seqHashMap* map) {
    if (map == NULL || map->size == 0) return NULL;  // 判空, 返回

    /*申请空间用于存放所有的键,
    申请失败则返回NULL,
    获取所有的键, 并返回*/
    KeyType* keys = (KeyType*)calloc(sizeof(KeyType), map->size);
    if (!keys) return NULL;
    for (int i = 0, count = 0; count < map->size && i < map->capacity; ++i) {
        if (map->buckets[i]) {
            keys[count] = map->buckets[i]->key;
            ++count;
        }
    }
    return keys;
}

// 获取所有的值
ValType* valTravese(seqHashMap* map) {
    if (map == NULL || map->size == 0) return NULL;  // 判空, 返回

    /*申请空间用于存放所有的值,
    申请失败则返回NULL,
    获取所有的值, 并返回*/
    ValType* vals = (ValType*)calloc(sizeof(ValType), map->size);
    if (!vals) return NULL;
    for (int i = 0, count = 0; count < map->size && i < map->capacity; ++i) {
        if (map->buckets[i]) {
            vals[count] = map->buckets[i]->val;
            ++count;
        }
    }
    return vals;
}

// 查看所有键值对
pair* pairTraverse(seqHashMap* map) {
    if (map == NULL || map->size == 0) return NULL;  // 判空, 返回

    /*申请空间用于存放所有的键值对,
    申请失败则返回NULL,
    获取所有的键值对, 并返回*/
    pair* items = (pair*)calloc(sizeof(pair), map->size);
    if (!items) return NULL;
    for (int i = 0, count = 0; count < map->size && i < map->capacity; ++i) {
        if (map->buckets[i]) {
            items[count] = *map->buckets[i];
            ++count;
        }
    }
    return items;
}

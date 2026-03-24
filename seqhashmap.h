#ifndef SEQHASHMAP_H
#define SEQHASHMAP_H

#define DefaultSize 20  // 定义默认最小值

typedef char* ValType;
typedef int KeyType;
typedef struct pair {
    KeyType key;
    ValType val;
} pair;

typedef struct seqHashMap {
    pair** buckets;
    int size;
    int capacity;
} seqHashMap;

// 获取对应插入位置
int hash(seqHashMap* map, KeyType key);
// 解析位置
int dehash(seqHashMap* map, KeyType key);
// 创建键值对
pair* pairCreate(KeyType key, ValType val);
// 创建哈希表
seqHashMap* hashMapCreate();
// 扩容哈希表
int hashMapExpend(seqHashMap* map);
// 销毁哈希表
void hashMapDestroy(seqHashMap** map);
// 删除哈希表中的键值对
void hashMapDeleteElement(seqHashMap* map, KeyType key);
// 更新哈希表元素
void hashMapUpdate(seqHashMap* map, KeyType key, ValType val);
// 查看对应键的值
void hashMapCheckVal(seqHashMap* map, KeyType key, ValType* result);
// 获取所有的键
KeyType* keyTravese(seqHashMap* map);
// 获取所有的值
ValType* valTravese(seqHashMap* map);
// 查看所有键值对
pair* pairTraverse(seqHashMap* map);
#endif
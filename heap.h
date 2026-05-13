#ifndef SEQBINARYTREE_H
#define SEQBINARYTREE_H

#define DefaultSize 16

typedef int ElementType;
typedef struct {
    unsigned int size;
    unsigned int capacity;
    ElementType* data;
} Heap;

// 创建堆
Heap* newHeap();
// 扩展堆
int extend(Heap* heap);
// 大顶堆插入元素
void maxHeapInsert(Heap* heap, ElementType element);
// 小顶堆插入元素
void minHeapInsert(Heap* heap, ElementType element);
// 元素出堆
ElementType maxPop(Heap* heap);
ElementType minPop(Heap* heap);
// 销毁堆
void heapDestroy(Heap* heap);
// 交换位置
void swap(ElementType* arr, unsigned int left, unsigned int right);
// 查找父节点
unsigned int parent(unsigned int child);

#endif
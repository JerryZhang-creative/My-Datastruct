#include "seqbinarytree.h"

#include <stdlib.h>

// 创建堆
Heap* newHeap() {
    Heap* heap = calloc(1, sizeof(Heap));
    if (heap) {
        heap->data = (Heap*)calloc(DefaultSize, sizeof(ElementType));
        heap->capacity = DefaultSize;
        if (heap->data) return heap;
    }
    return NULL;
}

// 扩展堆
int extend(Heap* heap) {
    if (!heap || heap->size == 0) return 0;
    unsigned int newCapacity = heap->capacity * 2;
    ElementType* newData = (ElementType*)calloc(newCapacity, sizeof(ElementType));
    if (!newData) return 0;
    for (int i = 0; i < heap->size; ++i) {
        newData[i] = heap->data[i];
    }
    free(heap->data);
    heap->data = newData;
    heap->capacity = newCapacity;
    return 1;
}

// 大顶堆插入元素(
int maxHeapInsert(Heap* heap, ElementType element) {
    if (!heap) return 0;
    if (heap->capacity == heap->size) extend(heap);
    unsigned int index = heap->size;
    heap->data[index] = element;
    heap->size++;
    while (index > 0 && element > heap->data[parent(index)]) {
        swap(heap->data, parent(index), index);
        index = parent(index);
    }
    return 1;
}

// 小顶堆插入元素
int minHeapInsert(Heap* heap, ElementType element) {
    if (!heap) return 0;
    if (heap->capacity == heap->size) extend(heap);
    unsigned int index = heap->size;
    heap->data[index] = element;
    heap->size++;
    while (index > 0 && element < heap->data[parent(index)]) {
        swap(heap->data, parent(index), index);
        index = parent(index);
    }
    return 1;
}

// 元素出堆
ElementType maxPop(Heap* heap) {
    if (!heap) return 0;
    ElementType top;
    top = heap->data[0];
    heap->data[0] = heap->data[--(heap->size)];

    int curr = 0;
    while (1) {
        unsigned int largest = curr;
        unsigned int lchild = 2 * curr + 1;
        unsigned int rchild = 2 * curr + 2;
        if (lchild < heap->size && heap->data[largest] < heap->data[lchild]) {
            largest = lchild;
        }
        if (rchild < heap->size && heap->data[largest] < heap->data[rchild]) {
            largest = rchild;
        }

        if (largest != curr) {
            swap(heap->data, curr, largest);
            curr = largest;
        } else {
            break;
        }
    }
    return top;
}

ElementType minPop(Heap* heap) {
    if (!heap) return 0;
    ElementType top;
    top = heap->data[0];
    heap->data[0] = heap->data[--(heap->size)];

    int curr = 0;
    while (1) {
        unsigned int least = curr;
        unsigned int lchild = 2 * curr + 1;
        unsigned int rchild = 2 * curr + 2;
        if (lchild < heap->size && heap->data[least] > heap->data[lchild]) {
            least = lchild;
        }
        if (rchild < heap->size && heap->data[least] > heap->data[rchild]) {
            least = rchild;
        }

        if (least != curr) {
            swap(heap->data, curr, least);
            curr = least;
        } else {
            break;
        }
    }
    return top;
}

// 销毁堆
void heapDestroy(Heap* heap) {
    if (!heap) return;
    free(heap->data);
    free(heap);
}

// 交换位置
void swap(ElementType* arr, unsigned int left, unsigned int right) {
    ElementType tmp;
    tmp = arr[left];
    arr[left] = arr[right];
    arr[right] = tmp;
}

// 查找父节点
unsigned int parent(unsigned int child) {
    if (child == 0) return 0;
    return (int)(child - 1) / 2;
}
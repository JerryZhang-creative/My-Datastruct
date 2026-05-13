#include "heap.h"

#include <stdlib.h>

// 创建堆
Heap* newHeap() {
    /*动态申请空间并初始化
    申请失败则返回NULL
    */
    Heap* heap = calloc(1, sizeof(Heap));
    if (heap) {
        heap->data = (ElementType*)calloc(DefaultSize, sizeof(ElementType));
        if (!heap->data) {
            free(heap);
            return NULL;
        }
        heap->capacity = DefaultSize;
        if (heap->data) return heap;
    }
    return NULL;
}

// 扩展堆
int extend(Heap* heap) {
    if (!heap) return 0;  // 判空保护

    unsigned int newCapacity = heap->capacity * 2;                                  // 设置新的容量
    ElementType* newData = (ElementType*)calloc(newCapacity, sizeof(ElementType));  // 重新申请空间
    if (!newData) return 0;                                                         // 申请失败返回0

    /*搬运原来的数据*/
    for (int i = 0; i < heap->size; ++i) {
        newData[i] = heap->data[i];
    }

    /*释放旧的数据域,
    更新数据域和容量
    , 返回1*/
    free(heap->data);
    heap->data = newData;
    heap->capacity = newCapacity;
    return 1;
}

// 大顶堆插入元素(
void maxHeapInsert(Heap* heap, ElementType element) {
    if (!heap) return;  // 判空保护

    /*如果堆已满, 则扩容
    扩容失败, 直接退出
    */
    if (heap->capacity == heap->size) {
        if (!extend(heap)) {
            return;
        }
    }

    /*将新的元素插入堆的末尾,
    更新堆的大小
    */
    unsigned int index = heap->size;
    heap->data[index] = element;
    heap->size++;

    /*插入元素上浮, 保持堆的特性*/
    while (index > 0 && element > heap->data[parent(index)]) {
        swap(heap->data, parent(index), index);
        index = parent(index);
    }
}

// 小顶堆插入元素
void minHeapInsert(Heap* heap, ElementType element) {
    if (!heap) return;  // 判空保护

    /*如果堆已满, 则扩容
    扩容失败, 直接退出
    */
    if (heap->capacity == heap->size) {
        if (!extend(heap)) {
            return;
        }
    }

    /*将新的元素插入堆的末尾,
    更新堆的大小
    */
    unsigned int index = heap->size;
    heap->data[index] = element;
    heap->size++;

    /*插入元素上浮, 保持堆的特性*/
    while (index > 0 && element < heap->data[parent(index)]) {
        swap(heap->data, parent(index), index);
        index = parent(index);
    }
}

// 元素出堆
ElementType maxPop(Heap* heap) {
    if (!heap) return 0;  // 判空保护

    /*记录堆顶元素,
    将末尾元素移至堆顶, 并更新堆的大小*/
    ElementType top;
    top = heap->data[0];
    heap->data[0] = heap->data[--(heap->size)];

    /*堆顶元素下沉,
    保持堆的特性*/
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

    return top;  // 返回堆顶元素
}

ElementType minPop(Heap* heap) {
    if (!heap) return 0;  // 判空保护

    /*记录堆顶元素,
    将末尾元素移至堆顶, 并更新堆的大小*/
    ElementType top;
    top = heap->data[0];
    heap->data[0] = heap->data[--(heap->size)];

    /*堆顶元素下沉,
    保持堆的特性*/
    int curr = 0;
    while (1) {
        unsigned int largest = curr;
        unsigned int lchild = 2 * curr + 1;
        unsigned int rchild = 2 * curr + 2;
        if (lchild < heap->size && heap->data[largest] > heap->data[lchild]) {
            largest = lchild;
        }
        if (rchild < heap->size && heap->data[largest] > heap->data[rchild]) {
            largest = rchild;
        }

        if (largest != curr) {
            swap(heap->data, curr, largest);
            curr = largest;
        } else {
            break;
        }
    }

    return top;  // 返回堆顶元素
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
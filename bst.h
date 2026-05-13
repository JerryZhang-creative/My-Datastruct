#ifndef LINKBINARYTREE_H
#define LINKBINARYTREE_H

typedef int ElementType;
typedef struct Node {
    struct Node* left;
    struct Node* right;
    ElementType val;
} Node;
typedef struct binaryTree {
    unsigned int size;
    Node* root;
} binaryTree;

// 创建节点并初始化
Node* newNode();
// 构建二叉树
binaryTree* newTree();
//添加值
void addElement(binaryTree* tree, ElementType val);
// 清空二叉树
void treeClear(binaryTree* tree);
// 销毁二叉树
void treeDestroy(binaryTree* tree);
// 删除元素
void nodeDelete(binaryTree* tree, ElementType val);
// 查看树的大小
unsigned int getSize(binaryTree* tree);
// 查看树的高度
unsigned int getHeight(binaryTree* tree);
// 广度优先遍历
ElementType* levelOrder(binaryTree* tree);
// 中序遍历
ElementType* midOrder(binaryTree* tree);
// 前序遍历
ElementType* prevOrder(binaryTree* tree);
// 后序遍历
ElementType* tailOrder(binaryTree* tree);
#endif
#include "linkbinarytree.h"

#include <stdlib.h>

// 创建节点并初始化
Node* newNode(ElementType val) {
    /*申请空间并初始化返回,
    申请失败返回NULL*/
    Node* node = (Node*)calloc(1, sizeof(Node));
    if (node == NULL) return NULL;
    node->val = val;
    return node;
}

// 构建二叉树
binaryTree* newTree() {
    /*申请空间并初始化返回,
    申请失败返回NULL*/
    binaryTree* tree = (binaryTree*)calloc(1, sizeof(binaryTree));
    if (tree == NULL) return NULL;
    return tree;
}

// 添加元素
static Node* _addElement(Node* root, ElementType val, unsigned int* sign) {
    /*建立辅助函数,
    寻找空位并插入元素*/
    if (root == NULL) return newNode(val);

    if (val > root->val) {
        root->right = _addElement(root->right, val, sign);
    } else if (val < root->val) {
        root->left = _addElement(root->left, val, sign);
    } else {
        *sign = 0;
    }
    return root;
}
void addElement(binaryTree* tree, ElementType val) {
    if (tree == NULL) return;  // 判空保护
    /*记录元素插入情况,
    并更新树的大小*/
    unsigned int sign = 1;
    tree->root = _addElement(tree->root, val, &sign);
    if (sign == 1) ++tree->size;
}

// 清空二叉树
static void _treeClear(Node* root) {
    /*建立辅助函数,
    清楚所有节点*/
    if (root == NULL) return;
    _treeClear(root->left);
    _treeClear(root->right);
    free(root);
}
void treeClear(binaryTree* tree) {
    if (!tree || !tree->root) return;  // 判空保护

    /*清空所有节点,
    并更新数据*/
    _treeClear(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

// 销毁二叉树
void treeDestroy(binaryTree* tree) {
    if (!tree) return;  // 判空保护

    /*释放所有结点的空间,
    释放树结构的空间*/
    if (tree->root) {
        treeClear(tree);
    }
    free(tree);
}

// 删除元素
static Node* _nodeDelete(Node* root, ElementType val, unsigned int* sign) {
    if (root == NULL) return NULL;  // 判空保护

    /*如果val小于节点值,
    去左子树寻找,
    如果val大于节点值,
    去右子树寻找,
    匹配则删除*/
    if (val > root->val) {
        root->right = _nodeDelete(root->right, val, sign);
    } else if (val < root->val) {
        root->left = _nodeDelete(root->left, val, sign);
    } else {
        *sign = 1;
        if (!root->left) {
            Node* tmp = root->right;
            free(root);
            return tmp;
        } else if (!root->right) {
            Node* tmp = root->left;
            free(root);
            return tmp;
        } else {
            Node* rightMin = root->right;
            while (rightMin && rightMin->left) {
                rightMin = rightMin->left;
            }
            root->val = rightMin->val;
            root->right = _nodeDelete(root->right, rightMin->val, sign);
        }
    }
    return root;
}
void nodeDelete(binaryTree* tree, ElementType val) {
    if (!tree || !tree->root) return;  // 判空保护

    /*记录删除情况,
    更新树的大小*/
    unsigned int sign = 0;
    tree->root = _nodeDelete(tree->root, val, &sign);
    if (sign) --tree->size;
}

// 查看树的大小
unsigned int getSize(binaryTree* tree) {
    if (tree == NULL) return 0;
    return tree->size;
}

// 查看树的高度
static unsigned int _getHight(Node* root) {
    /*建立辅助函数,
    获取树的高度*/
    if (root == NULL) return 0;
    unsigned int left = _getHight(root->left);
    unsigned int right = _getHight(root->right);
    return left > right ? left + 1 : right + 1;
}
unsigned int getHeight(binaryTree* tree) {
    if (tree == NULL || tree->root == NULL || tree->size == 0) return 0;  // 判空保护

    return _getHight(tree->root);  // 返回树的高度
}

// 广度优先遍历(层序遍历)
ElementType* levelOrder(binaryTree* tree) {
    if (tree == NULL || tree->root == NULL) return NULL;  // 判空保护

    Node** queue = (Node**)calloc(tree->size, sizeof(Node*));                   // 借助队列实现广度优先搜索
    ElementType* vals = (ElementType*)calloc(tree->size, sizeof(ElementType));  // 存储数据
    /*判空保护,
    返回NULL*/
    if (queue == NULL || vals == NULL) {
        free(queue);
        free(vals);
        return NULL;
    }

    unsigned int front = 0, tail = 0;  // 定义队首队尾指针
    queue[tail++] = tree->root;        // 将根节点压入队列中

    /*如果队列不为空,
    将队首节点出队,
    并将其左右节点入队*/
    while (front < tail) {
        Node* curr = queue[front];
        vals[front] = curr->val;

        if (curr->left != NULL) {
            queue[tail++] = curr->left;
        }
        if (curr->right != NULL) {
            queue[tail++] = curr->right;
        }
        front++;
    }

    free(queue);  // 释放辅助队列的空间
    return vals;  // 返回结果
}

// 中序遍历
static ElementType* _midOrder(Node* root, ElementType* arr, unsigned int* index) {  // 建立辅助函数
    if (root == NULL) return NULL;                                                  // 判空保护
    _midOrder(root->left, arr, index);                                              // 访问左子树
    arr[(*index)++] = root->val;                                                    // 存入数据
    _midOrder(root->right, arr, index);                                             // 访问右子树
    return arr;                                                                     // 返回结果
}
ElementType* midOrder(binaryTree* tree) {
    if (tree == NULL || tree->root == NULL || tree->size == 0) return NULL;  // 判空保护
    /*申请空间用于存储数据,
    判空保护*/
    ElementType* arr = (ElementType*)calloc(tree->size, sizeof(ElementType));
    if (!arr) return NULL;

    unsigned int index = 0;                     // 记录当前最小索引空位
    return _midOrder(tree->root, arr, &index);  // 返回数据
}

// 前序遍历
static ElementType* _prevOrder(Node* root, ElementType* arr, Node** stack, unsigned int* pos, unsigned int* index) {
    stack[(*pos)++] = root;  // 将根节点压入栈中
    /*如果栈不为空,
    将栈顶元素出栈,
    并将其左右孩子压入栈中*/
    while (*pos > 0) {
        Node* curr = stack[--(*pos)];
        arr[(*index)++] = curr->val;
        if (curr->right) {
            stack[(*pos)++] = curr->right;
        }
        if (curr->left) {
            stack[(*pos)++] = curr->left;
        }
    }
    return arr;  // 返回结果
}
ElementType* prevOrder(binaryTree* tree) {
    if (tree == NULL || tree->root == NULL || tree->size == 0) return NULL;  // 判空保护
    /*申请空间,
    并进行判空保护*/
    ElementType* arr = (ElementType*)calloc(tree->size, sizeof(ElementType));
    Node** stack = (Node**)calloc(tree->size, sizeof(Node*));
    if (!arr || !stack) {
        free(arr);
        free(stack);
        return NULL;
    }
    unsigned int index = 0;  // 记录最小索引空位
    unsigned int pos = 0;    // 记录栈顶指针
    ElementType* res = _prevOrder(tree->root, arr, stack, &pos, &index);
    free(stack);  // 释放辅助栈的空间
    return res;   // 返回数据
}

// 后序遍历
static ElementType* _tailOrder(Node* root, unsigned int size) {
    /*申请空间,
    并进行判空保护*/
    ElementType* arr = (ElementType*)calloc(size, sizeof(ElementType));
    Node** stack = (Node**)calloc(size, sizeof(Node*));
    if (!arr || !stack) {
        free(arr);
        free(stack);
        return NULL;
    }
    unsigned int top = 0, last = size - 1;
    stack[top++] = root;  // 根节点入栈
    /*栈不为空时,
    栈顶元素出栈,
    左右孩子入栈*/
    while (top) {
        Node* tmp = stack[--top];
        if (tmp->left) {
            stack[top++] = tmp->left;
        }
        if (tmp->right) {
            stack[top++] = tmp->right;
        }
        arr[last--] = tmp->val;
    }

    free(stack);  // 释放辅助栈空间
    return arr;   // 返回结果
}
ElementType* tailOrder(binaryTree* tree) {
    if (tree == NULL || tree->root == NULL || tree->size == 0) return NULL;  // 判空保护
    return _tailOrder(tree->root, tree->size);                               // 返回数据
}
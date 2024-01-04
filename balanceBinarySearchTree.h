#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_
#include "DoubleLinkListQueue.h"
#include "common.h"


//#define ELEMENTTYPE int


typedef struct AVLTreeNode
{
    ELEMENTTYPE data;
    /* 节点维护一个高度属性 */
    int height;
    struct AVLTreeNode *left;     //左子树
    struct AVLTreeNode *right;    //右子树
  
    #if 1
    /* 父节点 */
    struct AVLTreeNode *parent;
    #endif
}AVLTreeNode;

typedef struct BalanceBinarySearchTree
{
    /* 根节点 */
    AVLTreeNode * root;
    /* 树的节点个数 */
    int size;

    /* 回调函数比较器 放到结构体中 */
    int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

    /* 回调函数包装器，实现自定义打印函数接口 */
    int (*printFunc)(ELEMENTTYPE val1);
}BalanceBinarySearchTree;

/* 二叉搜索树的初始化 */
int balanceBinarySearchTreeInit(BalanceBinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2),  int (printFunc)(ELEMENTTYPE val1));

/* 二叉搜索树的插入 */
int balanceBinarySearchTreeInsert(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定元素 */
int balanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int balanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的中序遍历 */
int balanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的后序遍历 */
int balanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree *pBstree);

/* 二叉搜索树的层序遍历 */
int balanceBinarySearchTreeLevelOrderTravel(BalanceBinarySearchTree *pBstree);

/* 获取二叉搜索树的节点个数 */
int balanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree *pBstree, int *pSize);

/* 获取二叉搜索树的高度 */
/* 层序遍历的思路 */
int balanceBinarySearchTreeGetHeight(BalanceBinarySearchTree *pBstree, int *pHeight);

/* 二叉搜索树的删除 */
int balanceBinarySearchTreeDelete(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的销毁 */
int balanceBinarySearchTreeDestory(BalanceBinarySearchTree *pBstree);
#endif
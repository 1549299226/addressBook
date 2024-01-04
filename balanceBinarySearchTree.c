#include <stdlib.h>
#include <string.h>
#include "balanceBinarySearchTree.h"
#include "DoubleLinkListQueue.h"
//#include "common.h"


/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

#define true  1
#define false 0

/* 静态函数的前置声明 */
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);

/* 创建节点 */
static AVLTreeNode * createAVLTreeNewNode(ELEMENTTYPE val, AVLTreeNode * parent);

/* 根据指定的值获取二叉搜索树的节点位置 */
static AVLTreeNode * baseAppointValGetAVLTreeNode(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 判断二叉搜索树度为2 */
static int balanceBinarySearchTreeNodeHasTwoChildrens(AVLTreeNode *node);
/* 判断二叉搜索树度为1 */
static int balanceBinarySearchTreeNodeHasOneChildren(AVLTreeNode *node);
/* 判断二叉搜索树度为0 */
static int balanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node);

/* 前序遍历 */
static int preOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 中序遍历 */
static int inOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 后序遍历 */
static int postOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 获取当前节点的前驱节点 */
static AVLTreeNode * bstreeNodePreDecessor(AVLTreeNode *node);

/* 获取当前节点的后继节点 */
static AVLTreeNode * bstreeNodeSuccessor(AVLTreeNode *node);

/* 删除树的节点 */
static int balanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 添加节点之后要做的事情 */
static int insertNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 计算节点的平衡因子 */
static int AVLTreeNodeBalanceFactor(AVLTreeNode * node);

/* 判断节点是否平衡 */
static int AVLTreeNodeIsBalanced(AVLTreeNode * node);

/* 更新节点高度 */
static int AVLTreeNodeUpdataHeight(AVLTreeNode * node);

/* AVL树节点调整平衡 */
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 获取AVL节点较高的子节点 */
static AVLTreeNode * AVLTreeNodeGetChildTaller(AVLTreeNode *node);

/* 当前节点是父节点的左子树 */
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode * node);

/* 当前节点是父节点的右子树 */
static int AVLTreeCurrentNodeIsRight(AVLTreeNode * node);

/* 左旋 */
static int AVLTreeCurrentNodeRotaoteLeft(BalanceBinarySearchTree *pBstree, AVLTreeNode *node);

/* 右旋 */
static int AVLTreeCurrentNodeRotaoteRight(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand);

/* 旋转 */
static int AVLTreeCurrentNodeRotaote(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand, AVLTreeNode *parent, AVLTreeNode *child);

/* 二叉搜索树的初始化 */
int balanceBinarySearchTreeInit(BalanceBinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (printFunc)(ELEMENTTYPE val1))
{
    int ret = 0;
    BalanceBinarySearchTree * bstree = (BalanceBinarySearchTree *)malloc(sizeof(BalanceBinarySearchTree) * 1);
    if(bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(bstree, 0, sizeof(BalanceBinarySearchTree) * 1);
    /* 初始化树 */
    {
        bstree->root = NULL;
        bstree->size = 0;
        /* 回调函数在这边赋值 */
        bstree->compareFunc = compareFunc;

        /* 回调函数包装器 */
        bstree->printFunc = printFunc;
    }

    #if 0
    /* 分配根节点 */
    bstree->root = (AVLTreeNode*)malloc(sizeof(AVLTreeNode) * 1);
    if (bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(bstree->root, 0, sizeof(AVLTreeNode) * 1);
    /* 初始化根节点 */
    {
        bstree->root->data = 0;
        bstree->root->left = NULL;
        bstree->root->parent = NULL;
        bstree->root->right = NULL;
    }
    #else
    bstree->root = createAVLTreeNewNode(0, NULL);
    if(bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
    #endif

    *pBstree = bstree;

    return ret;
}
#if 0
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{
    #if 0
    if (val1 < val2)
    {
        return -1;
    }
    else if (val1 > val2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    #else
    return val1 - val2;
    #endif
}
#endif


/* 判断二叉搜索树度为2 */
static int balanceBinarySearchTreeNodeHasTwoChildrens(AVLTreeNode *node)
{
    return (node->left != NULL) && (node->right != NULL);
}

/* 判断二叉搜索树度为1 */
static int balanceBinarySearchTreeNodeHasOneChildren(AVLTreeNode *node)
{
    return ((node->left == NULL) && (node->right != NULL) || (node->left != NULL) && (node->right == NULL));
}

/* 判断二叉搜索树度为0 */
static int balanceBinarySearchTreeNodeIsLeaf(AVLTreeNode *node)
{
    return (node->left == NULL) && (node->right == NULL);
}

/* 获取当前节点的前驱节点 */
/* 中序遍历到的前一个节点 */
static AVLTreeNode * bstreeNodePreDecessor(AVLTreeNode *node)
{
    
    if (node->left != NULL)
    {
        /* 前驱节点是在左子树的右子树的右子树 */
        AVLTreeNode *travelNode = node->left;
        while (travelNode->right != NULL)
        {
            travelNode = travelNode->right;
        }
        return travelNode;
    }

    /* 程序到这个地方说明一定没有左子树，那就往父节点找 */
    while (node->parent != NULL && node == node->parent->left)
    {
        node = node->parent;
    }
    /* node->parent == NULL*/
    /* node == node->parent->right */
    return node->parent;
    
}

/* 获取当前节点的后继节点 */
static AVLTreeNode * bstreeNodeSuccessor(AVLTreeNode *node)
{
    if (node->right != NULL)
    {
        AVLTreeNode *travelNode = node->right;
        while (travelNode->left != NULL)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }
    /* 程序执行到这个地方，说明一定没有右子树，向父节点寻找 */
    while (node->parent != NULL && node == node->parent->right)
    {
        node = node->parent;
    }

    return node->parent;

}
/* 创建节点 */
static AVLTreeNode * createAVLTreeNewNode(ELEMENTTYPE val, AVLTreeNode * parent)
{
    AVLTreeNode * newAVLNode = (AVLTreeNode*)malloc(sizeof(AVLTreeNode) * 1);
    if (newAVLNode == NULL)
    {
        return NULL;
    }
    memset(newAVLNode, 0, sizeof(AVLTreeNode) * 1);
    {
        newAVLNode->data = 0;
        newAVLNode->left = NULL;
        newAVLNode->parent = NULL;
        newAVLNode->right = NULL;
    }
    
    /* 新节点赋值 */
    newAVLNode->data = val;

    /* 给父节点赋值 */
    newAVLNode->parent = parent;

    return newAVLNode;
}

/* 获取AVL节点较高的字节点 */
static AVLTreeNode * AVLTreeNodeGetChildTaller(AVLTreeNode *node)
{
    /* 左子树的高度 */
    int leftHight = node->left == NULL ? 0 : node->left->height;
    /* 右子树的高度 */
    int rightHight = node->right == NULL ? 0 : node->right->height;

    if (leftHight > rightHight)
    {
        return node->left;
    }
    else if (leftHight < rightHight)
    {
        return node->right;
    }
    else
    {
        /* 左子树高度等于右子树高度 */
        if (AVLTreeCurrentNodeIsLeft(node))
        {
            return node->left;
        }
        else if (AVLTreeCurrentNodeIsRight(node))
        {
            return node->right;
        }
    }


}

/* 当前节点是父节点的左子树 */
static int AVLTreeCurrentNodeIsLeft(AVLTreeNode * node)
{
    return (node->parent != NULL) && (node == node->parent->left);
}

/* 当前节点是父节点的右子树 */
static int AVLTreeCurrentNodeIsRight(AVLTreeNode * node)
{
    return (node->parent != NULL) && (node == node->parent->right);
}


/* 旋转 */
static int AVLTreeCurrentNodeRotaote(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand, AVLTreeNode *parent, AVLTreeNode *child)
{
    /* p成为新的根节点 */
    /* 新根节点的父节点为不平衡节点的父节点 */
    parent->parent = grand->parent;      // 3
    
    /* 判断不平衡节点在其父节点的左右子树的位置 */
    if (AVLTreeCurrentNodeIsLeft(grand))
    {
        grand->parent->left = parent;    // 4
    }
    else if (AVLTreeCurrentNodeIsRight(grand))
    {
        grand->parent->right = parent;   // 4
    }
    else
    {
        /* 如果不平衡节点为树的总根节点 */
        /* 提拔p成为新的树总根节点 */
        pBstree->root = parent;          // 4
    }
    /* 原不平衡节点的父节点更新为新提拔的根节点 */
    grand->parent = parent;
    

    if (child != NULL)
    {
        /* 更新原孩子的父节点为原不平衡节点 */
        child->parent = grand;
    }

    /* 更新高度 */
    /* 先更新低的节点 */
    AVLTreeNodeUpdataHeight(grand);
    AVLTreeNodeUpdataHeight(parent);

}


/* 左旋 */
static int AVLTreeCurrentNodeRotaoteLeft(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand)
{
    int ret = 0;

    /* 左旋为提拔右节点为新的根节点，让左边的不平衡节点下去 */
    /* 所以不平衡节点的右边为新的根节点 */
    AVLTreeNode * parent = grand->right;
    AVLTreeNode * child = parent->left;

    /* 开始左旋 */
    grand->right = child;
    parent->left = grand;

    AVLTreeCurrentNodeRotaote(pBstree, grand, parent, child);

    // /* parent成为新的根节点 */
    // parent->parent = node->parent;

    // /* 判断原不平衡节点在其父节点的左边还是右边 */
    // if (AVLTreeCurrentNodeIsLeft(node))
    // {
    //     node->parent->left = parent;
    // }
    // else if(AVLTreeCurrentNodeIsRight(node))
    // {
    //     node->parent->right = parent;
    // }
    // else
    // {
    //     /* 原本不平衡的节点是树的总根节点 */
    //     pBstree->root = parent;
    // }
    // /* 更新原不平衡节点的父节点 */
    // node->parent = parent;

    // if (child)
    // {
    //     child->parent = node;
    // }

    // /* 更新高度 */
    // AVLTreeNodeUpdataHeight(node);
    // AVLTreeNodeUpdataHeight(parent);

    return ret;
}

/* 右旋： 提拔左节点为新的根，让右边不平衡节点下去，从而达成平衡 */
static int AVLTreeCurrentNodeRotaoteRight(BalanceBinarySearchTree *pBstree, AVLTreeNode *grand)
{
    int ret = 0;
    /* 右旋不平衡节点为grand */
    /* 要提拔左节点为新的根节点，所以grand的左子树为新的根 */
    /* 新的根的右子节点为孩子 */
    AVLTreeNode *parent = grand->left;
    AVLTreeNode *child = parent->right;
    
    /* 开始右旋 */
    /* 不平衡节点的左边接新根节点的右子树 */
    grand->left = child;                 // 1
    /* 新根节点的右子树接不平衡的节点 */
    parent->right = grand;               // 2

    AVLTreeCurrentNodeRotaote(pBstree, grand, parent, child);

    // /* p成为新的根节点 */
    // /* 新根节点的父节点为不平衡节点的父节点 */
    // parent->parent = grand->parent;      // 3
    
    // /* 判断不平衡节点在其父节点的左右子树的位置 */
    // if (AVLTreeCurrentNodeIsLeft(grand))
    // {
    //     grand->parent->left = parent;    // 4
    // }
    // else if (AVLTreeCurrentNodeIsRight(grand))
    // {
    //     grand->parent->right = parent;   // 4
    // }
    // else
    // {
    //     /* 如果不平衡节点为树的总根节点 */
    //     /* 提拔p成为新的树总根节点 */
    //     pBstree->root = parent;          // 4
    // }
    // /* 原不平衡节点的父节点更新为新提拔的根节点 */
    // grand->parent = parent;
    

    // if (child != NULL)
    // {
    //     /* 更新原孩子的父节点为原不平衡节点 */
    //     child->parent = grand;
    // }

    // /* 更新高度 */
    // /* 先更新低的节点 */
    // AVLTreeNodeUpdataHeight(grand);
    // AVLTreeNodeUpdataHeight(parent);

    return ret;
    
}

/* AVL树节点调整平衡 */
/* node一定是最低的不平衡节点 */
static int AVLTreeNodeAdjustBalance(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    /* LL LR RL RR */
    AVLTreeNode *parent = AVLTreeNodeGetChildTaller(node);
    AVLTreeNode *child = AVLTreeNodeGetChildTaller(parent);
    /* L*/
    if (AVLTreeCurrentNodeIsLeft(parent))
    {
        if (AVLTreeCurrentNodeIsLeft(child))
        {
            /* LL - 右旋 */
            AVLTreeCurrentNodeRotaoteRight(pBstree, node);
        }
        else if (AVLTreeCurrentNodeIsRight(child))
        {
            /* LR */
            AVLTreeCurrentNodeRotaoteLeft(pBstree, parent);
            AVLTreeCurrentNodeRotaoteRight(pBstree, node);
        }
    }
    else
    {
        /* R */
        if (AVLTreeCurrentNodeIsLeft(child))
        {
            /* RL */
            AVLTreeCurrentNodeRotaoteRight(pBstree, parent);
            AVLTreeCurrentNodeRotaoteLeft(pBstree, node);
        }
        else if (AVLTreeCurrentNodeIsRight(child))
        {
            /* RR */
            AVLTreeCurrentNodeRotaoteLeft(pBstree, node);
        }
    }
}

/* 添加节点之后的操作 */
/* 新添加的节点一定是叶子节点 */
static int insertNodeAfter(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    /* todo... */
    while ((node = node->parent) != NULL)
    {
        /* 程序执行到这里面的时候，一定有不止一个节点 */
        if (AVLTreeNodeIsBalanced(node))
        {
            /* 如果节点是平衡的更新高度 */
            AVLTreeNodeUpdataHeight(node);
        }
        else
        {
            /* node是最低的不平衡节点 */
            /* 调整平衡 */
            AVLTreeNodeAdjustBalance(pBstree, node);
            /* 调整完最低的不平衡节点，上面的不平衡节点就默认平衡 */
            break;
        }
    }
    /* 更新节点高度 */

    /* 调整平衡 */ 
    return ret;
}

static int tmpMax(int val1, int val2)
{
    return val1 - val2 >= 0 ? val1 : val2;
}

/* 更新节点高度 */
static int AVLTreeNodeUpdataHeight(AVLTreeNode * node)
{
    #if 1
    /* 左子树的高度 */
    int leftHight = node->left == NULL ? 0 : node->left->height;

    /* 右子树的高度 */
    int rightHight = node->right == NULL ? 0 : node->right->height;
    
    return 1 + tmpMax(leftHight, rightHight);
    #endif
    // /* 左子树 - 右子树 */
    // AVLTreeNodeBalanceFactor(node) >= 0
}

/* 二叉搜索树的插入 */
int balanceBinarySearchTreeInsert(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    /* 判断树是否为空 */
    if (pBstree->size == 0)
    {
        /* 更新树节点 */
        (pBstree->size)++;

        pBstree->root->data = val;

        insertNodeAfter(pBstree, pBstree->root);
        return ret;
    }

    /* 定义遍历节点，指向根节点 */
    AVLTreeNode * travelNode = pBstree->root;

    /* 定义父节点，以便插入节点可以记录要插入的父节点 */
    AVLTreeNode * parentNode = pBstree->root;

    /* 确定符号:到底放在左边还是右边 */
    int cmp = 0;
    while (travelNode != NULL)  
    {
        /* 标记父节点 */
        parentNode = travelNode;
        cmp = pBstree->compareFunc(val, travelNode->data);
        /* 插入元素与遍历节点比较，小于放左边，大于放右边 */
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 插入元素 = 遍历节点, 直接返回*/
            return ret;
        }
    }
    
    #if 0
    /* 分配新节点 */
    AVLTreeNode * newAVLNode = (AVLTreeNode*)malloc(sizeof(AVLTreeNode) * 1);
    if (newAVLNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newAVLNode, 0, sizeof(AVLTreeNode) * 1);
    {
        newAVLNode->data = 0;
        newAVLNode->left = NULL;
        newAVLNode->parent = NULL;
        newAVLNode->right = NULL;
    }
    
    /* 新节点赋值 */
    newAVLNode->data = val;
    #else
    AVLTreeNode * newAVLNode = createAVLTreeNewNode(val, parentNode);
    #endif

    /* 挂在左子树 */
    if (cmp < 0)
    {
        parentNode->left = newAVLNode;
    }
    else
    {
        /* 挂在右子树 */
        parentNode->right = newAVLNode;
    }

    /* 添加之后的调整 */
    insertNodeAfter(pBstree, newAVLNode);

    // /* 给新节点的父节点赋值 */
    // newAVLNode->parent = parentNode;

    /* 新节点的长度++ */
    (pBstree->size)++;

    return ret;
}

/* 根据指定的值获取二叉搜索树的节点位置 */
static AVLTreeNode * baseAppointValGetAVLTreeNode(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    AVLTreeNode * travelNode = pBstree->root;

    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 比较大小 */
        cmp = pBstree->compareFunc(val, travelNode->data);
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 找到了 */
            return travelNode;
        }
    }
    return NULL;
}

/* 二叉搜索树是否包含指定元素 */
int balanceBinarySearchTreeIsContainAppointVal(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    return baseAppointValGetAVLTreeNode(pBstree, val) == NULL ? 0 : 1;
}

/* 前序遍历 */
/* 根节点 左子树 右子树 */
static int preOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 根节点 */
    pBstree->printFunc(node->data);
    /* 左子树 */
    preOrderTravel(pBstree, node->left);
    /* 右子树 */
    preOrderTravel(pBstree, node->right);
}

/* 二叉搜索树的前序遍历 */
int balanceBinarySearchTreePreOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    preOrderTravel(pBstree, pBstree->root);    
    return ret;
}

/* 特性：中序遍历 = 升序 */
/* 左子树 根节点 右子树 */
static int inOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    inOrderTravel(pBstree, node->left);
    /* 根节点 */
    pBstree->printFunc(node->data);
    /* 右子树 */
    inOrderTravel(pBstree, node->right);
    
}

/* 二叉搜索树的中序遍历 */
int balanceBinarySearchTreeInOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    inOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 后序遍历 */
/* 左子树 右子树 根节点 */
static int postOrderTravel(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    postOrderTravel(pBstree, node->left);
    /* 右子树 */
    postOrderTravel(pBstree, node->right);
    /* 根节点 */
    pBstree->printFunc(node->data);
}

/* 二叉搜索树的后序遍历 */
int balanceBinarySearchTreePostOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    postOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 二叉搜索树的层序遍历 */
int balanceBinarySearchTreeLevelOrderTravel(BalanceBinarySearchTree *pBstree)
{
    int ret = 0;
    /* 创建队列 */
    DoubleLinkListQueue *pQueue = NULL;
    /* 初始化队列 */
    doubleLinkListQueueInit(&pQueue);
    
    /* 根节点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);

    /* 创建一个节点 */
    AVLTreeNode *nodeVal = NULL;

    /* 判断队列是否为空 */
    while(!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&nodeVal);
        #if 0
        printf("data = %d\n", nodeVal->data);
        #else
        pBstree->printFunc(nodeVal->data);
        #endif
        doubleLinkListQueuePop(pQueue);

        /* 将左子树入队 */
        if (nodeVal->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->left);
        }

        /* 将右子树入队 */
        if (nodeVal->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->right);
        }
    }
    
    /* 队列释放 */
    doubleLinkListQueueDestory(pQueue);
    return ret;
}

/* 获取二叉搜索树的节点个数 */
int balanceBinarySearchTreeGetNodeSize(BalanceBinarySearchTree *pBstree, int *pSize)
{
    if (pBstree == NULL)
    {
        return 0;
    }

    if(pSize)
    {
        *pSize = pBstree->size;
    }

    return pBstree->size;
}

/* 获取二叉搜索树的高度 */
int balanceBinarySearchTreeGetHeight(BalanceBinarySearchTree *pBstree, int *pHeight)
{

    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
#if 0
    if (pBstree->size == 0)
    {
        return 0;
    }
    *pHeight = pBstree->root->height;
    return pBstree->root->height;
#endif
    if (pBstree->size == 0)
    {
        return 0;
    }
    
    int ret = 0;
    /* 创建队列 */
    DoubleLinkListQueue * pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 根节点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);
    
    /* 树的高度(根节点入队高度) */
    int height = 0;
    /* 树每一层的节点数 */
    int levelSize = 1;

    /* 创建新节点 */
    AVLTreeNode * travelNode = NULL;
    
    
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);

        doubleLinkListQueuePop(pQueue);

        levelSize--;

        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }

        if (travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }
        
        /* 树的当前层节点遍历结束 */
        if (levelSize == 0)
        {
            height++;
            doubleLinkListQueueGetSize(pQueue, &levelSize);
        }
    }

    *pHeight = height;

    doubleLinkListQueueDestory(pQueue);

    return ret;
    
}

/* 删除树的节点 */
static int balanceBinarySearchTreeDeleteNode(BalanceBinarySearchTree *pBstree, AVLTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }

    /* 树的结点减一 */
    (pBstree->size)--;

    if (balanceBinarySearchTreeNodeHasTwoChildrens(node))
    {
        /* 找到前驱结点 */
        AVLTreeNode * preNode = bstreeNodePreDecessor(node);
        node->data = preNode->data;
        node = preNode;
    }

    /* 程序执行到这里. 要删除的结点要么是度为1 要么是度为0. */

    /* 假设node结点是度为1的。它的child要么是左要么是右. */
    /* 假设node结点是度为0的, */
    AVLTreeNode * child = node->left != NULL ? node->left : node->right;

    AVLTreeNode *delNode = NULL;
    if (child)
    {
        /* 度为1 */
        child->parent = node->parent;
        if (node->parent == NULL)
        {
            /* 度为1 且 它是根结点 */
            pBstree->root = child;

            delNode = node;
            #if 0
            if (node)
            {   
                free(node);
                node = NULL;
            }
            #endif
        }
        else
        {
            /* 度为1 且 它不是根结点 */
            if (node == node->parent->left)
            {
                node->parent->left = child;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = child;
            }

            delNode = node;
            #if 0
            /* 释放结点 */
            if (node)
            {
                free(node);
                node = NULL;
            }
            #endif
        }
    }
    else
    {
        /* 度为0 */
        if (node->parent == NULL)
        {
            /* 度为0 且是根结点 */
            delNode = node;
            #if 0
            if (node)
            {
                free(node);
                node = NULL;
            }
            #endif
        }
        else
        {
            if (node == node->parent->left)
            {
                node->parent->left = NULL;
            }
            else if (node == node->parent->right)
            {
                node->parent->right = NULL;
            }


            delNode = node;
            #if 0
            if (node)
            {
                free(node);
                node = NULL;
            }
            #endif
        }
       
    }

    if (delNode)
    {
        free(delNode);
        delNode = NULL;
    }
    
    return ret;
}


// /* 二叉搜索树的删除 */
// int balanceBinarySearchTreeDelete(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
// {

//     if (pBstree == NULL)
//     {
//         return NULL_PTR;
//     }
//     int ret = 0;
//     #if 0
//     AVLTreeNode * delNode = baseAppointValGetAVLTreeNode(pBstree, val);
//     balanceBinarySearchTreeDeleteNode(pBstree, delNode);
//     #else
//     balanceBinarySearchTreeDeleteNode(pBstree, baseAppointValGetAVLTreeNode(pBstree, val));
//     #endif
//     return ret;
// }

/* 二叉搜索树的删除 */
int balanceBinarySearchTreeDelete(BalanceBinarySearchTree *pBstree, ELEMENTTYPE val)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    int ret = 0;
    #if 0
    AVLTreeNode * delNode = baseAppointValGetAVLTreeNode(pBstree, val);
    return balanceBinarySearchTreeDeleteNode(pBstree, delNode);
    #else
    return balanceBinarySearchTreeDeleteNode(pBstree, baseAppointValGetAVLTreeNode(pBstree, val));
    #endif
    return ret;
}


/* 二叉搜索树的销毁 */
int balanceBinarySearchTreeDestory(BalanceBinarySearchTree *pBstree)
{
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    
    /* 创建队列 */
    DoubleLinkListQueue * pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 根节点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);
    
    AVLTreeNode * travelNode = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);

        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }

        if (travelNode->right != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }
        /* 最后释放 */
        if (travelNode)
        {
            free(travelNode);
            travelNode = NULL;
        }
    }

    /* 释放队列 */
    doubleLinkListQueueDestory(pQueue);

    /* 释放树 */
    if (pBstree)
    {
        free(pBstree);
        pBstree = NULL;
    }

    return ON_SUCCESS;

}

/* 计算节点的平衡因子 */
/* 左子树减去右子树 */
static int AVLTreeNodeBalanceFactor(AVLTreeNode * node)
{
    /* 左子树的高度 */
    int leftHight = node->left == NULL ? 0 : node->left->height;

    /* 右子树的高度 */
    int rightHight = node->right == NULL ? 0 : node->right->height;

    return leftHight - rightHight;
}

/* 判断节点是否平衡 */
static int AVLTreeNodeIsBalanced(AVLTreeNode * node)
{
    #if 0
    abs(AVLTreeNodeBalanceFactor(node)) <= 1;
    #else
    int nodefactor = abs(AVLTreeNodeBalanceFactor(node));
    if (nodefactor <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
    #endif
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubleLinkList.h"


/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 静态函数只在本源文件 .c 中使用*/
/* 静态函数前置声明 */
static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList *pList, ELEMENTTYPE val, int *pPos, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));
/* 静态函数封装节点 */
static DoubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val);
    
/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList ** pList)
{
    /* 给链表分配空间 */
    DoubleLinkList *list = (DoubleLinkList*)malloc(sizeof(DoubleLinkList) * 1);
    if(list == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(list, 0, sizeof(DoubleLinkList) * 1);
    
    /* 给头节点分配空间 */
    list->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if(list->head == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据*/
    memset(list->head, 0, sizeof(DoubleLinkNode) * 1);

    /* 虚拟头节点无意义*/
    list->head->data = 0;
    list->head->next = NULL;
    /* 虚拟头节点的prev指针置为NULL */
    list->head->prev = NULL;

    /* 初始化的时候，尾指针 = 头指针 */
    list->tail = list->head;

    /* 链表的长度为0 */
    list->len = 0;

    /* 二级指针 */
    *pList = list;

    return ON_SUCCESS;
}

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, pList->len, val);
}

/* 静态函数 */
static DoubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val)
{
    /* 封装节点 */
    DoubleLinkNode * newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if(newNode == NULL)
    {
        return NULL;
    }
    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;
    newNode->prev = NULL;

    /* 值赋给新节点 */
    newNode->data = val;

    return newNode;
}

/* 链表指定位置插入 */
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList, int pos, ELEMENTTYPE val)
{
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
#if 1
    /* 新建新节点封装成函数 */
    DoubleLinkNode * newNode = createDoubleLinkNode(val);
    if(newNode == NULL)
    {
        return NULL_PTR;
    }
#else
    /* 封装节点 */
    DoubleLinkNode * newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if(newNode == NULL)
    {
        return MALLOC_ERROR;
    }

    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;


    /* 值赋给新节点 */
    newNode->data = val;
#endif
#if 1
    /* 从虚拟头节点开始遍历 */
    DoubleLinkNode * travelNode = pList->head;
#else
    /* 从第一个节点开始遍历 */ 
    DoubleLinkNode * travelNode = pList->head->next;
#endif
    /* 这种情况下需要更改尾指针 */
    int flag = 0;
    if(pos == pList->len)
    {
        /* 修改节点指向 */
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while(pos)
        {
            travelNode = travelNode->next;
            pos--;
        }
        travelNode->next->prev = newNode;    // 3  空链表 / 尾插
    }

    /* 改变节点方向 */
    newNode->next = travelNode->next;    // 1
    newNode->prev = travelNode;          // 2
    travelNode->next = newNode;          // 4
    if(flag)
    {
        /* 尾指针更新位置 */
        pList->tail = newNode;
    }

    (pList)->len++;

    return ON_SUCCESS;
}


/* 链表头删 */
int DoubleLinkListHeadDel(DoubleLinkList *pList)
{
    return DoubleLinkListDelAppointPos(pList, 1);
}

/* 链表尾删 */
int DoubleLinkListTailDel(DoubleLinkList *pList)
{
    return DoubleLinkListDelAppointPos(pList, pList->len);
}

/* 链表指定位置删除 */
int DoubleLinkListDelAppointPos(DoubleLinkList *pList, int pos)
{
    int ret = 0;

    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
#if 1
    DoubleLinkNode * travelNode = pList->head;
#else
    DoubleLinkNode * travelNode = pList->head->next;
#endif

    int flag = 0;
    DoubleLinkNode * needDelNode = NULL;
    /* 需要修改尾指针 */
    if(pos == pList->len)
    {
        /* 需要修改尾指针 */
        flag = 1;

        /* 备份尾指针 */
        DoubleLinkNode * tmpNode = pList->tail;
        /* 移动尾指针 */
        pList->tail = pList->tail->prev;
        needDelNode = tmpNode;
    }
    else
    {
        while(--pos)
        {
            /* 向后移动位置 */
            travelNode = travelNode->next;
            // pos--;
        }
        /* 跳出循环找到的是哪一个节点？ */
        needDelNode = travelNode->next;
        travelNode->next = needDelNode->next;
        needDelNode->next->prev = travelNode;
    }

    if(flag)
    {
        /* 调整尾指针 */
        pList->tail = travelNode ;
    }

    /* 释放内存 */
    if(needDelNode != NULL)
    {
        free(needDelNode);
        needDelNode = NULL;
    }

    /* 链表的长度减一 */
    (pList->len)--;
    return ret;
}

/* 静态函数  */
/* 根据指定的元素得到在链表中所在的位置 */
static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList *pList, ELEMENTTYPE val, int *pPos, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE) )
{
    /* 静态函数只给本源文件的函数用，不需要判断合法性 */
    int ret = 0;
#if 0
    int pos = 0;
    DoubleLinkList *travelNode = pList->head;
#else
    int pos = 1;
    DoubleLinkNode *travelNode = pList->head->next;
#endif
    int cmp = 0;
    
    while(travelNode != NULL)
    {
        #if 0
        if(travelNode->data == val)
        {
            /* 解引用 */
            *pPos = pos;
            return pos;
        }
        #else
        cmp = compareFunc(val , travelNode->data);
        if(cmp == 0)
        {
            *pPos = pos;
            return pos;
        }
        #endif
        travelNode = travelNode->next;
        pos++;
    }
    /* 解引用 */
    *pPos = NOT_FIND;
    return NOT_FIND;
}

/* 链表删除指定元素 */
int DoubleLinkListDelAppointData(DoubleLinkList *pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    int ret = 0;

    /* 元素在链表中的位置*/
    int pos = 0;

    /* 链表的长度 */
    int size = 0;
    while(DoubleLinkListGetLength(pList, &size) && pos != NOT_FIND)
    {
        /* 根据指定的元素的到在链表中所在的位置 */
        // DoubleLinkListAccordAppointValGetPos(pList, DoubleLinkListAccordAppointValGetPos(pList, val, &pos));
        DoubleLinkListAccordAppointValGetPos(pList, val, &pos, compareFunc);
        DoubleLinkListDelAppointPos(pList, pos);
    }
    
    return ret;
}

/* 获取链表的长度 */
int DoubleLinkListGetLength(DoubleLinkList *pList, int *pSize)
{
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pList->len;
    }
    
    /* 返回来链表的长度 */
    return pList->len;
}

/* 链表的销毁 */
int DoubleLinkListDestory(DoubleLinkList *pList)
{
    /* 使用头删，释放链表 */
    int size = 0;
    while(DoubleLinkListGetLength(pList, &size))
    {
        DoubleLinkListHeadDel(pList);
    }

    if(pList->head != NULL)
    {
        free(pList->head);
        /* 指针置空 */
        pList->head = NULL;
        pList->tail = NULL;
    }
    return ON_SUCCESS;
}

/* 链表的遍历接口 */
int DoubleLinkListForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    // printFunc = printStruct;
    if(pList == NULL)
    {
        return NULL_PTR;
    }

#if 0
    /* travelNode 指向虚拟头节点 */
    DoubleLinkNode * travelNode = pList->head;
    while(travelNode->next != NULL)
    {
        travelNode = travelNode->next;
        printf("travelNode->data = %d\n", travelNode->data);
    }
#else
    /* 指向链表的第一个元素 */
    DoubleLinkNode * travelNode = pList->head->next;
    while(travelNode != NULL)
    {
#if 0
        printf("travelNode->data = %d\n", travelNode->data);
#else
        /* 包装器 . 钩子 . 回调函数 */
        printFunc(travelNode->data);
#endif
        travelNode = travelNode->next;
    }

#endif
    
    
    return ON_SUCCESS;
}

int DoubleReverseForeach(DoubleLinkList *pList, int (*printFunc)(ELEMENTTYPE))
{
    if(pList == NULL)
    {
        return NULL_PTR;
    }

    DoubleLinkNode * travelNode = pList->tail;
    
    while(travelNode != pList->head)
    {
        printFunc(travelNode->data);
        travelNode = travelNode->prev;
    }

    return ON_SUCCESS;
}

/* 获取头值 */
int DoubleLinkListGetHeadVal(DoubleLinkList *pList, ELEMENTTYPE *pVal)
{
    #if 0
    return DoubleLinkListGetAppointPosVal(pList, 0, pVal);
    #else
    int ret = 0;
    if(pList == NULL)
    {
        return NULL_PTR;
    }
    if(pVal)
    {
        *pVal = pList->head->next->data;
    }
    return ret;
    #endif
}

/* 获取尾值 */
int DoubleLinkListGetTailVal(DoubleLinkList *pList, ELEMENTTYPE *pVal)
{
    return DoubleLinkListGetAppointPosVal(pList, pList->len, pVal);
}

/* 获取指定位置的值*/
int DoubleLinkListGetAppointPosVal(DoubleLinkList *pList, int pos, ELEMENTTYPE *pVal)
{
    /* 指针判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    
    /* 判断非法位置 */
    if (pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
    
    DoubleLinkNode * travelNode = pList->head;

    while(pos--)
    {
        travelNode = travelNode->next;
    }
    
    *pVal = travelNode->data;

    return ON_SUCCESS;

}

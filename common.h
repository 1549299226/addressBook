#ifndef __COMMON_H_
#define __COMMON_H_



#define ELEMENTTYPE void*

/* 链表节点取别名 */
typedef struct DoubleLinkNode
{
    ELEMENTTYPE data;

    /* 指向前一个节点的指针 */
    struct DoubleLinkNode * prev;

    /* 指向下一个节点的指针 */
    struct DoubleLinkNode *next; /* 指针的类型为什么是节点 */
    
} DoubleLinkNode;

typedef struct DoubleDoubleLinkNode
{
    DoubleLinkNode node;
    
}DoubleDoubleLinkNode;

/* 链表 */
/* 虚拟头节点  1、数据域无意义 2、只使用指针域  */
typedef struct DoubleLinkList
{
    /* 链表的虚拟头节点 */
    DoubleLinkNode * head;
    DoubleLinkNode * tail;    /* 为什么尾指针不需要分配空间 */
     /* 链表长度 */
    int len;
}DoubleLinkList;

#endif

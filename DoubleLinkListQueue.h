#ifndef __DOUBLELINKLIST_QUEUE_H_
#define __DOUBLELINKLIST_QUEUE_H_

#include "common.h"

typedef DoubleLinkList DoubleLinkListQueue;

/* 队列初始化 */
int doubleLinkListQueueInit(DoubleLinkListQueue **pQueue);

/* 入队列 */
int doubleLinkListQueuePush(DoubleLinkListQueue *pQueue, ELEMENTTYPE val);

/* 队头元素 */
int doubleLinkListQueueTop(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal);

/* 队尾元素 */
int doubleLinkListQueueRear(DoubleLinkListQueue *pQueue, ELEMENTTYPE *pVal);

/* 出队列 */
int doubleLinkListQueuePop(DoubleLinkListQueue *pQueue);

/* 队列大小 */
int doubleLinkListQueueGetSize(DoubleLinkListQueue *pQueue, int *pSize);

/* 队列是否为空 */
int doubleLinkListQueueIsEmpty(DoubleLinkListQueue *pQueue);

/* 队列的销毁 */
int doubleLinkListQueueDestory(DoubleLinkListQueue *pQueue);

#endif

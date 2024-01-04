#ifndef __ADDRESSBOOK_H_
#define __ADDRESSBOOK_H_

#include "DoubleLinkListQueue.h"
#include "common.h"

typedef DoubleLinkList addressBookList;
typedef DoubleLinkNode addressBookNode;





//插入人员信息
int addressBookInsert(addressBookList *pBook, ELEMENTTYPE data);

//查看人员信息
int addressBookSelect(addressBookList *pBook, ELEMENTTYPE data);

//删除人员信息
int addressBookDelete(addressBookList *pBook, ELEMENTTYPE data);

//修改人员信息
int addressBookmodifica(addressBookList *pBook, ELEMENTTYPE data);

//排序
int addressBooksort(addressBookList *pBook, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

//顺序遍历
int addressBook (addressBookList *pBook, int (*printFunc)(ELEMENTTYPE));






#endif
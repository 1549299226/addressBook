#ifndef __ADDRESSBOOK_H_
#define __ADDRESSBOOK_H_

#include "balanceBinarySearchTree .h"
#define NAME_NUMBER 20
#define TELEPHONE_NUMBER 11
#define EMAIL_NUMBER 30
#define ADDRESS_NUMBER 100
#define OCCUPATION_NUMBER 30

typedef BalanceBinarySearchTree addressBookList;
typedef AVLTreeNode addressBookNode;

typedef struct addressBookInfo
{
    char name[NAME_NUMBER];
    char sex;
    char telephone[TELEPHONE_NUMBER];
    char email[EMAIL_NUMBER];
    char address[ADDRESS_NUMBER];
    char occupation[OCCUPATION_NUMBER];

} addressBookInfo;

//创建人员信息
addressBookInfo *createPersonInfo(char *name, char *sex,  char * telephone, char *email, char *address, char *occupation);

//插入人员信息
int addressBookInsert(addressBookList *pBook);

//查看人员信息
int addressBookSelect(addressBookList *pBook, ELEMENTTYPE data);

//删除人员信息
int addressBookDelete(addressBookList *pBook, ELEMENTTYPE data);

//修改人员信息
int addressBookmodifica(addressBookList *pBook, ELEMENTTYPE data);

//排序
int addressBooksort(addressBookList *pBook, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE));

//顺序遍历
int addressBookOrderTravel (addressBookList *pBook, int (*printFunc)(ELEMENTTYPE));






#endif
#ifndef __ADDRESSBOOK_H_
#define __ADDRESSBOOK_H_

#include "balanceBinarySearchTree .h"
#define NAME_NUMBER 20
#define SEX_NUMBER 10
#define TELEPHONE_NUMBER 11
#define EMAIL_NUMBER 30
#define ADDRESS_NUMBER 100
#define OCCUPATION_NUMBER 30

typedef BalanceBinarySearchTree addressBookList;
typedef AVLTreeNode addressBookNode;

typedef struct addressBookInfo
{
    char name[NAME_NUMBER];
    char email[EMAIL_NUMBER];
    char address[ADDRESS_NUMBER];
    char occupation[OCCUPATION_NUMBER];
    char telephone[TELEPHONE_NUMBER];
    char sex[SEX_NUMBER];

} addressBookInfo;

//初始化
int addressBookInit(addressBookList **pBook, int (*compareFunc)(void *val1, void *val2), int (*printFunc)(void *val));


//创建人员信息
addressBookInfo *createPersonInfo(addressBookInfo *data,char *name, char *sex,  char * telephone, char *email, char *address, char *occupation);

//插入人员信息
int addressBookInsert(addressBookList *pBook, addressBookInfo* data);

//查看人员信息
int addressBookSelect(addressBookList *pBook,  ELEMENTTYPE data);

//删除人员信息
int addressBookDelete(addressBookList *pBook, ELEMENTTYPE data, char *val);

//修改人员信息
int addressBookmodifica(addressBookList *pBook, ELEMENTTYPE data);

//顺序遍历
int addressBookOrderTravel (addressBookList *pBook, int (*printFunc)(ELEMENTTYPE));

//遍历保存
int addressBookInOrderTravel(addressBookList *pBook, int (*printFunc)(ELEMENTTYPE));

//遍历读取
int addressBookErgodicRead(addressBookList *pBook, void *data,int (*printFunc)(ELEMENTTYPE));


#endif
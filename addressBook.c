#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "addressBook.h"

enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

static int judgeNull(addressBookList *pBook);
static int judgeNull(addressBookList *pBook)
{
    int ret = 0;
    if (pBook == NULL)
    {
        return NULL_PTR;
    }
    return 0;
}

addressBookInfo *createPersonInfo(char *name, char *sex,  char* telephone, char *email, char *address, char *occupation)
{
    addressBookInfo* Info = (addressBookInfo*)malloc(sizeof(addressBookInfo));
    if (Info == NULL)
    {
        return NULL;
    }
    strncpy(Info->address,address,ADDRESS_NUMBER);
    strncpy(Info->email, email, EMAIL_NUMBER);
    strncpy(Info->name, name, NAME_NUMBER);
    strncpy(Info->telephone, telephone, TELEPHONE_NUMBER);
    strncpy(Info->occupation, occupation, OCCUPATION_NUMBER);
    strncpy(&Info->sex, sex, sizeof(Info->sex));
}

// 插入人员信息
int addressBookInsert(addressBookList *pBook)
{
    int ret = 0;

    /* 判空 */
    judgeNull(pBook);

    addressBookInfo* Info = createPersonInfo(Info->name, Info->telephone, &Info->sex, Info->address, Info->occupation, Info->email);

    printf("请输入姓名\n");
    scanf("%s", Info->name);
    printf("请输入电话号码\n");
    scanf("%s",  Info->telephone);
    printf("请输入性别\n");
    scanf("%s",  &Info->sex);
    printf("请输入地址\n");
    scanf("%s", Info->address);
    printf("请输入工作\n");
    scanf("%s", Info->occupation);
    printf("请输入邮箱\n");
    scanf("%s", Info->email);
    balanceBinarySearchTreeInsert(pBook,Info);

    return 0;
}

//查看人员信息
int addressBookSelect(addressBookList *pBook, ELEMENTTYPE data)
{
    int ret = 0;


    return 0;
}

//删除人员信息
int addressBookDelete(addressBookList *pBook, ELEMENTTYPE data)
{
    int ret = 0;


    return 0;
}

//修改人员信息
int addressBookmodifica(addressBookList *pBook, ELEMENTTYPE data)
{
    int ret = 0;


    return 0;
}

//排序
int addressBooksort(addressBookList *pBook, ELEMENTTYPE data, int (*compareFunc)(ELEMENTTYPE, ELEMENTTYPE))
{
    int ret = 0;


    return 0;
}

//顺序遍历
int addressBookOrderTravel (addressBookList *pBook, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;


    return 0;
}
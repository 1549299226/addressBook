#include <stdio.h>
#include "addressBook.h"
#include<stdlib.h>



enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};



// 插入人员信息
int addressBookInsert(addressBookList *pBook, ELEMENTTYPE data)
{
    int ret = 0;

    

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
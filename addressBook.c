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

enum CHOICE
{
    ONE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    QUIT

};
/* 判空 */
static int judgeNull(addressBookList *pBook);
/* 获取指定联系人的位置 */
static addressBookNode * baseAppointValGetaddressBookNode(addressBookList *pBook, ELEMENTTYPE data);


/* 判空 */
static int judgeNull(addressBookList *pBook)
{
    int ret = 0;
    if (pBook == NULL)
    {
        return NULL_PTR;
    }
    return 0;
}

/* 创建人员信息 */
addressBookInfo *createPersonInfo(addressBookInfo *data, char *name, char *sex,  char* telephone, char *email, char *address, char *occupation)
{
    data = (addressBookInfo*)malloc(sizeof(addressBookInfo));
    if (data == NULL)
    {
        return NULL;
    }
    strncpy(data->address,address,ADDRESS_NUMBER);
    strncpy(data->email, email, EMAIL_NUMBER);
    strncpy(data->name, name, NAME_NUMBER);
    strncpy(data->telephone, telephone, TELEPHONE_NUMBER);
    strncpy(data->occupation, occupation, OCCUPATION_NUMBER);
    strncpy(&data->sex, sex, sizeof(data->sex));
    
    
}

/* 插入人员信息 */
int addressBookInsert(addressBookList *pBook, addressBookInfo* data)
{
    int ret = 0;

    /* 判空 */
    judgeNull(pBook);

    createPersonInfo(data, data->name, data->telephone, &data->sex, data->address, data->occupation, data->email);

    printf("请输入姓名\n");
    scanf("%s", data->name);
    printf("请输入电话号码\n");
    scanf("%s",  data->telephone);
    printf("请输入性别\n");
    scanf("%s",  &data->sex);
    printf("请输入地址\n");
    scanf("%s", data->address);
    printf("请输入工作\n");
    scanf("%s", data->occupation);
    printf("请输入邮箱\n");
    scanf("%s", data->email);
    balanceBinarySearchTreeInsert(pBook,data);

    return 0;
}

#if 0
/* 获取指定联系人的位置 */
static int  baseAppointValGetaddressBookNode(addressBookList *pBook, addressBookNode *personnelName[ADDRESS_NUMBER], char * data)
{
    addressBookNode * travelNode = pBook->root;

    int cmp = 0;
    
    
    int count = 0;
    while (travelNode != NULL)
    {
        
        cmp = pBook->compareFunc(data, travelNode->data);
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
         /* 找到 */
            personnelName[count++] = travelNode;
        }
    }
    if (count > 0)
    {
         return count;
    }
    return 0; 
   
}
#endif
static addressBookNode * baseAppointValGetaddressBookNode(addressBookList  *pBook, ELEMENTTYPE data)
{
    addressBookNode * travelNode = pBook->root;
    int cmp = 0;
    while (travelNode != NULL)
    {
        cmp = pBook->compareFunc(data, travelNode->data);
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
            /* 找到 */
            return travelNode;
        }
    }
    return NULL;
}
/* 查看人员信息 */
int addressBookSelect(addressBookList *pBook,  ELEMENTTYPE data)
{
    int ret = 0;
    addressBookInfo *info = data; 
    printf("请输入你要查找的姓名：\n");
    scanf("%s", info->name);
    data = baseAppointValGetaddressBookNode(pBook, data);
    if (data == NULL)
    {
        printf("查无此人\n");
        return -1;
    }
    pBook->printFunc(data);
    return 0;
}

//删除人员信息
int addressBookDelete(addressBookList *pBook, ELEMENTTYPE data)
{
    int ret = 0;
    addressBookInfo *info = data; 
    printf("请输入需要删除的联系人姓名\n");
    scanf("%s", info->name);
    balanceBinarySearchTreeDelete(pBook, data);

    return 0;
}

#if 0
//修改人员信息
int addressBookmodifica(addressBookList *pBook,ELEMENTTYPE data)
{
    int ret = 0;
    addressBookInfo *info = data;
    printf("请输入要修改的人员姓名：\n");
    scanf("%s", info->name);
    
    int choice = 0;
    while (choice <= 7)
    {
        printf("请输入要修改的名称:\n");
        printf("1、姓名 2、电话 3、性别 4、地址 5、职业 6、邮箱 7、退出\n");
        scanf("%d", choice);
        switch (choice)
        {
        case ONE:
            printf("请输入要修改的名字");
            char *newName = malloc(NAME_NUMBER);
            memset(newName, 0, NAME_NUMBER);
            scanf("%s", newName);
            *info->name = *newName;
            addressBookInfo newinfo = *info;
            addressBookDelete(pBook, info);
            addressBookInsert(pBook, &newinfo); 
            break;

        case TWO:
            printf("请输入要修改的电话");
            char  *newTelephone = malloc(TELEPHONE_NUMBER);
            memset(newTelephone, 0, TELEPHONE_NUMBER);
            scanf("%s",newTelephone);
            strncpy(info->telephone, newTelephone, TELEPHONE_NUMBER);


        break;

        case :

        
        break;

        case :

        
        break;

        case :

        
        break;

        case :

        
        break;

        case :

        
        break;

        default:
            break;
        }

    }
    

    if ()
    {
        /* code */
    }
    
    
    info = baseAppointValGetaddressBookNode(pBook, data);
    
    

    return 0;
}
#endif
//顺序遍历
int addressBookOrderTravel (addressBookList *pBook, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    balanceBinarySearchTreeInOrderTravel(pBook);

    return 0;
}
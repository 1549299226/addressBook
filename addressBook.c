#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<unistd.h>
#include "addressBook.h"

enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

enum CHOICE{
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
static void * baseAppointValGetaddressBookNode(addressBookList *pBook, ELEMENTTYPE data);

//遍历写入
static int inOrderTravel(addressBookList *pBook, addressBookNode *node, int (*printFunc)(ELEMENTTYPE));

//遍历读取
static int inOrderTravelRead(addressBookList *pBook, addressBookNode *node, void *data,int (*printFunc)(ELEMENTTYPE));

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
int addressBookInit(addressBookList **pBook, int (*compareFunc)(void *val1, void *val2), int (*printFunc)(void *val))
{
    balanceBinarySearchTreeInit(pBook, compareFunc, printFunc);
}

/* 创建人员信息 */
addressBookInfo *createPersonInfo(addressBookInfo *data, char *name, char *sex,  char* telephone, char *email, char *address, char *occupation)
{
    
    if (data == NULL)
    {
        return NULL;
    }
    // data->name = (char *)malloc(NAME_NUMBER);
    // data->telephone = (char *)malloc(TELEPHONE_NUMBER);
    // data->email = (char *)malloc(EMAIL_NUMBER);
    // data->address = (char *)malloc(ADDRESS_NUMBER);
    // data->occupation = (char *)malloc(OCCUPATION_NUMBER);
    //data = (addressBookInfo*)malloc(sizeof(addressBookInfo));
    strncpy(data->address,address,ADDRESS_NUMBER - 1);
    strncpy(data->email, email, EMAIL_NUMBER - 1);
    strncpy(data->name, name, NAME_NUMBER - 1);
    strncpy(data->telephone, telephone, TELEPHONE_NUMBER - 1);
    strncpy(data->occupation, occupation, OCCUPATION_NUMBER - 1);
    strncpy(data->sex, sex, SEX_NUMBER-1);
    
    
}

/* 插入人员信息 */
int addressBookInsert(addressBookList *pBook, addressBookInfo* data)
{
    int ret = -1;

    /* 判空 */
    judgeNull(pBook);
    ret = balanceBinarySearchTreeInsert(pBook,data);
    if (ret == 0)
    {
        sleep(3);
        return 0;
    }
    
    printf("添加联系人成功\n\n");
    sleep(2);

    return ret;
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
static void * baseAppointValGetaddressBookNode(addressBookList  *pBook, ELEMENTTYPE data)
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
            return travelNode->data;
        }
    }
    return NULL;
}
/* 查看人员信息 */
int addressBookSelect(addressBookList *pBook,  ELEMENTTYPE data)
{
    int ret = 0;
    // if (data)
    // {
        
    // }
    
    if (pBook == NULL)
    {
        printf("没有联系人\n");
    }
    
    addressBookInfo *info = data; 
    printf("请输入你要查找的姓名：\n");
    scanf("%s", info->name);
    info = (addressBookInfo *)baseAppointValGetaddressBookNode(pBook, data);      
    if (info == NULL)
    {
        printf("查无此人\n");
        return 0;
    }
    pBook->printFunc(info);
    return 0;
}

//删除人员信息
int addressBookDelete(addressBookList *pBook, ELEMENTTYPE data, char* val)
{
    int ret = 0;
       if (pBook == NULL)
    {
        printf("没有这个联系人\n");
        return 0;
    }
    addressBookInfo *info = data; 
    info = (addressBookInfo *)baseAppointValGetaddressBookNode(pBook, data);     
    if (info == NULL)
    {
        printf("没有这个联系人\n");
        sleep(2);
        return 0;
    }
    
    balanceBinarySearchTreeDelete(pBook, data);
    printf("删除联系人成功\n");
    sleep(2);

    return 0;
}

#if 1
//修改人员信息
int addressBookmodifica(addressBookList *pBook,ELEMENTTYPE data)
{
    int ret = 0;
    addressBookInfo *info = data;
    printf("请输入要修改的人员姓名：\n");
    scanf("%s", info->name);
    
    info = (addressBookInfo *)baseAppointValGetaddressBookNode(pBook, data);
       if (info == NULL)
    {
        printf("查无此人\n");
        sleep(2);
        return 0;
    }
    int choice = 0;
    while (choice <= 7)
    {
        printf("请输入要修改的名称:\n");
        printf("1、姓名 2、电话 3、性别 4、地址 5、职业 6、邮箱 7、退出\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case ONE:
            printf("请输入新的的名字：\n");
            char *newName = malloc(NAME_NUMBER);
            memset(newName, 0, NAME_NUMBER);
            scanf("%s", newName);
            *info->name = *newName;
            addressBookInfo newinfo = *info;
            addressBookDelete(pBook, info, info->name);
            addressBookInsert(pBook, &newinfo); 
            break;

        case TWO:
            printf("请输入新的的电话：\n");
            char  *newTelephone = malloc(TELEPHONE_NUMBER);
            memset(newTelephone, 0, TELEPHONE_NUMBER);
            scanf("%s",newTelephone);
            strncpy(info->telephone, newTelephone, TELEPHONE_NUMBER);


        break;

        case THREE:
            printf("请输入新的的性别：\n");
            //char * newSex;
            char  *newSex = malloc(SEX_NUMBER);
            memset(newSex, 0, SEX_NUMBER);
            //memset(newSex, 0, ONE);
            scanf("%s",newSex);
            strncpy(info->sex, newSex, sizeof(info->sex));

        
        break;

        case FOUR:
            printf("请输入新的的地址：\n");
            char  *newAddress = malloc(ADDRESS_NUMBER);
            memset(newAddress, 0, sizeof(ADDRESS_NUMBER));
            scanf("%c",newAddress);
            strncpy(info->address, newAddress, sizeof(ADDRESS_NUMBER));

        
        break;

        case FIVE:
            printf("请输入新的的工作：\n");
            char  *newOccupation = malloc(OCCUPATION_NUMBER);
            memset(newOccupation, 0, OCCUPATION_NUMBER);
            scanf("%s",newOccupation);
            strncpy(info->occupation, newOccupation, OCCUPATION_NUMBER);
        
        break;

        case SIX:
            printf("请输入新的的工作：\n");
            char  *newEmail = malloc(EMAIL_NUMBER);
            memset(newEmail, 0, EMAIL_NUMBER);
            scanf("%s",newEmail);
            strncpy(info->email, newEmail, EMAIL_NUMBER);
        
        break;

        case QUIT:
            return 0;
        break;

        default:
            return 0;
            break;
        }
        

    }
    return 0;
}
#endif
//顺序遍历
int addressBookOrderTravel (addressBookList *pBook, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if (pBook == NULL)
    {
        printf("没有联系人\n");
        return 0;
    }
    
    balanceBinarySearchTreeInOrderTravel(pBook);

    return 0;
}


//遍历
static int inOrderTravel(addressBookList *pBook, addressBookNode *node, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if(node == NULL)
    {
        return ret;
    }
    /* 左子树 */
    inOrderTravel(pBook, node->left, printFunc);
    /* 根节点 */
    printFunc(node->data);
    /* 右子树 */
    inOrderTravel(pBook, node->right, printFunc);

}


int addressBookInOrderTravel(addressBookList *pBook, int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    ret = inOrderTravel(pBook, pBook->root, printFunc);
    return ret;
}


//遍历写入
static int inOrderTravelRead(addressBookList *pBook, addressBookNode *node, void *data,int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    if(node == NULL)
    {
        return ret;
    }
    addressBookInfo *info = data;
    /* 左子树 */
    ret = inOrderTravel(pBook, node->left, printFunc);
    /* 根节点 */
    printFunc(node->data);
    addressBookInsert(pBook, info);
    /* 右子树 */
    inOrderTravel(pBook, node->right, printFunc);
    return ret;

}

//遍历读取
int addressBookErgodicRead(addressBookList *pBook, void *data,int (*printFunc)(ELEMENTTYPE))
{
    int ret = 0;
    ret = inOrderTravelRead(pBook, pBook->root,  data, printFunc);
    return ret;

}


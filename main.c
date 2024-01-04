#include <stdio.h>
#include "addressBook.h"

#define 

//通讯录结构体
typedef struct addressBook
{
    char name[20];
    char sex;
    char telephone[11];
    char email[20];
    char address[30];
    char occupation[20];

}addressBook;

int compareFunc(void *arg1, void *arg2)
{
    int *a = (int *) arg1;
    int *b = (int *) arg2;
    return (*a == *b ?  0 : 1) ;
}

//自定义打印
int printStruct(void *arg)
{
    
    addressBook* info = (addressBook*)arg;
    printf("name:%s\tsex:%c\ttelephone:%s\temail:%s\taddress:%s\toccupation:%s\t", 
             info->name, info->telephone, info->email, info->address, info->occupation);
}

int main()
{



    return 0;
}
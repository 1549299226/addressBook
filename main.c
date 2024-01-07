#include <stdio.h>
#include "addressBook.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include"balanceBinarySearchTree .h"
#define BUFFER_SIZE 1024

//通讯录结构体
// typedef struct addressBook
// {
//     char name[20];
//     char sex;
//     char telephone[11];
//     char email[20];
//     char address[30];
//     char occupation[20];

// }addressBook;

enum SECLET
{
    BUILT = 1,
    SEEK,
    DELETE,
    MODIFY,
    QUIT
};

int CompareName(void *arg1, void *arg2)
{
    addressBookInfo *idx1 = (addressBookInfo *) arg1;
    addressBookInfo *idx2 = (addressBookInfo *) arg2;

    int result = 0;
    result = strcmp(idx1->name,idx2->name);

    return result;
}

//自定义打印
int printStruct(void *arg)
{
    int ret = 0;
    addressBookInfo* info = (addressBookInfo*)arg;
    printf("name:%s\tsex:%c\ttelephone:%s\temail:%s\taddress:%s\toccupation:%s\n", 
             info->name, info->sex, info->telephone, info->email, info->address, info->occupation);
    return ret;
}

int main()
{
    addressBookList *List;
    balanceBinarySearchTreeInit(&List,CompareName,printStruct);
    /* 功能选项打印 */
    {
        int fd = open("./function.txt", O_RDWR);
        if (fd == -1)
        {
            perror("open error");
        }
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));

        read(fd, buffer, sizeof(buffer) - 1);
        printf("%s\n", buffer);

        close(fd);
    }

    /* 功能选择 */   
    {
        printf("请输入选项\n");
        int choice = 0;
        scanf("%d", &choice);
        switch (choice)
        {
        case BUILT:
                    addressBookInsert(List);
            break;
        case SEEK:
            break;
        case DELETE:
            break;
        case MODIFY:
            break;
        case QUIT:
            break;
        default:
            break;
        }
    }

    /* 保存 */
    {
        

    }
    return 0;
}
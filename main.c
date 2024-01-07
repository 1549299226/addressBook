#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include "addressBook.h"
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
    VIEW_ALL,
    QUIT
};

int CompareName(void *arg1, void *arg2)
{
    addressBookInfo *idx1 = (addressBookInfo *) arg1;
    addressBookInfo *idx2 = (addressBookInfo *) arg2;
    // char * idx1 = (char *)arg1;
    // char * idx2 = (char *)arg2;
    int result = 0;
    result = strcmp(idx1->name, idx2->name);

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
    // addressBookInfo * Info;
    // addressBookInfo **buffer = malloc(sizeof (addressBookInfo) * BUFFER_SIZE);
    
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
        int choice = 0;    
        //int count = 0;    
        while ( choice <= QUIT && choice >= 0)
        {
            printf("请输入选项\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case BUILT:
                    addressBookInfo * Info;
                    createPersonInfo(Info,Info->name, &Info->sex, Info->telephone, Info->email, Info->address, Info->occupation);
                    createPersonInfo(Info, Info->name, Info->telephone, &Info->sex, Info->address, Info->occupation, Info->email);
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
                    addressBookInsert(List, Info);
                    Info++;
                // choice = DELETE;
            break;
            case SEEK:                   
                        addressBookSelect(List, Info);
                //choice = 0;
                break;
            case DELETE:
                        printf("请输入需要删除的联系人姓名\n");
                        scanf("%s", Info->name);
                        addressBookDelete(List, Info, Info->name);
                        //count--;
                        if (List->root->left == NULL &&List->root->right == NULL)
                        {
                            printf("通讯录没有人员\n");
                            return 0;
                        }
                        
                break;
            case MODIFY:
                        addressBookmodifica(List, Info);
                break;
            case VIEW_ALL:
                        addressBookOrderTravel(List, printStruct);
                break;
            default:
                choice = QUIT;
                break;
            }
        }
    }

    /* 保存 */
    {
        

    }
    return 0;
}
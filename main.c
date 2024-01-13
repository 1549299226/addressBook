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
#define BUF    128

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
    SIX,
    QUIT
};

//保存到文件
int saveFile(void *arg)
{
    int fd = open("addressBook.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open error");
        _exit(-1);
    }
    char buf[BUF];
    memset(buf, 0, sizeof(buf));
    lseek(fd, 0, SEEK_END);
    addressBookInfo *Info = (addressBookInfo *)arg;
    sprintf(buf, "%s\n", Info->name);
    write(fd, buf, strlen(buf));

    sprintf(buf, "%s\n", Info->sex);
    write(fd, buf, strlen(buf));

    sprintf(buf, "%s\n", Info->telephone);
    write(fd, buf, strlen(buf));
    
    sprintf(buf, "%s\n", Info->occupation);
    write(fd, buf, strlen(buf));

    sprintf(buf, "%s\n", Info->email);
    write(fd, buf, strlen(buf));

    sprintf(buf, "%s\n", Info->address);
    write(fd, buf, strlen(buf));
    

    return fd;
   
}

int fileRead(void * arg)
{
    if (arg == NULL)
    {
        return -1;
    }
    
    int fd = open("addressBook.txt", O_RDWR | O_CREAT, 0644);
    char buf[BUF];
    
    struct stat st;
    if (stat("example.txt", &st) == 0) 
    {
        if (st.st_size == 0)
        {
            return 0;
        }
    } 
    else
    {
        perror("stat");
    }
   

    addressBookInfo * Info = arg;
    createPersonInfo(Info, Info->name, Info->sex, Info->telephone, Info->email, Info->address, Info->occupation);
    lseek(fd, 0, SEEK_END);
    
    read(fd, buf, strlen(buf));
    if (buf[0] == '\0')
    {
        return 0;//没有内容
    }
    
    
    strncpy(Info->name, buf, sizeof(buf) - 1);

    read(fd, buf, strlen(buf));
    strncpy(Info->sex, buf, sizeof(buf) - 1);

    read(fd, buf, strlen(buf));
    strncpy(Info->telephone, buf, sizeof(buf) - 1);

    read(fd, buf, strlen(buf));
    strncpy(Info->occupation, buf, sizeof(buf) - 1);

    read(fd, buf, strlen(buf));
    strncpy(Info->email, buf, sizeof(buf) - 1);

    read(fd, buf, strlen(buf));
    strncpy(Info->address, buf, sizeof(buf) - 1);

    return fd;
}


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
    printf("name:%s\tsex:%s\ttelephone:%s\temail:%s\taddress:%s\toccupation:%s\n", 
             info->name, info->sex, info->telephone, info->email, info->address, info->occupation);
    return ret;
}

int main()
{
    addressBookList *List = NULL;
    // addressBookInfo * Info;
    // addressBookInfo **buffer = malloc(sizeof (addressBookInfo) * BUFFER_SIZE);
    
    addressBookInit (&List,CompareName,printStruct);
    addressBookInfo * Info;
    createPersonInfo(Info,Info->name, Info->sex, Info->telephone, Info->email, Info->address, Info->occupation);
    int fd1 = 0;//功能页面
    int fd2 = 0;//保存
    int fd3 = 0;//加入到树中
    //addressBookErgodicRead(List, Info, fileRead);  //将之前保存的数据拿出来
    
    /* 功能选择 */   
    {
        int choice = 0;    
        //int count = 0;    
        while ( choice <= QUIT && choice >= 0)
        {
            /* 功能选项打印 */
            {
                fd1 = open("./function.txt", O_RDWR | O_CREAT, 0644);
                if (fd1 == -1)
                {
                    perror("open error");
                    _exit(-1);
                }
                char buffer[BUFFER_SIZE];
                memset(buffer, 0, sizeof(buffer));
                read(fd1, buffer, sizeof(buffer) - 1);
                printf("%s\n", buffer);

                close(fd1);
            }
            printf("请输入选项\n");
            scanf("%d", &choice);
            if (choice < BUILT || choice > QUIT)
            {
                printf("没有该选项\n请重新选择");
                //sleep(3);
                printf("请输入选项\n");
                //choice = 0;
                scanf("%d", &choice);
            }
            
            switch (choice)
            {
            case BUILT:    //新增联系人
                    addressBookInfo * Info = (addressBookInfo*)malloc(sizeof(addressBookInfo));
                    createPersonInfo(Info,Info->name, Info->sex, Info->telephone, Info->email, Info->address, Info->occupation);
                    //createPersonInfo(Info, Info->name, Info->telephone, &Info->sex, Info->address, Info->occupation, Info->email);
                    printf("请输入姓名\n");
                    scanf("%s", Info->name);
                    
                    printf("请输入性别\n");
                    scanf("%s",  Info->sex);
                    
                    printf("请输入电话号码\n");
                    scanf("%s",  Info->telephone);
                    
                    printf("请输入邮箱\n");
                    scanf("%s", Info->email);
                    
                    printf("请输入地址\n");
                    scanf("%s", Info->address);
                    
                    printf("请输入工作\n");
                    scanf("%s", Info->occupation);
                    
                    addressBookInsert(List, Info);
                    Info++;
                    system("clear");
                // choice = DELETE;
            break;
            case SEEK:      //查找联系人     
                        addressBookSelect(List, Info);
                //choice = 0;
                break;
            case DELETE:   //删除联系人
                        printf("请输入需要删除的联系人姓名\n");
                        scanf("%s", Info->name);
                        //count--;
                        if (List->root->left == NULL &&List->root->right == NULL)
                        {
                            printf("通讯录没有人员\n");
                            system("clear");
                            break;
                        }
                        addressBookDelete(List, Info, Info->name);
                    system("clear");
                break;
            case MODIFY: //修改联系人
                        addressBookmodifica(List, Info);
                        system("clear");

                break;
            case VIEW_ALL:  //查看全部联系人
                        addressBookOrderTravel(List, printStruct);
                        //system("clear");

                break;

            case SIX: //保存
                        fd2 = addressBookInOrderTravel(List, saveFile);

                        printf("保存成功\n");
                        close(fd2);
                        sleep(2);
                        system("clear");
                          

                
                break;

            default:   //退出通讯录
                choice = QUIT;
                printf("正在退出。。。\n");
                close(2);
                system("clear");
                printf("退出成功\n");
                close(1);
                return 0;
                //break;
            }
        }
    }
    close(fd3);
    /* 保存 */
    {
        

    }
    return 0;
}
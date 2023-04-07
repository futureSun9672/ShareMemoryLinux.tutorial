#include<sys/ipc.h>
#include<sys/shm.h> //共享内存
#include<string.h>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct worker
{
        int age;
        char number[15];
        char name[20];
}worker;

int main()
{
	printf("IPC_CREAT=%#o",IPC_CREAT);
	int shmid = shmget((key_t)0x8000, 0, 0);//获取内存段
	worker*  p = NULL; //指向共享变量
        p = (worker*)shmat(shmid, 0, 0);  // 把已经存在的共享变量引入程序
        printf("写入前：%d, %s, %s\n",p->age,p->number,p->name);
        printf("进程id：%d\n",getpid());
        p->age = 50;
        strcpy(p->number,"12345678906");
        strcpy(p->name,"李力");
        printf("写入后：%d, %s, %s\n",p->age,p->number,p->name);
        return 0;
}

#include<sys/ipc.h>
#include<sys/shm.h> //共享内存
#include<string.h>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

typedef struct worker
{
	int age;
	char number[15];
	char name[20];
}worker;
 
int main()
{
	int shmid = shmget( (key_t)0x6406, sizeof(worker)*10, 0666|IPC_CREAT);
	if(shmid == -1)
	{
		printf("(key_t)0x6406 failed\n");
		return -1;	
	}
	worker*  p = NULL; //指向共享变量
	p = (worker*)shmat(shmid, 0, 0);
	// 写入前
	for(int ii=0;ii < 10;ii++)
	{
		printf("写入前：%d, %s, %s\n",(p+ii)->age,(p+ii)->number,(p+ii)->name);
	}
	printf("进程id：%d\n",getpid());
	
	//写入
	for(int ii=0;ii < 10;ii++)
        {
		(p+ii)->age = 10 + ii;
		strcpy((p+ii)->number,"13984553895");
		strcpy((p+ii)->name,"张宁智");

        }
	
	//写入后
	for(int ii=0;ii < 10;ii++)
        {
                printf("写入后：%d, %s, %s\n",(p+ii)->age,(p+ii)->number,(p+ii)->name);
        }
	
	return 0;
}

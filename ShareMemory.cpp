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
	int shmid = shmget( (key_t)0x8000, sizeof(worker), 0666|IPC_CREAT);
	if(shmid == -1)
	{
		printf("(key_t)0x8000 failed\n");
		return -1;	
	}
	worker*  p = NULL; //指向共享变量
	p = (worker*)shmat(shmid, 0, 0);
	printf("写入前：%d, %s, %s\n",p->age,p->number,p->name);
	printf("进程id：%d\n",getpid());
	p->age = 28;
	strcpy(p->number,"13984553895");
	strcpy(p->name,"张宁智");
	printf("写入后：%d, %s, %s\n",p->age,p->number,p->name);
	//sleep(30);
	//shmdt(p); //从进程移除内存
	//int age = p->age;
	//删除共享内存
	//shmctl(shmid,IPC_RMID,0);
	return 0;
}

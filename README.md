## linux共享内存笔记
### 这是一篇介绍在Linux下，使用共享内存的简单教程
## 目录

 1. 包含头文件
 2. 所用函数
 3. 简单例子
## 1.包含头文件

```cpp
<sys/ipc.h>
<sys/shm.h>
```
## 2.所用函数

 - 查看共享内存的命令： ipcs -m
 - 查看进程编号： getpid()
 (1) shm_id  = shmget(key_t key, size_t size, int shmflg) 
shm_id 共享内存id，系统区分不同共享内存
![在这里插入图片描述](https://img-blog.csdnimg.cn/ca4b3995c9be40c6b2b29d8259adf4a0.png#pic_center)

key  内存键值，共享内存的唯一标识

size 内存大小，若创建填整数，若打开写0

shmflg 文件权限，打开填0

若不存在该内存，创建共享内存id，返回id号，错误返回-1

shmflg主要和一些标志有关。
    IPC_CREAT   如果共享内存不存在，则创建一个共享内存，否则打开操作。
    IPC_EXCL     只有在共享内存不存在的时候，新的共享内存才建立，否则就产生错误。 

> 引用

    如果将IPC_CREAT和IPC_EXCL标志一起使用，shmget()将返回一个新建的共享内存的标识符；如果该共享内存已存在，或者返回-1。

     IPC_EXEL标志本身并没有太大的意义，但是和IPC_CREAT标志一起使用可以用来保证所得的对象是新建的，而不是打开已有的对象。

     对于用户的读取和写入许可指定SHM_R和SHM_W；

     (SHM_R>3)和(SHM_W>3)是一组读取和写入许可，而(SHM_R>6)和(SHM_W>6)是全局读取和写入许可。
     推荐使用0666|IPC_CREAT，来作为shmflg的值。

(2) void * shmat(int shm_id, const void *shm_addr, int shmflg)

将创建的共享内存的物理地址映射到进程空间，返回进程物理地址

例： char* p =  (char*) shmat(i shm_id, 0, 0);

shmat(shm_id, 0, 0)

shm_id :  shmget返回的标识

*shm_addr：  返回当前的地址，通常为0

shmflg 通常为0

(3)shmdt( *shmaddr)

共享内存从当前程序分离

(4)shmctl(shm_id, int command, struct shmid_ds *buf)

控制共享内存

删除：

shm_id 标识

command 填 IPC_RMID

buf 填0

## 简单例子

 - 例1.  ShareMemory.cpp
 创建共享内存,保存一个结构体，并写入
 
 
 - 例2. useShareMemory.cpp
 另一个程序使用例1创建的共享内存
 
 - 例3. ShareMemoryX.cpp
  应用开发常用的方法，定义一个结构体数组

## Linux命令
ipcs -m   查看当前共享内存
ipcrm -m 共享内存编号   删除

 
 

     





 


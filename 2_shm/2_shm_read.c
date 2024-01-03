/*共享内存：*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#if 0
int shmget(key_t key, size_t size, int shmflg);
功能：创建并打开共享内存
参数：size  ：指定开辟的共享内存大小
	  shmflg：IPC_CREAT
返回：成功返回共享内存ID，失败-1

void *shmat(int shmid, const void *shmaddr, int shmflg);
功能：映射
参数：shmaddr：为NULL，由系统选择一个合适的地址进行映射
	  shmflg ：0可读可写，SHM_RDONLY只读
返回：成功返回映射后的首地址，失败返回(void*)-1


int shmdt(const void *shmaddr);
功能：解除映射
参数：shmaddr：shmat的返回值
返回：成功0 失败-1

int shmctl(int shmid, int cmd, struct shmid_ds *buf);
#endif

#define N 32

int main(int argc, const char *argv[])
{
	//获取key值
	key_t key = ftok(".", 1);

	//创建并打开共享内存
	int shmid = shmget(key, N, IPC_CREAT|0664);
	if(shmid == -1)
	{
		perror("shmget error");
		exit(1);
	}

	//映射：将共享内存映射到当前进程内
	char *p = (char*)shmat(shmid, NULL, 0);

	//读：sleep(1);
	fputs(p, stdout);
	

	//解除映射 
	shmdt(p);

	//删除共享内存
	system("ipcs -m");
	shmctl(shmid, IPC_RMID, NULL);
	system("ipcs -m");

	
	return 0;
}

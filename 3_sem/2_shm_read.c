/*共享内存：*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>


#define N 32

int main(int argc, const char *argv[])
{
	//获取key值
	key_t key = ftok(".", 1);

	/**************** 共享内存 *********************/
	//创建并打开共享内存
	int shmid = shmget(key, N, IPC_CREAT|0664);
	if(shmid == -1)
	{
		perror("shmget error");
		exit(1);
	}
	//映射
	char *p = (char*)shmat(shmid, NULL, 0);

	/****************  信号灯 ***********************/
	//创建并打开
	int semid = semget(key, 1, IPC_CREAT|0664);
	if(semid == -1)
	{
		perror("semget error");
		exit(1);
	}
	//设置减操作(P)
	struct sembuf sembuf;
	sembuf.sem_num = 0; 					//信号量的编码
	sembuf.sem_op  = -1; 					//执行减一操作
	sembuf.sem_flg = 0; 					//阻塞

	/*****************  通信  *************************/
	while(1)
	{
		semop(semid, &sembuf, 1); 			//执行减一操作

		if(strncmp(p, "quit\n", 5) == 0)
		{
			break;
		}

		fputs(p, stdout); 					//将共享内存的数据打印到终端
	}

	/***************** 删除 ***************************/
	//解除映射 
	shmdt(p);

	//删除共享内存
	shmctl(shmid, IPC_RMID, NULL);
	system("ipcs -m");

	//删除信号灯
	semctl(semid, 0, IPC_RMID);
	system("ipcs -s");
	
	return 0;
}

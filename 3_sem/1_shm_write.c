/*共享内存：*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define N 32

union semun{
	int val;
};

int main(int argc, const char *argv[])
{
	//获取key值
	key_t key = ftok(".", 1);

	/**************** 共享内存 *********************/
	//创建并打开
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
	//设置信号量初值
	union semun semun;
	semun.val = 0;
	semctl(semid, 0, SETVAL, semun);
	//设置加操作(V)
	struct sembuf sembuf;
	sembuf.sem_num = 0; 					//信号量的编码
	sembuf.sem_op  = 1; 					//执行加一操作
	sembuf.sem_flg = 0; 					//阻塞


	/****************  通信 **************************/
	while(1)
	{
		fgets(p, N, stdin); 				//从终端获取数据写到共享内存
		semop(semid, &sembuf, 1); 			//执行加一操作

		if(strncmp(p, "quit\n", 5) == 0)
		{
			break;
		}
	}
	

	/****************  删除 **************************/
	//解除映射 
	shmdt(p);

	
	return 0;
}

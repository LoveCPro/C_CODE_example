/*信号灯：由若干个信号量组成*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#if 0
int semget(key_t key, int nsems, int semflg);
功能：创建并打开信号灯
参数：nsems ：信号灯中信号量的个数
	  semflg：IPC_CREAT|0664
返回：成功信号灯的ID，失败-1

int semctl(int semid, int semnum, int cmd);
int semctl(int semid, int semnum, int cmd, union semun);
功能：删除信号灯，设置信号灯中某一个信号量的初始值，获取信号量值
参数：semnum：信号灯中信号量的编码(从0起始)
	  cmd   ：SETVAL  IPC_STAT  IPC_SET 	 //需要第四个参数
	  		  GETVAL  IPC_RMID 				 //不需要第四个参数
	  semun ：需要自己定义
			  union semun {
					int              val;    //SETVAL
					struct semid_ds *buf;    //IPC_STAT, IPC_SET
					unsigned short  *array;  //GETALL, SETALL
					struct seminfo  *__buf;  //IPC_INFO
				};                                                                                                                         
				EFAULT(arg指向的地址无效)

EIDRM(信号量集已经删除)

EINVAL(信号量集不存在，或者semid无效)

EPERM(EUID没有cmd的权利)

ERANGE(信号量值超出范围)

int semop(int semid, struct sembuf *sops, unsigned nsops);
功能：执行PV操作，减操作/加操作
参数：nsops：同时操作信号量的个数
	  sops ：unsigned short sem_num;  //信号量的编码
    		 short          sem_op;   //正数加操作(V),负数减操作(P)
			 short          sem_flg;  //0阻塞，IPC_NOWAIT非阻塞
#endif

union semun{
	int val;
};

int main(int argc, const char *argv[])
{
	struct sembuf sembuf;
	union semun semun;
	int ret = 0;

	
	key_t key = ftok(".", 1);
	//创建并打开信号灯
	int semid = semget(key, 1, IPC_CREAT|0664);
	if(semid == -1)
	{
		perror("semget error");
		exit(1);
	}

	//设置信号灯中第一个信号量的初始值
	semun.val = 2;
    //创建一个信号量集对像
	semctl(semid, 0, SETVAL, semun);   
	
	ret = semctl(semid, 0, GETVAL); 		//获取信号量的值
	printf("ret = %d\n",ret);


	//执行减操作(P)
	sembuf.sem_num = 0;    //信号量的编码
	sembuf.sem_op  = -2;   //减操作
	sembuf.sem_flg = 0;    //阻塞
	semop(semid, &sembuf, 1);
	ret = semctl(semid, 0, GETVAL); 		//GETVAL获取信号量的值
	printf("ret = %d\n",ret);


	//执行加操作(V)
	sembuf.sem_num = 0;
	sembuf.sem_op  = 3;  //
	sembuf.sem_flg = 0;
	semop(semid, &sembuf, 1);
	ret = semctl(semid, 0, GETVAL); 		//获取信号量的值
	printf("ret = %d\n",ret);


	//删除信号灯
	system("ipcs -s");
	semctl(semid, 0, IPC_RMID);
	system("ipcs -s");
	
	return 0;
}

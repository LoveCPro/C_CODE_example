#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 	//ftok msgget
#include <sys/ipc.h> 	//ftok msgget
#include <sys/msg.h> 	//msgget

#if 0
ipcs  -q
ipcrm -q  MSGID

int msgget(key_t key, int msgflg);
功能：创建并打开指定的一个消息队列
参数：msgflg：IPC_CREAT创建并打开
返回：成功返回消息队列ID，失败-1


int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
功能：向一个指定的消息队列发送消息
参数：msgflg：0阻塞模式，IPC_NOWAIT非阻塞
	  msgp  ：发送消息的地址
	  		  struct msgbuf{
				  long mtype; 		//消息的类型,>0
				  char mtext[1]; 	//消息内容
			  };
	  msgsz  ：消息中消息内容的大小
返回：成功0 失败-1

ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
功能：从消息队列中读走一条消息存储到msgp内
参数：msgflg：0阻塞模式，IPC_NOWAIT非阻塞
	  msgp  ：发送消息的地址
	  		  struct msgbuf{
				  long mtype; 		//消息的类型,>0
				  char mtext[1]; 	//消息内容 
			  };
	  msgsz  ：消息中消息内容的大小
	  msgtyp ：=0 ：读取队列中第一条消息
	  		   >0 ：指定类型中的第一条消息被读取
			   <0 ：小于或等于|msgtyp|中最小的类型
返回：成功0 失败-1


int msgctl(int msqid, int cmd, struct msqid_ds *buf);
#endif

struct msgbuf{
	long mtype;
	int a;
	float b;
	char c;
};

#define N sizeof(struct msgbuf) - sizeof(long)

int main(int argc, const char *argv[])
{
	//获取key值
	key_t key = ftok(".", 1);  //相同的文件的键值是相同的

	//创建并打开消息队列
	int msgid = msgget(key, IPC_CREAT|0664);
	if(msgid == -1)
	{
		perror("msgget error");
		exit(1);
	}

	//接收消息
	struct msgbuf msgbuf;
	msgrcv(msgid, &msgbuf, N, -2, 0);
	printf("a = %d  b = %.2f  c = %c\n",msgbuf.a,  msgbuf.b,  msgbuf.c);
	
	//删除
	system("ipcs -q");
	msgctl(msgid, IPC_RMID, NULL); //删除消息队列
	system("ipcs -q");

	

	return 0;
}

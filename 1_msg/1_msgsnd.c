#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 	//ftok msgget
#include <sys/ipc.h> 	//ftok msgget
#include <sys/msg.h> 	//msgget

#if 0
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
	struct msgbuf msgbuf;

	//获取key值
	key_t key = ftok(".", 1);

	//创建并打开消息队列，成功返回消息队列的id
	int msgid = msgget(key, IPC_CREAT|0664);   //不存在则创建，存在的话打开，创建的权限是0664
	if(msgid == -1)
	{
		perror("msgget error");
		exit(1);
	}

	//发送消息 
	msgbuf.mtype = 1;
	msgbuf.a = 10;
	msgbuf.b = 10.23;
	msgbuf.c = 'A';
	msgsnd(msgid,  &msgbuf, N, 0);

	msgbuf.mtype = 2;
	msgbuf.a = 20;
	msgbuf.b = 20.23;
	msgbuf.c = 'B';
	msgsnd(msgid,  &msgbuf, N, 0);

	msgbuf.mtype = 3;
	msgbuf.a = 30;
	msgbuf.b = 30.23;
	msgbuf.c = 'C';
	msgsnd(msgid,  &msgbuf, N, 0); //均发送到消息队列中。

	return 0;
}

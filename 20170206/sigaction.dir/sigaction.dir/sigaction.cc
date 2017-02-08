 ///
 /// @file    sigaction.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-06 10:39:32
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum,siginfo_t *p,void *p1)
{
	cout<<endl<<"before num"<<signum<<endl;
	sleep(1);
	cout<<"after num"<<signum<<endl;
}
int main(void)
{
	struct sigaction act;
	/*******
	 *int sigaction(int signum, const struct sigaction *act,struct sigaction *oldact);
	 *.signum为欲捕捉的信号;act包含处理函数的地址,阻塞信号结婚,信号处理方式
	 *成功返回0,失败返回-1,
	 *	 struct sigaction {
     *    	  void     (*sa_sigaction)(int, siginfo_t *, void *);
     *        sigset_t   sa_mask;//将要被阻塞的信号集合
     *        int        sa_flags;//信号处理方式掩码
     *      };
     *sa_sigaction信号处理函数指针,指向void handler(int iSignNum, siginfo_t *pSignInfo, void *pReserved)的函数.该函数的三个参数为,iSignNum处理的信号;
	 *pSignInfo与该信号有关的信息结构体指针;pReserved为NULL
	 *
	 ********/
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO|SA_RESTART|SA_NODEFER;
	/*SA_SIGINFO表示使用新的信号处理函数
	 *SA_RESTART表示若正在进行系统调用,此时收到信号,则处理完信号后,再返回到原来的系统调用
	 *SA_NODEFER表示可以被所有的信号打断,即若此时处理2号信号,仍然可以被2号信号打断,不断软中断,信号不丢失
	 *	默认是在执行2号信号时候不可以被自身打断
	 *SA_RESETHAND,处理完捕捉的信号后,自动撤销信号处理函数
	 */ 
	int ret;
	 ret=sigaction(SIGINT,&act,NULL);
	 ret=sigaction(SIGQUIT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction");
		return -1;
	}
	//while(1);
	char buf[20]={0};
	read(STDIN_FILENO,buf,sizeof(buf));
	cout<<buf;
	/***********
	 * sigaction()默认是当正在进行系统调用的时候,接收到信号量,本系统调用返回错误,
	 * 再执行相应的信号处理函数
	 *
	 */
	 return 0;
}

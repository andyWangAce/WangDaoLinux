#include"head.h"

int main()
{
	if(fork())
	{
		return 0;
	}
	else
	{
		int maxfd=3;
		sleep(1);
		setsid();
		chdir("/");
		umask(0);
		int i;
		for(i=0;i<maxfd;i++)
		{
			close(i);
		}
		while(1);
	}
}

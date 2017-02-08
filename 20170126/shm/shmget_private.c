#include"head.h"

int main()
{
	int shmid=shmget(IPC_PRIVATE,1<<20,IPC_CREAT);
	
	return 0;
}

#include"head.h"

void handle_request(int fdr)
{
	int newfd;
	recvm(fdr,&newfd);
	send_file(newfd);
	close(newfd);
}

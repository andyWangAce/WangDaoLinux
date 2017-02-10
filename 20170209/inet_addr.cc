 ///
 /// @file    inet_aton.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-09 14:14:43
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		cout<<"error args"<<endl;
		return -1;
	}
	int i=inet_addr(argv[1]);
	printf("%x\n",i);
	/*****
	 * in_addr_t inet_addr(const char *cp);
	 * 将点分十进制的字符串转化为网络字节序的32位二进制数
	 */ 
	struct in_addr addr;
	bzero(&addr,sizeof(addr));
	addr.s_addr=i;
	printf("%s\n",inet_ntoa(addr));
	/*****
	 * char *inet_ntoa(struct in_addr in);
	 * 其中struct in_addr
	 *	{
	 *		unsigned long int s_addr
	 *	}
	 * 将网络字节序的32位二进制数转化为点分十进制
	 */ 
	return 0;
}

///
/// @file    gethostbyname.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-09 20:52:23
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

int main(int argc ,char *argv[])
{
	/*	if(argc!=2)
		{
		cout<<"error args"<<endl;
		return -1;
		}
		*/
	struct hostent * host;
	//	host=gethostbyname(argv[1]);
	host=gethostbyname("www.baidu.com");
#if 0
	 *struct hostent *gethostbyname(const char *name);将主机/域名转化为IP地址
	* struct hostent {
		char  *h_name;            正式的域名名称
			char **h_aliases;         主机的别名
			int    h_addrtype;		 IP地址类型
			int    h_length;          IP地址有几个字节,IPV4为4个字节,32位;IPV6有16个字节,128位
			char **h_addr_list;       主机的IP地址,以网络字节数的形式显示
			*}
#endif
	if(NULL==host)
	{
		cout<<"gethostbyname error"<<endl;
		return -1;
	}
	cout<<"正式的域名: "<<host->h_name<<endl;
	char **aliases=host->h_aliases;
	for(;(*aliases)!=NULL;aliases++)//二级字符串指针,输出每个指针指向的字符串,法一利用解引用
	{
		cout<<"主机别名: "<<*aliases<<endl;
	}
	cout<<"IP地址类型 "<<host->h_addrtype<<endl;
	cout<<"IP地址字节数"<<host->h_length<<endl;
	char **list=host->h_addr_list;
	struct in_addr addr;
	bzero(&addr,sizeof(addr));
	char ip[16];
	int ret;
	for(int i=0;list[i]!=NULL;i++)//法二,利用字符数组形式
	{
		bzero(ip,sizeof(ip));
		inet_ntop(AF_INET,list[i],ip,16);
		cout<<"主机的IP地址列表 "<<ip<<endl;
		//	printf("%s\n",list[i]);
		/*****
		 * const char *inet_ntop(int af, const void *src,char *dst, socklen_t size);
		 * 将网络字节数形式转化为点分十进制地址
		 * af即address family.IPV4为AF_INET,IPV6为AF_INET6
		 * src指向一个ipv4/6类型的网络字节数形式的
		 * dst为欲要得到的点分十进制字符串
		 * size为点分十进制的字符串的长度,一般为16,3*4+3+1
		 *成功返回dst的值
		 */
		int *pi;

		ret=inet_pton(AF_INET,ip,pi);
		if(ret==0)
		{
			perror("inet_pton");
			return -1;
		}
		//cout<<*pi<<endl;
		printf("%x\n",*pi);
		/*
		 *int inet_pton(int af, const char *src, void *dst);
		 *成功返回1,失败返回0
		 *将点分十进制转化为网络字节数形式
		 */ 
	}
		return 0;
}

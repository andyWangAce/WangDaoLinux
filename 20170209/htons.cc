 ///
 /// @file    htons.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-09 14:00:44
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	int port=0x1234;//内存为34 12 00 00 
//	cout<<i<<endl;
//	cout<<htons(i)<<endl;
	int nport=htons(port);//改变后为 12 34 00 00 
	/*****
	 * uint16_t htons(uint16_t hostshort);
	 * 将小端形式的主机端口号转化为大端形式的主机端口号
	 * 其中的s表示只交换低2位字节
	 * uint16_t ntohs(uint16_t netshort);
	 * 将大端形式的主机端口号转化为小端形式的主机端口号
	 */ 
	printf("%x\n",port);
	printf("%x\n",nport);
	return 0;
}

 ///
 /// @file    1.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 10:48:33
 ///
 
#include <iostream>

int add(int x,int y)
{
	return x+y;
}
int add(int x ,int y ,int z)
{
	return x+y+z;
}
int main(void)
{
	std::cout<<"add="<<add(1,2)<<std::endl;
	return 0;
}


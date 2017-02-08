 ///
 /// @file    singleton.cc
 /// @author  Andy(wangyanchao_ace@126.com
 /// @date    2017-02-05 09:13:38
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Singleton
{
private:
	Singleton()
	{}
public:
	static Singleton * GetInstance()
	{
		if(_p==NULL)//若该类未创造对象时,建立一个堆对象
		{
			_p=new Singleton;
		}
		return _p;
	}
	/***********
	 *.单例模式即要求通过该类只能创建一个对象
	 *步骤:
	 *	1.将构造函数私有化
	 *	2.定义一个创建堆对象的静态函数,通过该函数new一个堆对象,调用构造函数
	 *	3.在类中定义一个静态的指针对象
	 */ 
private:
	static Singleton *_p;//成员数据是该类的静态指针型
};
Singleton *  Singleton::_p=NULL;
int main()
{
	Singleton *p1=Singleton::GetInstance();
	Singleton *p2=Singleton::GetInstance();
	Singleton *p3=Singleton::GetInstance();
	cout<<(void *)p1<<endl;
	cout<<(void *)p2<<endl;
	cout<<(void *)p3<<endl;
	return 0;
}

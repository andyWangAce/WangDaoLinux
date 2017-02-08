 ///
 /// @file    computer.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 22:40:28
 ///
#include <unistd.h>//使用sleep()函数时候需要调用unistd.h
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
	Computer(const char *brand,double price)
	:_brand(new char[strlen(brand)+1])
	 ,_price(price)//初始化表达式写与构造函数的头和函数体之间,以:开头,不同变量之间以,隔开
	{
		strcpy(_brand,brand);
	}
	void Print()
	{	
		cout<<_brand<<endl;
		cout<<_price<<endl;
	}
	~Computer()
	{
		cout<<"destructor:"<<_brand<<endl;
		delete _brand;
	
	}
	/***********
	 *.析构函数名为~加类名,无参数,无返回值
	 *.定义在堆区的对象:析构函数在对象生命周期结束时由OS自动调用,但是与构造函数相比,析构函数可以显式主动调用
	 *但是一般不主动调用,以为在声明周期结束时候系统会自动调用析构函数,造成多次free的段错误
	 *.默认析构函数无法释放堆区的内存,需要自己主动释放
	 */
private:
	char * _brand;
	double _price;
};
Computer c3("msi",1222);//定义在全局/静态区的对象,当main函数结束时自动调用析构函数
int main(void)
{
	{
	Computer c1("ASUS",100);
	c1.Print();
	}//c1生命周期在其大括号内,出了括号,结束生命,系统自动调用析构函数
	{
	Computer *c2=new Computer("HP",22);
	c2->Print();
	//delete c2;
	/*定义在堆区域的对象,必须自己delete释放空间,调用析构函数,其生命周期结束的时候,系统不会自动调用析构函数
	 */
	}
	c3.Print();
	sleep(2);
	return 0;
}

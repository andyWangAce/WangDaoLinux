 ///
 /// @file    computer.cc
 /// @author  Andy(wangyanchao_ace@126.com
 /// @date    2017-02-04 20:21:23
 ///
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
	Computer(const char* brand,double Price)
	:_Price(Price)
	 ,_brand(new char[strlen(brand)+1])
	{
		strcpy(_brand,brand);
		cout<<"add sucess"<<endl;
		_TotalPrice+=Price;
	}
	~Computer()
	{
		delete [] _brand;
		_TotalPrice-=_Price;
	}
	static void Print(const Computer &rhs)
	{
		cout<<rhs._brand<<endl;
		cout<<_TotalPrice<<endl;
	}
	/*****
	 *.类中的静态成员函数为所有对象共享,其内部只能使用静态数据或调用静态函数,因为静态成员函数
	 *内部不含this指针,所有没办法直接使用静态数据或者静态函数,只能通过参数传递的方法使用对象
	 *的非静态数据.
	 */
private:
	double _Price;
	char * _brand;
	static double  _TotalPrice;
	char i;
};

double Computer::_TotalPrice=0;
/************
 * .静态数据成员,是在编译的时候进行创建,该类的所有对象共享同个静态数据成员
 * 此外静态数据成员还需要需要在类外进行声明 类型 类名::变量名=初值;
 **********/
int main()	
{
	Computer c1("ASUS",1000);
	c1.Print(c1);
	Computer::Print(c1);//静态成员函数,可以直接通过类名使用,类名::静态成员函数
	Computer c2("MAC",1500);
	c2.Print(c2);
	c1.~Computer();
	Computer::Print(c2);
	cout<<"sizeof(double)"<<sizeof(double)<<endl;//double 8个字节
	cout<<"sizeof(char *)"<<sizeof(char *)<<endl;
	cout<<"sizeof(Computer)"<<sizeof(Computer)<<endl;
	/******
	 *64位系统,8个字节表示地址,故指针大小为8个字节,类的数据成员大小不包含静态数据成员的大小,
	 *且要进行内存对齐,即类的数据成员的总大小为8的倍数.
	 *****/ 
	return 0;
}

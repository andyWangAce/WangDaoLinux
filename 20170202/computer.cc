 ///
 /// @file    computer.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 17:00:12
 ///
#include <string> 
#include <iostream>
using std::cout;
using std::endl;
using std::string;


const int MaxSize=100;//b位于文字常量区而不是位于全局/静态区

class Computer{//定义方法的第一种方法,在类中定义方法
public:
	void Print()
	{
		cout<<"brand:"<<_brand<<endl;
		cout<<"price:"<<_price<<endl;
	}
	void SetBrand(string  brand)
	{
		_brand=brand;
	}
	void SetPrice(double price)
	{
		_price=price;
	}
private :
	string  _brand;//定义类的属性即类中的变量,其名称前常加_
	double  _price=100;
};//定义类,结尾加;

class Computer1{//定义方法的第二种方法,在类中声明方法即函数,在类外面定义
public:
	void Print();
	void SetBrand(string  brand);
	void SetPrice(double price);
private :
	string  _brand;//定义类的属性即类中的变量,其名称前常加_
	double  _price;
};

void Computer1::Print()//在类外定义具体的方法即函数时候要写类名::函数名
{
	cout<<"brand:"<<_brand<<endl;
	cout<<"price:"<<_price<<endl;
}
void Computer1::SetBrand(string  brand)
{	
	_brand=brand;
}
void Computer1::SetPrice(double price)
{
	_price=price;
}
int main(void)
{
	Computer com;
	com.SetBrand("ASUS");
	com.SetPrice(5999);
	cout<<sizeof(com)<<endl;//sizeof(com),得到的是对象com中的变量的大小和,对象的方法存放于代码段
	string s;
	cout<<sizeof(s)<<endl;
	double d;
	cout<<sizeof(d)<<endl;
	long int li;
	cout<<sizeof(li)<<endl;
	long long int lli;
	cout<<sizeof(lli)<<endl;
	float f;
	cout<<sizeof(f)<<endl;
	com.Print();
	Computer com1;
	com1.SetBrand("ASUS");
	com1.SetPrice(5999);
	com1.Print();
	Computer com2;
	cout<<sizeof(com2)<<endl;
	return 0;
}

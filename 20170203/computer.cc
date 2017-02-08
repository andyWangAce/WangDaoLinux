
 /// @file    computer.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-03 10:46:37
 ///
#include <unistd.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
	Computer(const char *brand,double price)
	:_brand(new char[strlen(brand)+1])
	,_price(price)
	{
		memset(_brand,0,sizeof(_brand));
		strcpy(_brand,brand);
		cout<<"Constructor"<<endl;
	}
	void Print()
	{
		cout<<_brand<<endl;
		cout<<_price<<endl;
	}
	
/********************
*	//该函数类型系统提供的默认复制构造函数,不能创建堆区,该拷贝方式称为浅拷贝
*	Computer(const Computer &rsh){
*		_brand=rsh._brand;
*		_price=rsh._price;
*		cout<<"the copy constructor"<<endl;
*	}
*****************/
	//自定义the copy constructor,使得_brand指向另外一块内容相同的堆区,深拷贝
	Computer(const Computer &rsh)
	:_brand(new char[strlen(rsh._brand)+1])
	 ,_price(rsh._price)
	{
		strcpy(_brand,rsh._brand);
		cout<<"user the copy constructor"<<endl;
	}

	//析构函数
	~Computer(){
		cout<<"destructor"<<_brand<<endl;
		delete[] _brand;
	}
	
	//赋值运算符
	Computer &operator = (const Computer & rsh){
		if(this==&rsh) 
			return *this;
		delete []_brand;
		cout<<"delete old"<<endl;
		_brand=new char[strlen(rsh._brand)+1];
		memset(_brand,0,sizeof(_brand));
		strcpy(_brand,rsh._brand);
		return *this;
	}
	/*************
	 *系统提供默认的赋值运算符的重载,但是无法做到堆区的复制,使得old的_brand指向new的_brand,不仅
	 *造成了old的_brand指向的堆区丢失,发生内存泄漏,还会在释放new和old时候两次free_brand指向区域,
	 *故需要自定义赋值运算符.
	 *.形式如下 类型 &operator =(const 类型 & 对象名a)
	 *.还要考虑自复制这种特殊情况
	 */
private:
	char * _brand;
	double _price;
};
int main(void)
{
	Computer c1("ASUS",1000);
	c1.Print();
	cout<<"-------------"<<endl;
	Computer c2=c1;
	c2.Print();	
	cout<<"------------"<<endl;
	Computer c3("MAC",123);
	c1=c3;
	c1=c1;
	c1.Print();
	sleep(2);
	//c2与c1的_brand指向同一块区域,对象生命周期结束时候,会两次free同一堆区,发生段错误
	return 0;
}

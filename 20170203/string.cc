 ///
 /// @file    string.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-03 22:21:34
 ///
#include <string.h> 
#include <iostream>
using std::cout;
using std::endl;
#define MaxSize 10
class String
{
public:
	//默认构造函数
	String()
	{
	//	cout<<&_pstr<<endl;
	//	_pstr=new char[MaxSize];
	//	memset(_pstr,0,sizeof(_pstr));
	}

	//自定义构造函数
	String(const char *pstr)
	: _pstr(new char[strlen(pstr)+1])
	{
		cout<<&_pstr<<endl;
		memset(_pstr,0,sizeof(_pstr));
		strcpy(_pstr,pstr);
	}

	//复制构造函数
	String(const String &rhs)
	: _pstr(new char[strlen(rhs._pstr)+1])   
	{
		cout<<&_pstr<<endl;
		memset(_pstr,0,sizeof(_pstr));
		strcpy(_pstr,rhs._pstr);
	}

	//重载赋值表达式
	String & operator=(const String &rhs)
	{
		if(this==&rhs)
			return *this;
		delete [] _pstr;
		_pstr=new char[strlen(rhs._pstr)+1];
		strcpy(_pstr,rhs._pstr);
		return *this;
	}
	//打印函数
	void Print()
	{
		cout<<_pstr<<endl;
	}
	//析构函数
	~String()
	{
		cout<<&_pstr<<endl;
		cout<<"destructor"<<_pstr<<endl;
		delete [] _pstr;
	}
private:
	char *_pstr;
};
int main(void)
{
	String str1;
	str1.Print();

	cout<<"-----------------"<<endl;
	String str2="Hello,world";
	String str3="wangdao";

	str2.Print();
	str3.Print();
	str2=str3;
	str2.Print();

	String str4=str3;
	str4.Print();
	return 0;
	}
	

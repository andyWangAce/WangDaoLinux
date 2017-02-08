/
 /// @file    point.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-04 10:48:39
 ///
#include <stdio.h> 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int x,int y,int& z)
	:_x(x)
	 ,_y(y)
	 ,_ref(z)
	{
		cout<<"constructor"<<endl;
	}
	/************
	 *常量成员即const类型的成员,必须在初始化列表中赋值,经过初始化后,只能对其值进行修改
	 *引用成员也必须在初始化列表中进行赋值
	 */ 
	void Print()
	{
		cout<<"("<<_x<<","<<_y<<","<<_ref<<")";
	}
private:
	const int _x,_y;
	int &_ref;
};

class Line
{
public:
	Line(int x1,int y1,int &z1,int x2,int y2,int& z2)
	:_beg(x1,y1,z1)
	,_end(x2,y2,z2)
	{	
		cout<<"construtor Line"<<endl;
	}
	void Print()
	{
		_beg.Print();
		cout<<"->";
		_end.Print();
	}
private:
	Point _beg,_end;//当类的成员的是对象时候,常在初始化列表中对成员赋值
};
int main()
{	
//	Point p1(1,3,4);
//	p1.Print();

/*	char *p=new char[4];//new分配堆空间的时候,会自动对其赋初值\0
	for(int i=0;i<4;i++)
	{
		printf("%d\n",p[i]);
	}
*/
	int i=3,j=6;
	Line l1(1,2,i,4,5,j);
	l1.Print();
	return 0;
}

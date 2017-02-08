 ///
 /// @file    string.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 15:45:33
 ///
 
#include <iostream>
#include <string>//使用string类型,需要引用头文件#include<string>

using std::cout;
using std::endl;
using std::string;

int main(void)
{
//	string s1=new string(hello);
	string s1="hello";
	cout<<s1<<endl;
	string s2=s1;//c++中的string类型之间可以直接复制
	cout<<s2<<endl;
	s1=s1+s2;//string之间相加可以实现字符串拼接
	cout<<s1<<endl;
	const char *p1=s1.c_str();//string s;s.c_str(),实现将string类型的字符串转化为标准C的字符串
	cout<<p1<<endl;
	string s3=s2+"world";//string类型的字符串和"字符串"相加实现字符串拼接
	cout<<s3<<endl;
	cout<<s3[0]<<endl;//string类型的字符串支持数组类型的随机访问
	cout<<"size of s3="<<s3.size()<<endl;
	cout<<"size of s3="<<s3.length()<<endl;//s.size()或者s.length()得到字符串的长度
	string::iterator it;//迭代器,起始于begin处,结束于end之前
	for(it=s3.begin();it!=s3.end();it++)
	{
		cout<<*it;
	}
	cout<<endl;
	int pos=s3.find("he");//int s.find("s1"),查找s1在s中的位置,失败返回-1
	cout<<s3.substr(pos,5)<<endl;
	/*
	 s.sub(pos,len),获得s的子串,其中pos为在母串的起始下标(从0开始计算),len为子串的长度
	*/
	 return 0;
}

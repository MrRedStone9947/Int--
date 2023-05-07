#include"int++.h"
using namespace std;

int main(){
	//创建高精度整数,不构造默认值为0 ,长度为1 
	BigInt x,y;
	//也可以构造
	//通过字符串(String) BigInt x("123456")
	//通过数字 BigInt x(123456)
	//通过另一个高精度数 k(假设BigInt k("123456")),BigInt x(k); 
	
	//输入
	cin>>x>>y;
	//输出
	cout<<x<<" "<<y<<endl;
	
	//加法 
	cout<<x+y<<endl;
	//减法 
	cout<<x-y<<endl;
	//乘法 
	cout<<x*y<<endl;
	//除法
	cout<<x/y<<endl;
	//除此之外支持 +=,-=,*=,/=,++,--
	//也可以高精度和低精度进行运算,例:
	cout<<x+3<<endl;
	
	//其他功能
	//获取长度
	cout<<x.length()<<" "<<y.length()<<endl;
	//转数字(慎用),数字过大时无法使用,会返回奇怪的数字 
	cout<<x.toInt()<<" "<<y.toInt()<<endl;
	//转字符串 
	cout<<x.toString()<<" "<<y.toString()<<endl;
	//取第n位，O(1)，例如x=123456,x[2]=2,超过数字长度或者第0位会返回0 
	cout<<x[1]<<" "<<y[2]<<endl;
	//也支持负数下标，O(1),例如x=123456,x[-1]=6, 超过数字长度或者第0位会返回0 
	cout<<x[-1]<<" "<<y[-2]<<endl; 
	return 0;
}


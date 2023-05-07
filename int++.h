#ifndef INT++_H
#define INT++_H

#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
using namespace std;

class BigInt{
	private:
		vector<char> v;
		int size;
		
		void init(){
			v=vector<char>();
			size=1;
			v.push_back('0');
			v.push_back('0');
		}
		void init(string x){
			v=vector<char>();
			size=x.size();
			char st='0';
			int r=0;
			if(x[0]=='-'){
				r=1;
				size--;
				if(x[1]!='0'){
					st='1';
				}
			}
			v.push_back(st);
			for(int i=x.size()-1;i>=r;i--){
				v.push_back(x[i]);
			}
		}
		void init(long long x){
			v=vector<char>();
			char st='0';
			if(x<0){
				st='1';
			}
			v.push_back(st);
			size=0;
			if(x==0){
				v.push_back('0');
				size=1;
				return;
			}
			x=abs(x);
			while(x){
				size++;
				v.push_back(x%10+'0');
				x/=10;
			}
		}
		void init(BigInt x){
			v=vector<char>();
			size=x.size;
			for(int i=0;i<=size;i++){
				v.push_back(x.v[i]);
			}
		}
		
		bool isEqual(BigInt x){
			if(size!=x.size){
				return 0;
			}
			for(int i=0;i<=size;i++){
				if(v[i]!=x.v[i]){
					return 0;
				}
			}
			return 1;
		}
		bool isSmaller(BigInt x){
			if(size<x.size){
				return 1;
			}
			if(size>x.size){
				return 0;
			}
			if(v[0]=='1'&&x.v[0]=='0'){
				return 1;
			}
			if(v[0]=='0'&&x.v[0]=='1'){
				return 0;
			}
			for(int i=size;i>=1;i--){
				if(v[i]<x.v[i]){
					return 1;
				}
				if(v[i]>x.v[i]){
					return 0;
				}
			}
			return 0;
		}
		bool isBigger(BigInt x){
			if(size<x.size){
				return 0;
			}
			if(size>x.size){
				return 1;
			}
			if(v[0]=='1'&&x.v[0]=='0'){
				return 0;
			}
			if(v[0]=='0'&&x.v[0]=='1'){
				return 1;
			}
			for(int i=size;i>=1;i--){
				if(v[i]<x.v[i]){
					return 0;
				}
				if(v[i]>x.v[i]){
					return 1;
				}
			}
			return 0;
		}
			
		BigInt add(BigInt x){
			BigInt ret;
			int k=0;
			for(int i=1;i<=max(size,x.size);i++){
				int a=0,b=0;
				if(i<=size){
					a=v[i]-'0';
				}
				if(i<=x.size){
					b=x.v[i]-'0';
				}
				int t=a+b+k;
				k=t/10;
				t%=10;
				if(i>ret.size){
					ret.size++;
					ret.v.push_back('0');
				}
				ret.v[i]=t+'0';
			}
			while(k){
				ret.size++;
				ret.v.push_back(k%10+'0');
				k/=10;
			}
			return ret;
		}
		BigInt minus(BigInt x){
			BigInt ret;
			int k=0;
			for(int i=1;i<=size;i++){
				int a=0,b=0;
				if(i<=size){
					a=(v[i]-'0');
				}
				if(i<=x.size){
					b=(x.v[i]-'0');
				}
				int t=a-b-k;
				if(t<0){
					t+=10;
					k=1;
				}
				else{
					k=0;
				}
				if(i>ret.size){
					ret.size++;
					ret.v.push_back('0');
				}
				ret.v[i]=t+'0';
			}
			while(ret.v[ret.size]=='0'&&ret.size>1){
				ret.size--;
				ret.v.pop_back();
			}
			return ret;
		}
		BigInt negative(){
			BigInt ret=*this;
			if(ret.v[0]=='0'){
				ret.v[0]='1';
			}
			else{
				ret.v[0]='0';
			}
			return ret;
		}
		BigInt mul(BigInt x){
			BigInt ret;
			if((v[0]=='1'&&x.v[0]=='0')||(v[0]=='0'&&x.v[0]=='1')){
				ret.v[0]='1';
			}
			for(int i=1;i<=size;i++){
				int k=0;
				for(int j=1;j<=x.size;j++){
					int pos=i+j-1;
					if(pos>ret.size){
						ret.size++;
						ret.v.push_back('0');
					}
					int t=(ret.v[pos]-'0')+(v[i]-'0')*(x.v[j]-'0')+k;
					k=t/10;
					t%=10;
					ret.v[pos]=t+'0';
				}
				ret.size++;
				ret.v.push_back(k+'0');
			}
			while(ret.v[ret.size]=='0'&&ret.size>1){
				ret.size--;
				ret.v.pop_back();
			}
			return ret;
		}
		BigInt div(BigInt x){
			BigInt ret;
			if((v[0]=='1'&&x.v[0]=='0')||(v[0]=='0'&&x.v[0]=='1')){
				ret.v[0]='1';
			}
			if(this->absolute()<x.absolute()||*this==0){
				return BigInt(0);
			}
			for(int i=1;i<size;i++){
				ret.size++;
				ret.v.push_back('0');
			}
			BigInt t(v[size]-'0');
			for(int i=size-1;i>size-x.size+1;i--){
				t=t*10+(v[i]-'0');
			}
			for(int i=size-x.size+1;i>=1;i--){
				t=t*10+(v[i]-'0');
				int cnt=0;
				while(t>=x){
					t-=x;
					cnt++;
				}
				ret.v[i]=cnt+'0';
			}
			while(ret.v[ret.size]=='0'&&ret.size>1){
				ret.size--;
				ret.v.pop_back();
			}
			return ret;
		}
		BigInt absolute(){
			BigInt ret=*this;
			ret.v[0]='0';
			return ret;
		}
		
		void input(){
			string s;
			cin>>s;
			init(s);
		}
		void print(){
			if(v[0]=='1'){
				printf("-");
			}
			for(int i=size;i>=1;i--){
				printf("%c",v[i]);
			}
		}
		int get(int index){
			int pos;
			if(index==0||index>size){
				pos=0;
			}
			else if(index<0){
				pos=abs(index);
				if(pos>size){
					pos=0;
				}
			}
			else{
				pos=size-index+1;
			}
			return v[pos]-'0';
		}
	public:
		BigInt(){
			init();
		}
		BigInt(string x){
			init(x);
		}
		BigInt(long long x){
			init(x);
		}
		
		int operator[](int index){
			return get(index);
		}
		bool operator==(BigInt x){
			return isEqual(x);
		}
		bool operator==(long long x){
			return *this==BigInt(x);
		}
		bool operator<(BigInt x){
			return isSmaller(x);
		}
		bool operator<(long long x){
			return *this<BigInt(x);
		}
		bool operator>(BigInt x){
			return isBigger(x);
		}
		bool operator>(long long x){
			return *this>BigInt(x);
		}
		bool operator<=(BigInt x){
			return *this<x||*this==x;
		}
		bool operator<=(long long x){
			return *this<=BigInt(x);
		}
		bool operator>=(BigInt x){
			return *this>x||*this==x;
		}
		bool operator>=(long long x){
			return *this>=BigInt(x);
		}
		BigInt operator+(BigInt x){
			if(x>=0){
				return add(x);
			}
			else{
				return minus(x.absolute());
			}
		}
		BigInt operator+(long long x){
			return *this+BigInt(x);
		}
		BigInt operator+=(BigInt x){
			BigInt ret=*this+x;
			init(ret);
			return ret;
		}
		BigInt operator+=(long long x){
			return *this+=BigInt(x);
		}
		BigInt operator++(int x){
			return (*this+=1);
		}
		BigInt operator-(BigInt x){
			if(x>*this){
				return -(x-*this);
			}
			else if(x<0){
				return add(x.absolute());
			}
			else{
				return minus(x);
			}
		}
		BigInt operator-(long long x){
			return *this-BigInt(x);
		}
		BigInt operator-(){
			return negative();
		}
		BigInt operator-=(BigInt x){
			BigInt ret=*this-x;
			init(ret);
			return ret;
		}
		BigInt operator-=(long long x){
			return *this-=BigInt(x);
		}
		BigInt operator--(int x){
			return (*this-=1);
		}
		BigInt operator*(BigInt x){
			return mul(x);
		}
		BigInt operator*(long long x){
			return (*this)*BigInt(x);
		}
		BigInt operator*=(BigInt x){
			BigInt ret=(*this)*x;
			init(ret);
			return ret;
		}
		BigInt operator*=(long long x){
			return (*this)*=BigInt(x);
		}
		BigInt operator/(BigInt x){
			return div(x);
		}
		BigInt operator/(long long x){
			return (*this)/BigInt(x);
		}
		BigInt operator/=(BigInt x){
			BigInt ret=(*this)/x;
			init(ret);
			return ret;
		}
		BigInt operator/=(long long x){
			return (*this)/=BigInt(x);
		}
		
		friend ostream& operator<<(ostream& os,BigInt x);
		friend istream& operator>>(istream& os,BigInt& x);
		
		int length(){
			return size;
		}
		long long toInt(){
			long long ret=0;
			for(int i=size;i>=1;i--){
				ret=(ret+(v[i]-'0'))*10;
			}
			ret/=10;
			if(v[0]=='1'){
				ret=-ret;
			}
			return ret;
		}
		string toString(){
			string ret="";
			if(v[0]=='1'){
				ret+="-";
			}
			for(int i=size;i>=1;i--){
				ret+=v[i];
			}
			return ret;
		}
};
ostream& operator<<(ostream& os,BigInt x){
	x.print();
	return os;
}
istream& operator>>(istream& os,BigInt& x){
	x.input();
	return os;
}

#endif

#include<iostream>
#include<string>
using namespace std;
template <typename T>T manx(T a,T b){
	return a>b?a:b;
}

int main(){
	int x=1;
	int y=2;
	cout<<manx(x,y)<<endl;
	cout<<manx("sb","250")<<endl;
	cout<<manx(1.14,5.14);
}

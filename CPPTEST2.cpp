#include<iostream>
#include<stack>
using namespace std;
int main(){
	int t;
	stack<int> s;
	while(cin>>t){
		s.push(t);
	}
	while(!s.empty()){
		cout<<s.top()<<endl;
		s.pop();
	}
	cout<<"end"<<endl;
}

#include<iostream>
#include<unordered_map>
#include<string>
#include<map>
using namespace std;
int main(){
	unordered_map<string,int>tab;
	tab["666"]=10;
	tab["666"]=11;
	cout<<tab["666"];
	map<string,int>manp;
	manp["666"]=10;
	manp["666"]=11;
	cout<<manp["666"];
}

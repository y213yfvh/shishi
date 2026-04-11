#include<iostream>
#include<list>
#include<vector>
#include<map>
using namespace std;
template<typename T>
struct tree{
	tree* left;
	tree* right;
	T data;
	int weight;
	tree(tree*,tree*,T,int);
};
template<typename T>
tree<T>::tree(tree* left,tree* right,T data,int weight){
	this->data=data;
	this->left=left;
	this->right=right;
	this->weight=weight;
}
template<typename T>
class Tree{
	public:
		tree<T>* root;
		Tree();
		~Tree();
		Tree(vector<tree<T>*>&);
		void printTree();
		void printTree(tree<T>*);
		void CODE(map<T,string>&);
		void CODE(string s,tree<T>*,map<T,string>&);
};
template<typename T>
Tree<T>::Tree(){
	this->root=nullptr;
}
template<typename T>
Tree<T>::Tree(vector<tree<T>*>& v){
	if(v.empty()){
		this->root=nullptr;
		return;
	}
	int len=v.size();
	while(len>1){
		int x1,x2,w1=2147483647,w2=2147483647;
		for(int i=0;i<len;i++){
			if(v[i]->weight<w1){
				w1=v[i]->weight;
				x1=i;
			}
		}
		for(int i=0;i<len;i++){
			if(v[i]->weight<w2&&i!=x1){
				w2=v[i]->weight;
				x2=i;
			}
		}
		tree<T>* a=v[x1];
		tree<T>* b=v[x2];
		tree<T>* tr=new tree<T>(a,b,-1,w1+w2);
		if(x1<x2){int t=x1;x1=x2;x2=t;}
		v.erase(v.begin()+x1);
		v.erase(v.begin()+x2);
		v.push_back(tr);
		len--;
	}
	this->root=v[0];
}
template<typename T>
void Tree<T>::printTree(){
	tree<T>* cur=this->root;
	if(cur!=nullptr){
		printTree(cur);
	}
}
template<typename T>
void Tree<T>::printTree(tree<T>* cur){
	if(cur->left!=nullptr)printTree(cur->left);
	if(cur->data+1)cout<<cur->data<<endl;
	if(cur->right!=nullptr)printTree(cur->right);
}
template<typename T>
void clearTree(tree<T>* node) {
    if (!node) return;
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}
template<typename T>
Tree<T>::~Tree() {
    clearTree(root);
}
template<typename T>
void Tree<T>::CODE(map<T,string>& Map){
	string s="";
	tree<T>* cur=this->root;
	if(cur!=nullptr)CODE(s,cur,Map);
}
template<typename T>
void Tree<T>::CODE(string s,tree<T>* cur,map<T,string>& Map){
	if(cur->left!=nullptr){
		CODE(s+"0",cur->left,Map);
	}
	if(cur->left==nullptr&&cur->right==nullptr){
		Map[cur->data]=s;
	}
	if(cur->right!=nullptr){
		CODE(s+"1",cur->right,Map);
	}
}
int main(){
	int n,t,x;
	cin>>n;
	vector<tree<int>*> v;
	for(int i=0;i<n;i++){
		cin>>t;
		cin>>x;
		tree<int>* xx=new tree<int>(nullptr,nullptr,t,x);
		v.push_back(xx);
	}
	map<int,string> Map;
	Tree<int> tr(v);
	tr.CODE(Map);
	for(auto& p:Map){
		cout<<p.first<<":"<<p.second<<endl;
	}
}

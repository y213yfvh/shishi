#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using namespace std;
template<typename T>
struct tree{
	tree* left;
	tree* right;
	T data;
	tree(tree*,tree*,T);
};
template<typename T>
tree<T>::tree(tree* left,tree* right,T data){
	this->data=data;
	this->left=left;
	this->right=right;
}
template<typename T>
class Tree{
	public:
		tree<T>* root;
		Tree();
		~Tree();
		Tree(vector<T>&);
		void printTree();
		void MprintTree();
		void MprintTree(tree<T>*);
		void mprintTree();
};
template<typename T>
Tree<T>::Tree(){
	this->root=nullptr;
}
template<typename T>
void Tree<T>::MprintTree(){
	MprintTree(this->root);
}
template<typename T>
void Tree<T>::MprintTree(tree<T>* cur){
	if(cur==nullptr)return;
	MprintTree(cur->left);
	cout<<cur->data<<endl;
	MprintTree(cur->right);
}
template<typename T>
void Tree<T>::mprintTree(){
	stack<tree<T>*> s;
	tree<T>* p=this->root;
	int len=0;
	while(p!=nullptr||len>0){
		while(p!=nullptr){
			s.push(p);
			len++;
			p=p->left;
		}
		p=s.top();
		s.pop();
		len--;
		cout<<p->data<<endl;
		p=p->right;
	}
}
template<typename T>
Tree<T>::Tree(vector<T>& v){
	if(v.empty())return;
	queue<tree<T>*> que;
	tree<T>* root=new tree<T>(nullptr,nullptr,v[0]); 
	que.push(root);
	int i=1;
	while(i<v.size()){
		tree<T>* cur=que.front();
		que.pop();
		cur->left=new tree<T>(nullptr,nullptr,v[i++]);
		que.push(cur->left);
		if(i>=v.size())break;
		cur->right=new tree<T>(nullptr,nullptr,v[i++]);
		que.push(cur->right);
	}
	this->root=root;
}
template<typename T>
void Tree<T>::printTree(){
	if(this->root==nullptr)return;
	queue<tree<T>*> que;
	que.push(this->root);
	while(que.size()){
		cout<<que.front()->data<<endl;
		if(que.front()->left!=nullptr){
			que.push(que.front()->left);
		}
		if(que.front()->right!=nullptr){
			que.push(que.front()->right);
		}
		que.pop();
	}
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

int main(){
	vector<int> v;
	int n,t;
	cin>>n;
	while(n--){
		cin>>t;
		v.push_back(t);
	}
	Tree<int> tt(v);
	tt.mprintTree();
	tt.MprintTree();
	//tt.printTree();
}

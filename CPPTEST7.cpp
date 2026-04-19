#include<iostream>
#include<fstream>
using namespace std;
class Node{
	public:
		int data;
		int weight;
		Node* left;
		Node* right;
		Node(int,int,Node*,Node*);
};
Node::Node(int data,int weight,Node* left,Node* right){
	this->weight=weight;
	this->data=data;
	this->left=left;
	this->right=right;
}
class to01Node{
	public:
		int data;
		char to01[64];
		to01Node* next;
		to01Node(int,char[],to01Node*);
};
to01Node::to01Node(int data,char to01[64],to01Node* next){
	this->data=data;
	this->next=next;
	for(int i=0;i<64;i++){
		this->to01[i]=to01[i];
	}
}
class to01List{
	public:
		to01Node* head;
		to01Node* tail;
		to01List(void);
};
class Tree{
	public:
		Node* root;
		Tree(int,int);
};
Tree::Tree(int data,int weight){
	this->root=new Node(data,weight,nullptr,nullptr);
}
class lNode{
	public:
		Tree* data;
		lNode* next;
		lNode(Tree*,lNode*);
};
lNode::lNode(Tree* dat,lNode* ptr){
	data=dat;
	next=ptr;
}
class List{
	public:
		lNode* tail;
		int length;
		List(void);
		~List(void);
		void joinNode(int,Tree*);
		void deleteNode(int);
		void changeNode(int,Tree*);
		void printNode(int);
		void appendNode(Tree*);
		void printEveryNode();
		void connectList(List*);
		int listLength();
		int findData(Tree*);
};
List::List(){
	tail=new lNode(0,nullptr);
	tail->next=tail;
	length=0;
}
List::~List(){
    if(tail==nullptr)return;
    lNode* head=tail->next;
    lNode* cur=head->next;
    while(cur != head){
        lNode* next=cur->next;
        delete cur;
        cur=next;
    }
    delete head;
    tail=nullptr;
    length=0;
}
void List::appendNode(Tree* data){
	lNode* cur=this->tail;
	lNode* newNode=new lNode(data,this->tail->next);
	cur->next=newNode;
	this->length++;
	this->tail=newNode;
}
void List::joinNode(int num,Tree* data){
	lNode* head=this->tail->next;
	lNode* cur=head;
	num--;
	while(num--){
		if(cur->next!=head)cur=cur->next;
		else {
			cout<<"error:to big!"<<endl;
			return;
		}
	}
	if(cur->next==head){
		List::appendNode(data);
		return;
	}
	lNode* newNode=new lNode(data,cur->next);
	cur->next=newNode;
	this->length++;
}
void List::deleteNode(int num){
	lNode* head=this->tail->next;
	lNode* cur=head;
	num--;
	while(num--){
		if(cur->next!=head)cur=cur->next;
		else {
			cout<<"error:to big!"<<endl;
			return;
		}
	}
	if(cur->next==this->tail){
		this->tail=cur;
	}
	lNode* p=cur->next;
	cur->next=p->next;
	delete p;
	this->length--;
}
void List::changeNode(int num,Tree* data){
	lNode* head=this->tail->next;
	lNode* cur=head;
	while(num--){
		if(cur->next!=head)cur=cur->next;
		else {
			cout<<"error:to big!"<<endl;
			return;
		}
	}
	cur->data=data;
}
void List::printNode(int num){
	lNode* head=this->tail->next;
	lNode* cur=head;
	while(num--){
		if(cur->next!=head)cur=cur->next;
		else {
		cout<<"error:to big!"<<endl;
		return;
		}
	}
	cout<<cur->data<<endl;
}
void List::printEveryNode(){
	lNode* head=this->tail->next;
	lNode* cur=head;
	while(cur->next!=head){
		cur=cur->next;
		cout<<cur->data<<endl;
	}
	cout<<"end"<<endl;
}
int List::listLength(){
	return this->length;
}
int List::findData(Tree* dat){
	lNode* head=this->tail->next;
	int cnt=0;
	lNode* cur=head;
	while(cur->next!=head){
		cur=cur->next;
		cnt++;
		if(cur->data==dat)return cnt;
	}
	return -1;
}
void List::connectList(List* list2){
	if(list2->length>0){
		lNode* tail1=this->tail;
		lNode* tail2=list2->tail;
		lNode* cur=tail1->next;
		tail1->next=tail2->next->next;
		lNode* p=tail2->next;
		tail2->next=cur;
		delete p;
		this->tail=tail2;
		this->length+=list2->length;
		list2->tail=new lNode(0,nullptr);
		list2->tail->next=list2->tail;
		list2->length=0;
	}
}
class forest:public List{
	public:
		forest();
		void buildHuffmanTree();
};
forest::forest(){
	tail=new lNode(0,nullptr);
	tail->next=tail;
	length=0;
}
void forest::buildHuffmanTree(){
	int min1=2147483647,min2=2147483647;
	lNode* minTree1Last=nullptr;
	lNode* minTree2Last=nullptr;
	lNode* head=this->tail->next;
	lNode* cur;
	while(this->length!=1){
		while(cur->next!=head){
			if(min1<cur->next->data->root->weight){
				min1=cur->next->data->root->weight;
				minTree1Last=cur;
			}else if(min2<cur->next->data->root->weight){
				min2=cur->next->data->root->weight;
				minTree2Last=cur;
			}
		}
		minTree1Last->next->data->root=
		new Node(-1,min1+min2,
		minTree1Last->next->data->root,
		minTree2Last->next->data->root);
		Tree* de=minTree2Last->next->data;
		lNode* del=minTree2Last->next;
		minTree2Last->next=minTree2Last->next->next;
		delete de;delete del;
		this->length--;
	}
}
int main(){
	fstream f;
	f.open("test.txt",ios::app);
	f.write("666",3);
}

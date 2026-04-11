#include<iostream>
using namespace std;
class Node{
	public:
		int data;
		Node* next;
		Node(int,Node*);
};
Node::Node(int dat,Node* ptr){
	data=dat;
	next=ptr;
}
class List{
	public:
		Node* tail;
		int length;
		List(void);
		~List(void);
		void joinNode(int,int);
		void deleteNode(int);
		void changeNode(int,int);
		void printNode(int);
		void appendNode(int);
		void printEveryNode();
		void connectList(List*);
		int listLength();
		int findData(int);
};
List::List(){
	tail=new Node(0,nullptr);
	tail->next=tail;
	length=0;
}
List::~List(){
    if(tail==nullptr)return;
    Node* head=tail->next;
    Node* cur=head->next;
    while(cur != head){
        Node* next=cur->next;
        delete cur;
        cur=next;
    }
    delete head;
    tail=nullptr;
    length=0;
}
void List::appendNode(int data){
	Node* cur=this->tail;
	Node* newNode=new Node(data,this->tail->next);
	cur->next=newNode;
	this->length++;
	this->tail=newNode;
}
void List::joinNode(int num,int data){
	Node* head=this->tail->next;
	Node* cur=head;
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
	Node* newNode=new Node(data,cur->next);
	cur->next=newNode;
	this->length++;
}
void List::deleteNode(int num){
	Node* head=this->tail->next;
	Node* cur=head;
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
	Node* p=cur->next;
	cur->next=p->next;
	delete p;
	this->length--;
}
void List::changeNode(int num,int data){
	Node* head=this->tail->next;
	Node* cur=head;
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
	Node* head=this->tail->next;
	Node* cur=head;
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
	Node* head=this->tail->next;
	Node* cur=head;
	while(cur->next!=head){
		cur=cur->next;
		cout<<cur->data<<endl;
	}
	cout<<"end"<<endl;
}
int List::listLength(){
	return this->length;
}
int List::findData(int dat){
	Node* head=this->tail->next;
	int cnt=0;
	Node* cur=head;
	while(cur->next!=head){
		cur=cur->next;
		cnt++;
		if(cur->data==dat)return cnt;
	}
	return -1;
}
void List::connectList(List* list2){
	if(list2->length>0){
		Node* tail1=this->tail;
		Node* tail2=list2->tail;
		Node* cur=tail1->next;
		tail1->next=tail2->next->next;
		Node* p=tail2->next;
		tail2->next=cur;
		delete p;
		this->tail=tail2;
		this->length+=list2->length;
		list2->tail=new Node(0,nullptr);
		list2->tail->next=list2->tail;
		list2->length=0;
	}
}
int main(){
	List list1;
	List list2;
	list1.appendNode(1);
	list1.appendNode(2);
	list1.appendNode(3);
	list1.appendNode(4);
	list2.appendNode(4);
	list2.appendNode(5);
	list2.appendNode(6);
	list1.connectList(&list2);
	list1.printEveryNode();
	list2.printEveryNode();
	cout<<list1.length<<endl;
}

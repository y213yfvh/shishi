#include<iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* createList(){
	Node* newNode=new Node{0,nullptr};
	newNode->next=newNode;
	return newNode;
}
Node* appendNodeByHead(Node* head,int data){
	Node* cur=head;
	while(cur->next!=head){
		cur=cur->next;
	}
	Node* newNode=new Node{data,head};
	cur->next=newNode;
	return newNode;
}
Node* appendNodeByTail(Node* tail,int data){
	Node* cur=tail;
	Node* newNode=new Node{data,cur->next};
	cur->next=newNode;
	return newNode;
}
Node* joinNode(Node* head,int num,int data){
	Node* cur=head;
	num--;
	while(num--){
		if(cur->next!=head)cur=cur->next;
		else {
			cout<<"error:to big!"<<endl;
			return nullptr;
		}
	}
	if(cur->next==head){
		cout<<"error:to big!"<<endl;
		return nullptr;
	}
	Node* newNode=new Node{data,cur->next};
	cur->next=newNode;
	return newNode;
}
Node* deleteNode(Node* head,int num){
	Node* cur=head;
	num--;
	while(num--){
		if(cur->next!=head)cur=cur->next;
		else {
			cout<<"error:to big!"<<endl;
			return nullptr;
		}
	}
	Node* p=cur->next;
	cur->next=p->next;
	delete p;
	return cur;
}
Node* changeNode(Node* head,int num,int data){
	Node* cur=head;
	while(num--){
		if(cur->next!=head)cur=cur->next;
		else {
			cout<<"error:to big!"<<endl;
			return nullptr;
		}
	}
	cur->data=data;
	return cur;
}
void printNode(Node* head,int num){
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
void printData(Node* cur){
	cout<<cur->data<<endl;
}
void printEveryNode(Node* head){
	Node* cur=head;
	while(cur->next!=head){
		cur=cur->next;
		cout<<cur->data<<endl;
	}
	cout<<"end"<<endl;
}
int listLength(Node* head){
	int cnt=0;
	Node* cur=head;
	while(cur->next!=head){
		cur=cur->next;
		cnt++;
	}
	return cnt;
}
int findData(Node* head,int dat){
	int cnt=0;
	Node* cur=head;
	while(cur->next!=head){
		cur=cur->next;
		cnt++;
		if(cur->data==dat)return cnt;
	}
	return -1;
}
Node* connectList(Node* tail1,Node*tail2){
	Node* cur=tail1->next;
	tail1->next=tail2->next->next;
	Node* p=tail2->next;
	tail2->next=cur;
	delete p;
	return tail2;
}
int main(){
	Node* tail1=nullptr;
	Node* tail2=nullptr;
	tail2=createList();
	tail2=appendNodeByTail(tail2,7);
	tail2=appendNodeByTail(tail2,8);
	tail2=appendNodeByTail(tail2,9);
	tail2=appendNodeByTail(tail2,10);
	tail2=appendNodeByTail(tail2,11);
	tail2=appendNodeByTail(tail2,12);
	changeNode(tail2->next,6,13);
	printEveryNode(tail2->next);
}

#include<iostream>
using namespace std;
template<typename T>
class Node{
	public:
		T data;
		Node* next;
		Node(T,Node*);
		Node(T);
};
template<typename T>
Node<T>::Node(T data,Node* next){
	this->data=data;
	this->next=next;
}
template<typename T>
Node<T>::Node(T data){
	this->data=data;
	this->next=nullptr;
}
template<typename T>
class List{
	public:
		Node<T>* head;
		Node<T>* tail;
		int len;
		List();
		~List();
		List& operator=(const List& other);
		List(const List& other);
		void appendNode(T);
		void deleteLastNode();
		void deleteNode(int);
		void addNode(int,T);
		int checkNode(T);
		void changeNode(int,T);
		void printEveryNode();
};
template<typename T>
List<T>::~List(){
    Node<T>* cur=head;
    while(cur!=nullptr){
        Node<T>* next=cur->next;
        delete cur;
        cur=next;
    }
}
template<typename T>
List<T>::List(){
	this->head=new Node<T>(T());
	this->len=0;
	this->tail=head;
}
template<typename T>
List<T>::List(const List& other) {
    head = new Node<T>(T());
    tail = head;
    len = 0;
    Node<T>* cur = other.head->next;
    while (cur != nullptr) {
        appendNode(cur->data);
        cur = cur->next;
    }
}
template<typename T>
void List<T>::appendNode(T data){
	this->tail->next=new Node<T>(data);
	this->len++;
	this->tail=this->tail->next;
}
template<typename T>
void List<T>::deleteLastNode(){
	if(this->len){
		Node<T>* cur=this->head;
		int n=this->len-1;
		while(n--){
			cur=cur->next;
		}
		Node<T>* noTail=this->tail;
		cur->next=nullptr;
		this->tail=cur;
		delete noTail;
		this->len--;
	}else {
		cout<<"None"<<endl;
	}
}
template<typename T>
void List<T>::printEveryNode(){
	Node<T>* cur=this->head;
	while(cur->next!=nullptr){
		cur=cur->next;
		cout<<cur->data<<endl;
	}
}
template<typename T>
void List<T>::deleteNode(int n){
	Node<T>* cur=this->head;
	if(n<0){
		cout<<"deleteNode() error:-"<<endl;
		return;
	}else if(n>=len){
		cout<<"deleteNode() error:too big"<<endl;
		return;
	}else if(n==len-1){
		this->deleteLastNode();
	}else{
		while(n--){
			cur=cur->next;
		}
		Node<T>* p=cur->next;
		cur->next=p->next;
		delete p;
		this->len--;
	}
}
template<typename T>
void List<T>::addNode(int n,T data){
	Node<T>* cur=this->head;
	if(n<0){
		cout<<"addNode() error:-"<<endl;
		return;
	}else if(n>len){
		cout<<"addNode() error:too big"<<endl;
		return;
	}else if(n==len){
		this->appendNode(data);
	}else{
		while(n--){
			cur=cur->next;
		}
		Node<T>* p=cur->next;
		cur->next=new Node<T>(data,p);
		this->len++;
	}
}
template<typename T>
int List<T>::checkNode(T data){
	Node<T>* cur=this->head;
	int n=0;
	while(cur->next!=nullptr){
		cur=cur->next;
		if(cur->data==data){
			return n;
		}
		n++;
	}
	return -1;
}
template<typename T>
void List<T>::changeNode(int n,T data){
	Node<T>* cur=this->head;
	if(n<0){
		cout<<"changeNode() error:-"<<endl;
		return;
	}else if(n>=len){
		cout<<"changeNode() error:too big"<<endl;
		return;
	}else{
		while(n--){
			cur=cur->next;
		}
		cur->next->data=data;
	}
}
template<typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        while (head->next != nullptr) deleteNode(0);
        Node<T>* cur = other.head->next;
        while (cur != nullptr) {
            appendNode(cur->data);
            cur = cur->next;
        }
    }
    return *this;
}
int main(){
	List<string> list;
	list.appendNode("aaa");
	list.appendNode("d");
	list.appendNode("a");
	list.appendNode("a");
	list.printEveryNode();
	List<string> list2;
	list2=list;
	list.printEveryNode();
}

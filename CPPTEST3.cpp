#include<iostream>
#include<string>
using namespace std;
class human{
	public:
		int height;
		int weight;
		string name;
		void eat(){
			cout<<"eat"<<endl;
		}
		void setheight(int h){
			this->height=h;
		}
		void setweight(int w){
			this->weight=w;
		}
		void print(){
			cout<<this->height<<" "<<this->weight<<" "<<this->name<<endl;
		}
		human();
		~human();
};
human::human(void){
	cout<<"A human bas been burned!"<<endl;
}
human::~human(void){
	cout<<"A human has been deaded!"<<endl;
}
class cxk:public human{
	public:
		cxk();
		~cxk();
};
cxk::cxk(void){
	cout<<"hello everyone!I love singing,dancing,rap,and basketball!"<<endl;
}
cxk::~cxk(void){
	cout<<"(kun kiss)"<<endl;
}
int main(){
	human man;
	man.setweight(200);
	man.setheight(160);
	man.name="LiangZi";
	man.print();
	cxk kun;
	kun.setheight(178);
	kun.setweight(70);
	kun.name="CaiXukun";
	kun.print();
}

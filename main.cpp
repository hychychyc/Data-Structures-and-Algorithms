#include<iostream>
#include"chain.h"
//#include"extendedChain.h"
//#include"circularListWithHeader.h"
//#include"doublylinkedlist.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
template<class T>
void chain<T>::reverse(){
    chainNode<T> *tmp=this->firstNode,*pre=NULL,*tmp2=tmp->next;
    for(int i=0;tmp2!=NULL&&tmp!=NULL;i++){
    	if(i&1) pre=tmp->next,tmp->next=tmp2,tmp2=pre;
        else pre=tmp2->next,tmp2->next=tmp,tmp=pre;
    }
    this->firstNode->next=NULL;
    this->firstNode=tmp==NULL?tmp2:tmp;
}
template<class T>
void chain<T>::insertSort(){
	
    chainNode<T> *tmp=firstNode->next,*t=tmp;firstNode->next=NULL;
    
    for(;tmp!=NULL;tmp=t){chainNode<T> * i=firstNode;t=tmp->next;
    	if(tmp->element<firstNode->element) tmp->next=firstNode,firstNode=tmp;
        else {
        	for(;i->next&&i->next!=tmp&&i->next->element<tmp->element;i=i->next); //
        if(tmp!=i->next)tmp->next=i->next,i->next=tmp;	
		else tmp->next=NULL;
		}
       //cout<<*this<<endl;
    }
    //tmp=firstNode;
    //for(int i=0;i<listSize-1;i++,tmp=tmp->next);
   // tmp->next=NULL;
}
int main(int argc, char** argv) {
	chain<int>b;
	b.insert(0,1);cout<<b<<endl;
	b.insert(1,2);cout<<b<<endl;
	b.insert(2,3);
	//b.push_back(4);//cout<<b;
	b.insert(1,4);
	b.insert(1,5);
	b.insert(0,6);
	b.insert(1,7);
	b.insert(0,8);
	//b.erase(2);
	cout<<b;
	b.insertSort();
	cout<<b;
	//cout<<b.get(2);
	return 0;
}

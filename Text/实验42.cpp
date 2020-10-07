#include<iostream>
using namespace std;
template<class T>
struct chainNode{
    T element;
    chainNode<T>* next;
    chainNode() {}
    chainNode(const T& element){this->element=element;}
    chainNode(const T& element,chainNode<T>* next){this->next=next;this->element=element;}
};

template<class T>
class chain{
	public:
		chain(int initialCapacity=10);
        chain(const chain<T>&);
		~chain();
        int size(){return listSize;}
        T &get(int theIndex);
        int IndexOf(const T& theElement);
        void erase(int theIndex);
        
        void insert(int theIndex,const T& theElement);
        void insertSort();
        void output(ostream& out);
        void reverse();
        class iterator {
            public:
                iterator(chainNode<T>* theNode=NULL){node=theNode;}
                T &operator *() const{return node->element;}
                T *operator->() const{return &node->element;}
                iterator & operator++(){node=node->next;return *this;}
                iterator operator++(int){iterator old=*this;node=node->next;return old;}
                bool operator!=(const iterator right)const{return node!=right.node;}
                bool operator==(const iterator right)const{return node==right.node;}
            protected:
                chainNode<T> *node;
        };
		iterator begin(){return iterator(firstNode);}
        iterator end(){return iterator(NULL);}
    protected:
        //void checkIndex(int theIndex);
        chainNode<T>* firstNode;
        int listSize;
};
template<class T>
chain<T>::chain(int initialCapacity){
    if(initialCapacity<1){
        //ostringstream s;
        //s<<"error!"<<endl;
    }
    firstNode=NULL;
    listSize=0;
}
template<class T>
chain<T>::chain(const chain<T>& theList){
    listSize=theList.listSize;
    if(listSize==0){firstNode=NULL;return ;}
    chainNode<T>* sourseNode=theList.firstNode;
    firstNode=new chainNode<T>(sourseNode->element);
    sourseNode=sourseNode->next;
    chainNode<T>*targetNode=firstNode;
    while(sourseNode!=NULL){
        targetNode->next=new chainNode<T>(sourseNode->element);
        targetNode=targetNode->next;
        sourseNode=sourseNode->next;
    } 
    targetNode->next=NULL;
}
template<class T>
chain<T>::~chain(){
    while(firstNode!=NULL){
        chainNode<T>* nextNode=firstNode->next;
        delete firstNode;
        firstNode=nextNode;
    }
}
template<class T> 
T& chain<T>::get(int theIndex){
    //checkIndex(theIndex);
    chainNode<T>*currentNode=firstNode;
    for(int i=0;i<theIndex;i++)
    currentNode=currentNode->next;
    return currentNode->element;
}
template<class T>
void chain<T>::insert(int theIndex,const T& theElement){
    if(theIndex==0) firstNode=new chainNode<T>(theElement,firstNode);
    else {
        chainNode<T> *p=firstNode;
        for(int i=0;i<theIndex-1;i++)
        p=p->next;
        p->next=new chainNode<T>(theElement,p->next);
    }
    listSize++;
}
template<class T>
int chain<T>::IndexOf(const T& theElement){
   chainNode<T>*currentNode=firstNode;
   int index=0;
   while(currentNode!=NULL&&currentNode->element!=theElement){
       currentNode=currentNode->next;index++;
   }if(currentNode==NULL) return -1;
   return index;
}
template<class T>
void chain<T>::erase(int theIndex){
    //checkIndex(theIndex);
    chainNode<T>* deleteNode;
    if(theIndex==0){
        deleteNode=firstNode;
        firstNode=firstNode->next;
    }else{
        chainNode<T>* p=firstNode;
        for(int i=0;i<theIndex-1;i++) p=p->next;
        deleteNode=p->next;
        p->next=p->next->next;
    }listSize--;
    delete deleteNode;
}
template<class T>
void chain<T>::output(ostream& out){
    for(chainNode<T>* i=firstNode;i!=NULL;i=i->next) 
    out<<i->element<<"  ";
    
}
template<class T>
ostream& operator <<(ostream& out, chain<T> &x){
    x.output(out);return out;
}
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
	if(listSize==0) return ;
    chainNode<T> *tmp=firstNode->next,*t=tmp;firstNode->next=NULL;
    
    for(;tmp!=NULL;tmp=t){chainNode<T> * i=firstNode;t=tmp->next;
    	if(tmp->element<firstNode->element) tmp->next=firstNode,firstNode=tmp;
        else {
        	for(;i->next&&i->next!=tmp&&i->next->element<tmp->element;i=i->next); 
        if(tmp!=i->next)tmp->next=i->next,i->next=tmp;	
		else tmp->next=NULL;
		}

    }
    
}

int main(){int n,m;
    
    chain<long long> s,s2,s3;
    cin>>n>>m;long long ans1=0,ans2=0,ans3=0;
    for(int i=1;i<=n;i++){long long x;cin>>x;
        s.insert(i-1,x);
    }
   	for(int i=1;i<=m;i++){long long x;cin>>x;
   		s2.insert(i-1,x);
	}
	s.insertSort();	
	s2.insertSort();
	
	chain<long long>::iterator it=s.begin(),it2=s2.begin();
	for(int i=1;i<=n;i++,it++)ans1+=(i-1)^(*it);
   	for(int i=1;i<=m;i++,it2++)ans2+=(i-1)^(*it2);
	   
    it=s.begin(),it2=s2.begin();
    for(int i=0;i<s.size();i++,it++)
    s3.insert(0,*it);
	for(int i=0;i<s2.size();i++,it2++)
    s3.insert(0,*it2);
   	s3.insertSort();cout<<s3;
   	chain<long long>::iterator it3=s3.begin();
   	for(int i=0;i<s3.size();i++,it3++) ans3+=i^(*it3);
   	
    cout<<ans1<<endl<<ans2<<endl<<ans3<<endl;
        
    //
    
}

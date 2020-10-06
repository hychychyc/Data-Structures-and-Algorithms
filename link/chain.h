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

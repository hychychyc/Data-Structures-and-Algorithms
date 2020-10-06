
template<class T>
class circularListWithHeader {
    public :
        circularListWithHeader(){
            this->firstNode=new chainNode<T>();
            this->firstNode->next=this->firstNode;this->listSize=0;
         };  
        circularListWithHeader(const circularListWithHeader<T>&);
		~circularListWithHeader();
        int size(){return listSize;}
        T &get(int theIndex);
        int IndexOf(const T& theElement);
        void erase(int theIndex);
        void insert(int theIndex,const T& theElement);
        void output(ostream& out);
        
    protected:
        //void checkIndex(int theIndex);
        chainNode<T>* firstNode;
        int listSize;
        
};

template<class T>
circularListWithHeader<T>::circularListWithHeader(const circularListWithHeader<T>& theList){
    listSize=theList.listSize;
    firstNode=new chainNode<T>();
    if(listSize==0){this->fisrtNode->next=firstNode;return ;}
    chainNode<T>* sourseNode=theList.firstNode->next;
    firstNode->next=new chainNode<T>(sourseNode->element);
    sourseNode=sourseNode->next;
    chainNode<T>*targetNode=firstNode->next;
    while(sourseNode!=theList->firstNode){
        targetNode->next=new chainNode<T>(sourseNode->element);
        targetNode=targetNode->next;
        sourseNode=sourseNode->next;
    } 
    targetNode->next=firstNode;
}
template<class T>
circularListWithHeader<T>::~circularListWithHeader(){
    while(firstNode->next!=firstNode){
        chainNode<T>* nextNode=firstNode->next->next;
        delete firstNode->next;
        firstNode=nextNode;
    }
    delete firstNode;
}
template<class T> 
T& circularListWithHeader<T>::get(int theIndex){
    //checkIndex(theIndex);
    chainNode<T>*currentNode=firstNode->next;
    for(int i=0;i<theIndex;i++)
    currentNode=currentNode->next;
    return currentNode->element;
}
template<class T>
void circularListWithHeader<T>::insert(int theIndex,const T& theElement){
    if(theIndex==0) firstNode->next=new chainNode<T>(theElement,firstNode);
    else {
        chainNode<T> *p=firstNode->next;
        for(int i=0;i<theIndex-1;i++)
        p=p->next;
        p->next=new chainNode<T>(theElement,p->next);
    }
    listSize++;
    //cout<<*this;
}
template<class T>
void circularListWithHeader<T>::erase(int theIndex){
    //checkIndex(theIndex);
    chainNode<T>* deleteNode;
    if(theIndex==0){
        deleteNode=firstNode->next;
        firstNode->next=firstNode->next->next;
    }else{
        chainNode<T>* p=firstNode->next;
        for(int i=0;i<theIndex-1;i++) p=p->next;
        deleteNode=p->next;
        p->next=p->next->next;
    }listSize--;
    delete deleteNode;
}
template<class T>
void circularListWithHeader<T>::output(ostream& out){
    for(chainNode<T>* i=firstNode->next;i!=firstNode;i=i->next) 
    out<<i->element<<"  ";
    //out<<"end";
}
template<class T>
int circularListWithHeader<T>::IndexOf(const T& theElement){
    this->firstNode->element=theElement;
    chainNode<T>*currentNode=this->firstNode->next;
    int index=0;
    while(currentNode->element!=theElement){
       currentNode=currentNode->next;index++;
    }if(currentNode==this->firstNode) return -1;
    return index;
}
template<class T>
ostream& operator <<(ostream& out, circularListWithHeader<T> &x){
    x.output(out);return out;
}

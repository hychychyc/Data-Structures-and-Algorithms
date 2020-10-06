
template<class T>
class extendedChain : public chain<T>{
    public :
        void erase(int theIndex);
        void insert(int theIndex,const T& theElement);
        void clear();
        void push_back(const T &theElement);
        protected:
        chainNode<T>* lastNode;
};
template<class T>
void extendedChain<T>::clear(){
    while(this->firstNode!=NULL){
        chainNode<T> *nextNode=this->firstNode->next;
        delete this->firstNode;
        this->firstNode=nextNode;
    }
    this->listSize=0;
}
template<class T>
void extendedChain<T>::push_back(const T& theElement){
    chainNode<T>* newNode=new chainNode<T>(theElement,NULL);
    if(this->firstNode==NULL) this->firstNode=lastNode=newNode;
    else{
        lastNode->next=newNode;
        lastNode=newNode;
    }this->listSize++;
}
template<class T>
void extendedChain<T>::insert(int theIndex,const T& theElement){
    
    if(theIndex==0) {
        this->firstNode=new chainNode<T>(theElement,this->firstNode);
        if(this->listSize==theIndex){
            lastNode=this->firstNode;
        }
    }
    else {
        chainNode<T> *p=this->firstNode;
        for(int i=0;i<theIndex-1;i++)
        p=p->next;
        p->next=new chainNode<T>(theElement,p->next);
        if(this->listSize==theIndex){
            lastNode=p->next;
        }
    }
    
    this->listSize++;
}
template<class T>
void extendedChain<T>::erase(int theIndex){
    //this->checkIndex(theIndex);
    chainNode<T>* deleteNode;
    if(theIndex==0){
        deleteNode=this->firstNode;
        this->firstNode=this->firstNode->next;
    }else{
        chainNode<T>* p=this->firstNode;
        for(int i=0;i<theIndex-1;i++) p=p->next;
        deleteNode=p->next;
        p->next=p->next->next;
        if(this->listSize==theIndex){
            lastNode=p;
        }
    }this->listSize--;
    delete deleteNode;
}

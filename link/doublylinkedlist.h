using namespace std;
template<class T>
struct chainNode{
    T element;
    chainNode<T>* next,* previous;
    chainNode() {}
    chainNode(const T& element){this->element=element;}
    chainNode(const T& element,chainNode<T>* next,chainNode<T>* previous){this->next=next;this->previous=previous,this->element=element;}
};

template<class T>
class doublyLinkedList{
    public:
		doublyLinkedList(int initialCapacity=10);
        doublyLinkedList(const doublyLinkedList<T>&);
		~doublyLinkedList();
        int size(){return listSize;}
        T &get(int theIndex);
        int IndexOf(const T& theElement);
        void erase(int theIndex);
        void insert(int theIndex,const T& theElement);
        void output(ostream& out);
        
    protected:
        //void checkIndex(int theIndex);
        chainNode<T>* firstNode,*lastNode;
        int listSize;
};
template<class T>
T &doublyLinkedList<T>::get(int theIndex){
    if(theIndex<this->listSize/2){
        chainNode <T>*p=this->firstNode;
        for(int i=0;i<theIndex;i++)p=p->next;
        return p->element; 
    }else{
        chainNode <T>*p=this->lastNode;
        for(int i=0;i<this->listSize-theIndex;i++)p=p->previous;
        return p->element; 
    }
    
}
template<class T>
doublyLinkedList<T>::doublyLinkedList(int initialCapacity){
    if(initialCapacity<1){
        //ostringstream s;
        //s<<"error!"<<endl;
    }
    firstNode=lastNode=NULL;
    listSize=0;
}
template<class T>
doublyLinkedList<T>::doublyLinkedList(const doublyLinkedList<T>& theList){
    listSize=theList.listSize;
    if(listSize==0){firstNode=lastNode=NULL;return ;}
    chainNode<T>* sourseNode=theList.firstNode;
    firstNode=new chainNode<T>(sourseNode->element);
    firstNode->previous=NULL;
    sourseNode=sourseNode->next;
    chainNode<T>*targetNode=firstNode;
    while(sourseNode!=NULL){
        targetNode->next=new chainNode<T>(sourseNode->element);
        targetNode->previous=targetNode;
        targetNode=targetNode->next;
        sourseNode=sourseNode->next;
    } 
    targetNode->next=NULL;lastNode=targetNode;
}
template<class T>
doublyLinkedList<T>::~doublyLinkedList(){
    while(firstNode!=NULL){
        chainNode<T>* nextNode=firstNode->next;
        delete firstNode;
        firstNode=nextNode;
    }
}
template<class T>
void doublyLinkedList<T>::insert(int theIndex,const T& theElement){
	if(theIndex<=this->listSize/2){
	    if(theIndex==0) {
	    	firstNode=new chainNode<T>(theElement,firstNode,NULL);
	    	if(firstNode->next!=NULL)firstNode->next->previous=firstNode;
			else lastNode=firstNode;
		}
	    else {
	        chainNode<T> *p=firstNode;
	        for(int i=0;i<theIndex-1;i++)
	        p=p->next;
	        p->next=new chainNode<T>(theElement,p->next,p);
	    	if(p->next->next!=NULL)
	        p->next->next->previous=p->next;
	    }
	    listSize++;
	}else{
		if(theIndex==listSize) {
			lastNode=new chainNode<T>(theElement,NULL,lastNode);
			if(lastNode->previous!=NULL)lastNode->previous->next=lastNode;
			else firstNode=lastNode;
		}
	    else {
	        chainNode<T> *p=lastNode;
	        for(int i=0;i<listSize-theIndex-1;i++)
	        p=p->previous;
	        p->previous=new chainNode<T>(theElement,p,p->previous);
	        if(p->previous->previous!=NULL)
	        p->previous->previous->next=p->previous;
	    }
	    listSize++;
	}
}
template<class T>
int doublyLinkedList<T>::IndexOf(const T& theElement){
   chainNode<T>*currentNode=firstNode;
   int index=0;
   while(currentNode!=NULL&&currentNode->element!=theElement){
       currentNode=currentNode->next;index++;
   }if(currentNode==NULL) return -1;
   return index;
}
template<class T>
void doublyLinkedList<T>::erase(int theIndex){
    //checkIndex(theIndex);
    if(theIndex<this->listSize/2){
	    chainNode<T>* deleteNode;
	    if(theIndex==0){
	        deleteNode=firstNode;
	        firstNode=firstNode->next;
	        firstNode->previous=NULL;
	    }
		else{
	        chainNode<T>* p=firstNode;
	        for(int i=0;i<theIndex-1;i++) p=p->next;
	        deleteNode=p->next;
	        p->next=p->next->next;
	    }listSize--;
	    delete deleteNode;
	}else{
		chainNode<T>* deleteNode;
	    if(theIndex==listSize){
	        deleteNode=lastNode;
	        lastNode=lastNode->previous;
	        lastNode->next=NULL;
	    }else{
	        chainNode<T>* p=lastNode;
	        for(int i=0;i<listSize-theIndex-1;i++)p=p->previous;
	        deleteNode=p->previous;
	        p->previous=p->previous->previous;
	    }listSize--;
	    delete deleteNode;
	}
}
template<class T>
void doublyLinkedList<T>::output(ostream& out){
    for(chainNode<T>* i=firstNode;i!=NULL;i=i->next) 
    out<<i->element<<"  ";
    
}
template<class T>
ostream& operator <<(ostream& out, doublyLinkedList<T> &x){
    x.output(out);return out;
}

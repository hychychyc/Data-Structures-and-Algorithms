#include<iostream>
using namespace std;

template<typename T>
struct matrixTerm {//三元组 
   int row,col;T value;
   matrixTerm(int trow,int tcol,T tvalue){row=trow;col=tcol;value=tvalue;}
   matrixTerm (const matrixTerm<T> &a){row=a.row;col=a.col;value=a.value;}
   matrixTerm(){};
   matrixTerm& operator=(const matrixTerm <T>&a) {//重载 
  	row=a.row;col=a.col;value=a.value;
  	return *this;
	}
   //operator int() const {return value;}
};

template<typename T>//变长度 
void changeLength1D(T*& a, int oldLength, int newLength){
   T* temp = new T[newLength];              
   int number = min(oldLength, newLength);  
   copy(a, a + number, temp);
   delete [] a;                            
   a = temp;
}

template<typename T>
class arrayList {//线性表类 
   public:
      arrayList(int initialCapacity = 10);
      arrayList(const arrayList<T>&);
      ~arrayList() {delete [] element;}

      bool empty() const {return listSize == 0;}
      int size() const {return listSize;}
      T& get(int theIndex) const;
      int indexOf(const T& theElement) const;
      void erase(int theIndex);
      void insert(int theIndex, const T& theElement);
      void output(ostream& out) const;

      
      int capacity() const {return arrayLength;}
      void reSet(int);
      void set(int, const T&);
      void clear() {listSize = 0;}
      
     
      class iterator;
      iterator begin() {return iterator(element);}
      iterator end() {return iterator(element + listSize);}

    
      class iterator {
         public:
            iterator(T* thePosition = 0) {position = thePosition;}
            T& operator*() const {return *position;}
            T* operator->() const {return &*position;}
            iterator& operator++()   {++position; return *this;}
            iterator operator++(int) {iterator old = *this;
            	++position;
            	 return old;
            }

           
            iterator& operator--()  {--position; return *this;}
            iterator operator--(int) {iterator old = *this;
            	--position;
            	return old;
            }
            bool operator!=(const iterator right) const
                  {return position != right.position;}
            bool operator==(const iterator right) const
                  {return position == right.position;}
         protected:
            T* position;
      };  

	arrayList& operator=(const arrayList<T> &theList) {
  		
		
		arrayLength = theList.arrayLength;
   		listSize = theList.listSize;
		if(element==theList.element)return *this;
		delete []element;
   		element = new T[arrayLength];
   		copy(theList.element, theList.element + listSize, element);
  		return *this;
  	}
  	
   protected:  
      void checkIndex(int theIndex) const; 
      T* element;           
      int arrayLength;       
      int listSize;         
};

template<typename T>
arrayList<T>::arrayList(int initialCapacity){
   arrayLength = initialCapacity;
   element = new T[arrayLength];
   listSize = 0;
}
template<class T>
void arrayList<T>::erase(int theIndex){
  
   copy(element + theIndex + 1, element + listSize,element + theIndex);
	element[--listSize].~T(); // invoke destructor
}
template<typename T>
arrayList<T>::arrayList(const arrayList<T>& theList){
   arrayLength = theList.arrayLength;
   listSize = theList.listSize;
   element = new T[arrayLength];
   copy(theList.element, theList.element + listSize, element);
}




template<typename T>
void arrayList<T>::insert(int theIndex, const T& theElement){
   
   if (listSize == arrayLength){
         changeLength1D(element, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }
   copy_backward(element + theIndex, element + listSize,element + listSize + 1);
   element[theIndex] = theElement;
   listSize++;
}

template<class T>
void arrayList<T>::set(int theIndex, const T& newValue){
   
   element[theIndex] = newValue;
}

template<class T>
void arrayList<T>::reSet(int theSize){
   if (theSize > arrayLength){
      delete element;
      element = new T[theSize];
      arrayLength = listSize;
   }
   listSize = theSize;
}
template<class T>
T& arrayList<T>::get(int theIndex) const{
   return element[theIndex];
}

template<typename T>
class sparseMatrix{
    

   public:
   	sparseMatrix(const sparseMatrix<T>&a){
   		rows=a.rows;cols=a.cols;
   		arrayList<matrixTerm<T> > w(a.terms);
   		terms=w;
	   } ;
	   sparseMatrix(){
   	
	   } ;
      void transpose(sparseMatrix<T> &b);
      void replace(int trows,int tcols){//替换 
          terms.clear();//清除 
          rows=trows;cols=tcols;int a,b;T c;
          for(int i=0;i<rows;i++)
          for(int j=0;j<cols;j++){cin>>c;
              if(c!=0){
              	matrixTerm <T>tmp(i,j,c);
				  terms.insert(terms.size(),tmp);
			  }
          }
          
      }
      void replace2(int trows,int tcols){
          terms.clear();int t;cin>>t;
          rows=trows;cols=tcols;int a,b;T c;
          while(t--){cin>>a>>b>>c;a--;b--;
              if(c!=0){
              	matrixTerm <T>tmp(a,b,c);
				  terms.insert(terms.size(),tmp);
			  }
          }
          
      }
	  //ostream& operator<<(ostream& out, sparseMatrix<T>& x);
	  void output(ostream& out);
      int getrows(){return rows;}
      int getcols(){return cols;}
      sparseMatrix<T> operator *( sparseMatrix<T> &b);
      void add(sparseMatrix<T> &b, sparseMatrix<T> &c);
      void muilt(sparseMatrix<T> &b, sparseMatrix<T> &c);
      void insertsort();
      sparseMatrix& operator=(const sparseMatrix<T> &a) {
  		rows=a.rows;cols=a.cols;
   		
   		terms=a.terms;
  		return *this;
  		}
   private:
      int rows,cols;   
      arrayList<matrixTerm<T> > terms;
};
template<typename T>
void sparseMatrix<T>::output(ostream& out){
	out<<rows<<' '<<cols<< endl;
   	typename arrayList<matrixTerm<T> >::iterator it = terms.begin();
    for(int i=0;i<rows;i++,cout<<endl)
    for(int j=0;j<cols;j++){
        if(it!=terms.end()&&(*it).row==i&&(*it).col==j){
         cout<<(*it).value<<' ',   it++;
        }else  cout<<0<<' ';
    }
    //cout<<endl;
  
   }
template <typename T>
ostream& operator<<(ostream& out, sparseMatrix<T>& x){
   x.output(out);
   return out;
}

template<typename T>
void sparseMatrix<T>::muilt(sparseMatrix<T> &b, sparseMatrix<T> &c){//乘法 
   c.rows = rows;
   c.cols = b.cols;
   c.terms.clear();
   int cSize = 0;
  T temp[b.cols];//计数器 
  int* rowSize = new int[b.rows];
   int* rowNext = new int[b.rows+1];//b累加行 
 
   for (int i=0;i<b.rows;i++) 
      rowSize[i] = 0;  
   for (typename arrayList<matrixTerm<T> >::iterator i = b.terms.begin();i != b.terms.end(); i++)
      rowSize[(*i).row]++; 
   rowNext[0] = 0;
   for (int i = 1; i <=b.rows; i++)
      rowNext[i] = rowNext[i - 1] + rowSize[i - 1];//累加  
  
   typename arrayList<matrixTerm<T> >::iterator it=terms.begin();
   for(int i=0;i<rows;i++){
        for(int j=0;j<b.cols;j++)temp[j]=0;
      	while(it!=terms.end()&&i==(*it).row){//矩阵中有i 
        	int t=(*it).col;//矩阵col 
        	for(int k=rowNext[t];k<rowNext[t+1];k++)//枚举第二个矩阵的行 
        	temp[b.terms.get(k).col]+=(*it).value*b.terms.get(k).value;//计算 
       		it++;
     	}
      for(int j=0;j<b.cols;j++)
        if(temp[j]!=0){
            matrixTerm<T> p;
			p.row=i,p.col=j,p.value=temp[j];c.terms.insert(cSize++,p);//插入 
        }
      
   }
}



template<typename T>
void sparseMatrix<T>::add(sparseMatrix<T> &b, sparseMatrix<T> &c){
   c.rows = rows;
   c.cols = cols;
   c.terms.clear();
   int cSize = 0;
   
   typename arrayList<matrixTerm<T> >::iterator it = terms.begin();
   typename arrayList<matrixTerm<T> >::iterator ib = b.terms.begin();
   typename arrayList<matrixTerm<T> >::iterator itEnd = terms.end();
   typename arrayList<matrixTerm<T> >::iterator ibEnd = b.terms.end();//迭代器 
   while (it != itEnd && ib != ibEnd){
     int tIndex = (*it).row * cols + (*it).col;
     int bIndex = (*ib).row * cols + (*ib).col;//算下标 

     if (tIndex < bIndex){
   	 	c.terms.insert(cSize++, *it);//插小的 
         it++;
     }
     else {if (tIndex == bIndex){//相等相加 
              if ((*it).value + (*ib).value != 0){
                 matrixTerm <T>mTerm;
                 mTerm.row = (*it).row;
                 mTerm.col = (*it).col;
                 mTerm.value = (*it).value + (*ib).value;
                 c.terms.insert(cSize++, mTerm);
              }
              it++; 
              ib++;
           }
           else{
              c.terms.insert(cSize++, *ib);//插小的 
              ib++;
           }
          }
     }
   for (; it != itEnd; it++)
      c.terms.insert(cSize++, *it);
   for (; ib != ibEnd; ib++)
      c.terms.insert(cSize++, *ib);//插入剩下的 
}
template<typename T>
void sparseMatrix<T>::transpose(sparseMatrix<T> &b){
   b.cols = rows;
   b.rows = cols;
   //b.terms.reSet(terms.size());
	
   int* colSize = new int[cols];
   int* rowNext = new int[cols];//数组 
 
   for (int i = 0; i < cols; i++) 
      colSize[i] = 0;  
   for (typename arrayList<matrixTerm<T> >::iterator i = terms.begin();
        i != terms.end(); i++)
      colSize[(*i).col]++;  
   
   rowNext[0] = 0;
   for (int i = 1; i <cols; i++)
      rowNext[i] = rowNext[i - 1] + colSize[i - 1];  //前缀和 ，变成列主次 

   matrixTerm<T> mTerm;
   for (typename arrayList<matrixTerm<T> >::iterator i = terms.begin();
        i != terms.end(); i++){
      int j = rowNext[(*i).col]++; 
      mTerm.row = (*i).col;
      mTerm.col = (*i).row;//交换行和列 
      mTerm.value = (*i).value;
      b.terms.set(j, mTerm);//插入 
   }
}
sparseMatrix<int> Q,P;
int main(){
	//freopen("a.out","w",stdout);
    int w;cin>>w;
    while(w--){
        int opt,rows,cols;
        cin>>opt;//cout<<"case";
        if(opt==1){cin>>rows>>cols;
            Q.replace(rows,cols);
        }
        if(opt==3){cin>>rows>>cols;
            if(rows!=Q.getrows()||cols!=Q.getcols()){
                Q.replace2(rows,cols);cout<<-1<<endl;
                continue;
            }
            
            P.replace2(rows,cols);sparseMatrix<int>W(Q);
            W.add(P,Q);
        }
        if(opt==2){
            cin>>rows>>cols;
            if(rows!=Q.getcols()){
                Q.replace2(rows,cols);cout<<-1<<endl;
                continue;
            }
            P.replace2(rows,cols);sparseMatrix<int>W(Q);
            //Q=Q*P;
			W.muilt(P,Q);
        }
        
        if(opt==5) {sparseMatrix<int>W(Q);
			W.transpose(Q);
        	//Q=W;
		}
		if(opt==4) 
		cout<<Q;
    }
    //cout<<4;
}


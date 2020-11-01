#include<iostream>
#include<iomanip>
using namespace std;
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
   T* temp = new T[newLength];             
   int number = min(oldLength, newLength); 
   copy(a, a + number, temp);
   delete [] a;                         
   a = temp;
}
template<class T>
class stack {
   public:
      virtual ~stack() {}
      virtual bool empty() const = 0;
      virtual int size() const = 0;  
      virtual T& top() = 0;
      virtual void pop() = 0;      
      virtual void push(const T& theElement) = 0;           
};
template<class T>
class arrayStack : public stack<T>
{
   public:
      arrayStack(int initialCapacity = 10);
      ~arrayStack() {delete [] stack;}
      bool empty() const {return stackTop == -1;}
      int size() const
          {return stackTop + 1;}
      T& top()
         {
            return stack[stackTop];
         }
      void pop()
           {
              stack[stackTop--].~T();  
           }
      void push(const T& theElement);
   private:
      int stackTop;       
      int arrayLength;    
      T *stack;          
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
   arrayLength = initialCapacity;
   stack = new T[arrayLength];
   stackTop = -1;
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{
   if (stackTop == arrayLength - 1)
      {
         changeLength1D(stack, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }
   stack[++stackTop] = theElement;
}

int main(){
	int n;arrayStack<char>S;arrayStack<double>s;
	cin>>n;
	while(n--){string a;
		cin>>a;int len=a.length();
		double tmp=0,now[3],f=1;int opt; 
		for(int i=len-1;i>=-1;i--){
			if(i!=-1&&a[i]!='(') S.push(a[i]);
			else{opt=0,tmp=0;f=1;
				while(!S.empty()&&')'!=S.top()){
					char t=S.top();
					if(t>='0'&&t<='9'){
						
						now[opt]=t-'0';
						//cout<<t-'0'<<endl;
						
					}else if(t=='#'){
						now[opt]=s.top();s.pop();
					}
					else if(t=='-'){
						if(opt==1){
							tmp+=f*now[0]*now[opt];
						}else if(opt==2){
							tmp+=f*now[0]/now[opt];
						}
						else tmp+=f*now[opt];
						opt=0;f=-1;
					}else if(t=='*'){
						if(opt==1){
							now[0]=now[0]*now[opt];
						}else if(opt==2) now[0]=now[0]/now[opt]; 
						opt=1;
						
					}else if(t=='/'){
						if(opt==1){
							now[0]=now[0]*now[opt];
						}else if(opt==2) now[0]=now[0]/now[opt]; 
						opt=2;
					}else{
						if(opt==1){
							tmp+=f*now[0]*now[opt];
						}else if(opt==2){
							tmp+=f*now[0]/now[opt];
						}
						else tmp+=f*now[opt];
						opt=0;f=1;
					}
					S.pop();
				}
				if(opt==1){
							tmp+=f*now[0]*now[opt];
						}else if(opt==2){
							tmp+=f*now[0]/now[opt];
						}
						else tmp+=f*now[opt];
						opt=0;f=1;
				s.push(tmp);
		
				if(!S.empty()&&S.top()==')')
				S.pop(),S.push('#');
			}
		}
		cout<<fixed<<setprecision(2)<<s.top()<<endl;	
	}
}


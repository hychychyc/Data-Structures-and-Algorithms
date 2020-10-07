#include<cstdio>
#include<string>
#include<iostream>
using namespace std;
template<class T>
void changeLength1D(T *&a,int oldLength,int newlength){//改变1维数组长度
    T *temp=new T[newlength];//新数组
    copy(a,a+min(oldLength,newlength),temp);//复制
    delete [] a;//释放老数组
    a=temp;
}
struct student{//学生类
    string name,phonenumber,classes;
    int dormitorynumber;
};
template<class T>
class arrayList{//数组类
	public:
		arrayList(int initialCapacity=10);//构造函数，复制构造函数，析构函数
        arrayList(const arrayList<T>&);
		~arrayList(){delete [] element;};
        int size(){return listSize;}
        int IndexOf(string theName);
        void erase(string theName);
        void insert(int theIndex,const T& theElement);
        void output (string theClasses) ;
        void modify(string theName,int opt,string theKey);
        void modify(string theName,int opt,int theKey);
    protected:
        T* element;//线性表元素
        int arrayLength;//容量
        int listSize;//线性表长度
};
template<class T>//构造函数
arrayList<T>::arrayList(int initialCapacity){
    arrayLength=initialCapacity;
    element=new T[arrayLength];
    listSize=0;
}
template<class T>//复制构造函数
arrayList<T>::arrayList(const arrayList<T>& theList){
    arrayLength=theList.arrayLength;
    listSize=theList.listSize;
    element=new T[arrayLength];
    copy(theList.element,theList.element+listSize,element);
}
template<class T>//插入
void arrayList<T>::insert(int theIndex,const T& theElement){
    if(arrayLength==listSize){//判断超容量
        changeLength1D(element,arrayLength,2*arrayLength);
        arrayLength*=2;
    }
    copy_backward(element+theIndex,element+listSize,element+listSize+1);//后移
    element[theIndex]=theElement;
    listSize++;
}
template<class T>//找名字对应的数组下标
int arrayList<T>::IndexOf(string theName){
    for(int i=0;i<listSize;i++)
    if(element[i].name==theName)  return i;//找到
    return -1;//未找到返回-1
}
template<class T>//删除
void arrayList<T>::erase(string theName){
    int theIndex=IndexOf(theName);//找到下标
    copy(element+theIndex+1,element+listSize,element+theIndex);//前移
    element[--listSize].~T();//删掉最后一个的空间
}
template<class T>//编辑电话和班级
void arrayList<T>::modify(string theName,int opt,string theKey){
    int theIndex=IndexOf(theName);//找到下标
    if(opt==1) element[theIndex].phonenumber=theKey;//修改
    if(opt==2) element[theIndex].classes=theKey;
    
}
template<class T>//编辑宿舍号
void arrayList<T>::modify(string theName,int opt,int theKey){
    int theIndex=IndexOf(theName);//找到下标
    if(opt==3) element[theIndex].dormitorynumber=theKey;//修改
}
template<class T>//输出异或和
void arrayList<T>::output(string theClasses){int ans=0;//答案
    for(int i=0;i<listSize;i++) if(element[i].classes==theClasses) ans^= element[i].dormitorynumber;//求值并输出
    cout<<ans<<endl;
}
arrayList<student> s;
int main(){int n;
	cin>>n;//输入
    while(n--){int opt,opt2,key;string a,b,c,d;
        student tmp;
        cin>>opt;
        if(opt==0)  cin>>tmp.name>>tmp.phonenumber>>tmp.classes>>tmp.dormitorynumber,s.insert(s.size(),tmp);
        if(opt==1)  cin>>a,s.erase(a);
        if(opt==2) {
            cin>>a>>opt2;
            if(opt2==3)cin>>key,s.modify(a,opt2,key);
            else cin>>b,s.modify(a,opt2,b);
        } 
        if(opt==3)  cin>>a,cout<<(s.IndexOf(a)!=-1?1:0)<<endl;
        if(opt==4)  cin>>a,s.output(a);
    }
}
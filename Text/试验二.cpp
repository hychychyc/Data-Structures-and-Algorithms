#include<iostream>
using namespace std;
template<class T>
class Sort{
	public:
		void ranksort(T *a,int n){//给数组a的n个元素排名次，结果在r中返回 
			int *r=new int[n];
			for(int i=0;i<n;i++) r[i]=0;//初始化 
			for(int i=1;i<n;i++)
				for(int j=0;j<i;j++)
					if(a[j]<=a[i]) r[i]++;//比较所有元素对 
					else r[j]++;
			for(int i=0;i<n;i++) //原地重排数组元素使之有序 
				while(r[i]!=i){
					int t=r[i];//把正确的元素移到a[i] 
					swap(a[i],a[t]);
					swap(r[i],r[t]);
				}
			
		}
		void selectionsort(T *a,int n){//及时终止的选择排序 
			bool sorted=false;
			for(int size=n;!sorted&&(size>1);size--){
				int indexOfMax=0;
				sorted=true; 
				for(int i=1;i<size;i++)//查找最大元素 
					if(a[indexOfMax]<=a[i]) indexOfMax=i;
					else sorted=false;//无序 
				swap(a[indexOfMax],a[size-1]);
			}
		}
		bool bubble(T *a,int n){//把数组中的最大元素移到右端 
			bool swapped=0;//交换标记 
			for(int i=0;i<n-1;i++) 
				if(a[i]>a[i+1])
				swap(a[i],a[i+1]),swapped=1;//交换并标记 
			return swapped;
		}
		void bubblesort(T *a,int n){//及时终止的冒泡排序 
			for(int i=n;i>1&&bubble(a,i);i--);
		}
		void insertsort(T *a,int n){//插入排序 
			for(int i=1,j;i<n;i++){//把a[i]插入之前的有序数组 
				T t=a[i];
				for(j=i-1;j>=0&&t<a[j];j--) a[j+1]=a[j];
				a[j+1]=t;
			}
		} 
};
Sort<int>s;
int main(){int n;
	cin>>n;
	int *a=new int[n];
	for(int i=0;i<n;i++) cin>>a[i];
	s.ranksort(a,n);
	for(int i=0;i<n;i++) cout<<a[i]<<' ';
	delete [] a;	
} 

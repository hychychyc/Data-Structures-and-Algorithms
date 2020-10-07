#include<iostream>
using namespace std;
template<class T>
class Sort{
	public:
		void ranksort(T *a,int n){//������a��n��Ԫ�������Σ������r�з��� 
			int *r=new int[n];
			for(int i=0;i<n;i++) r[i]=0;//��ʼ�� 
			for(int i=1;i<n;i++)
				for(int j=0;j<i;j++)
					if(a[j]<=a[i]) r[i]++;//�Ƚ�����Ԫ�ض� 
					else r[j]++;
			for(int i=0;i<n;i++) //ԭ����������Ԫ��ʹ֮���� 
				while(r[i]!=i){
					int t=r[i];//����ȷ��Ԫ���Ƶ�a[i] 
					swap(a[i],a[t]);
					swap(r[i],r[t]);
				}
			
		}
		void selectionsort(T *a,int n){//��ʱ��ֹ��ѡ������ 
			bool sorted=false;
			for(int size=n;!sorted&&(size>1);size--){
				int indexOfMax=0;
				sorted=true; 
				for(int i=1;i<size;i++)//�������Ԫ�� 
					if(a[indexOfMax]<=a[i]) indexOfMax=i;
					else sorted=false;//���� 
				swap(a[indexOfMax],a[size-1]);
			}
		}
		bool bubble(T *a,int n){//�������е����Ԫ���Ƶ��Ҷ� 
			bool swapped=0;//������� 
			for(int i=0;i<n-1;i++) 
				if(a[i]>a[i+1])
				swap(a[i],a[i+1]),swapped=1;//��������� 
			return swapped;
		}
		void bubblesort(T *a,int n){//��ʱ��ֹ��ð������ 
			for(int i=n;i>1&&bubble(a,i);i--);
		}
		void insertsort(T *a,int n){//�������� 
			for(int i=1,j;i<n;i++){//��a[i]����֮ǰ���������� 
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

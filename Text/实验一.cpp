#include<cstdio>
#include<iostream>
using namespace std;
//�ݹ麯�� 
int dfs(int *a,int n,int x,int X,int s){//x����ö��λ��X�Ǽ������λ�� ��s�ǳ˻��� 
	int ans=0;
	if(x==n)	return s;
	swap(a[X],a[x]);ans^=dfs(a,n,x+1,X+1,s+a[X]*(X+1));//ѡxλ 
	swap(a[X],a[x]);ans^=dfs(a,n,x+1,X,s);//��ѡ 
	return ans;
}
int main(){
	int n;
	scanf("%d",&n);
	int *a=new int [n];
	for(int i=0;i<n;i++) 
		scanf("%d",&a[i]);
	printf("%d",dfs(a,n,0,0,0));
	delete []a;
} 

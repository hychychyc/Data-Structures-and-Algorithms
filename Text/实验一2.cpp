#include<cstdio>
#include<iostream>
using namespace std;
//�ݹ麯�� 
int dfs(int *a,int n,int x,int s){//x����λ�ã�s�ǳ˻��� 
	int ans=0;
	if(x==n)	return s;
	for(int i=x;i<n;i++){//ö�ٵ�xλ 
		swap(a[x],a[i]);//������ǰλ 
		ans|=dfs(a,n,x+1,s+(a[x]^(x+1)));//�ݹ�+ͳ�ƴ� 
		swap(a[x],a[i]);//������ǰλ 
	}
	return ans;
}
int main(){
	int n;scanf("%d",&n);
	int *a=new int [n];
	for(int i=0;i<n;i++) 
		scanf("%d",&a[i]);
	printf("%d",dfs(a,n,0,0));
	delete []a;
} 

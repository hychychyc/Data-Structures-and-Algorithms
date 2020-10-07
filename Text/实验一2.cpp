#include<cstdio>
#include<iostream>
using namespace std;
//递归函数 
int dfs(int *a,int n,int x,int s){//x代表位置，s是乘积和 
	int ans=0;
	if(x==n)	return s;
	for(int i=x;i<n;i++){//枚举第x位 
		swap(a[x],a[i]);//换到当前位 
		ans|=dfs(a,n,x+1,s+(a[x]^(x+1)));//递归+统计答案 
		swap(a[x],a[i]);//换到当前位 
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

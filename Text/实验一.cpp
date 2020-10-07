#include<cstdio>
#include<iostream>
using namespace std;
//递归函数 
int dfs(int *a,int n,int x,int X,int s){//x代表枚举位，X是集合里的位置 ，s是乘积和 
	int ans=0;
	if(x==n)	return s;
	swap(a[X],a[x]);ans^=dfs(a,n,x+1,X+1,s+a[X]*(X+1));//选x位 
	swap(a[X],a[x]);ans^=dfs(a,n,x+1,X,s);//不选 
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

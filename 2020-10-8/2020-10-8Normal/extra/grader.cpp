/***************************************************************
	File name: grader.cpp
	Author: huhao
	Create time: Sat 26 Sep 2020 03:43:01 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
const int N=100010;
int n,tp;
int a[N],b[N];
#include<random>
void check(int k)
{
	static int c[N*3]; int m=n*3;
	fr(i,0,m-1) c[i]=0;
#define set(v) c[((v)%m+m)%m]=1
	fr(i,1,n) set(a[i]+a[(i-1+k)%n+1]);
	fr(i,1,n) set(b[i]+b[(i-1+k)%n+1]);
	fr(i,1,n) set(a[i]+b[i]);
#undef set
	fr(i,0,m-1) if(!c[i]){ printf("%d\n",k); exit(0); }
}
void solve(int,int*,int*);
int main()
{
	std::mt19937 Rand;
	n=read(); tp=read();
	solve(n,a,b);
	if(tp==1) check(1);
	else fr(i,1,10000000/n) check(Rand()%n);
	printf("true\n");
	return 0;
}

/***************************************************************
	File name: grader.cpp
	Author: huhao
	Create time: Wed 30 Sep 2020 11:56:22 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
void init(int n,int *a);
void modify(int x,int y);
int query(int op);
#include<random>
int public_version=1;
int main()
{
	int type=(public_version?0:read());
	int n,q;
	const int N=100000010;
	static int a[N];
	if(type==0)
	{
		n=read(); q=read();
		for(int i=1;i<=n;i++) a[i]=read();
		init(n,a);
		while(q--)
		{
			int op=read();
			if(op==1){ int x=read(),y=read(); modify(x,y); }
			else printf("%d\n",query(read()));
		}
	}
	return 0;
}

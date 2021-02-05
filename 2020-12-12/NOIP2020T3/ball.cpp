#include<cstdio>
#include<cstring>
using namespace std;
inline void write(int x)
{
	int y=10;
	while(y<=x)y*=10;
	while(y!=1){y/=10;putchar(x/y+'0');x%=y;}
}
int m;
struct node
{
	int a[410],top;
	inline int pop(){return a[top--];}
	inline void push(int x){a[++top]=x;}
}sta[110];
int ss;
struct Answer{int x,y;}Ans[821000];
inline void moe(int x,int y){sta[y].push(sta[x].pop());Ans[++ss]=(Answer){x,y};}
inline void moe(int x,int y,int t){while(t--)moe(x,y);}
inline void moe(int x,int y0,int y1,int t)
{
	while(sta[x].top>0)
	{
		if(t==sta[x].a[sta[x].top])moe(x,y0);
		else
		{
			if(sta[y1].top<m)moe(x,y1);
			else moe(x,y0);
		}
	}
}
int main()
{
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	int n;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		sta[i].top=m;
		for(int j=1;j<=m;j++)scanf("%d",&sta[i].a[j]);
	}
	sta[n+1].top=0;
	for(int i=1;i<=n-2;i++)
	{
		int cnt=0;
		for(int j=1;j<=m;j++)cnt+=i==sta[n].a[j];
		moe(i,n+1,cnt);
		moe(n,i,n+1,i);
		moe(n+1,n,m-cnt);
		moe(n-1,n+1,n,i);
		moe(n+1,n-1,m);
		int zero=n,emp=n+1;
		for(int j=n-1;j>=i;j--)
		{
			cnt=0;
			for(int k=1;k<=m;k++)cnt+=i==sta[j].a[k];
			moe(zero,emp,cnt);
			moe(j,zero,emp,i);
			zero=emp;emp=j;
		}
		for(int j=i+2;j<=n+1;j++)
		{
			cnt=0;
			while(i==sta[j].a[sta[j].top]){cnt++;moe(j,i);}
			moe(i+1,j,cnt);
		}
		moe(n+1,i+1,m);
	}
	int i=1,j=1;
	while(i<=m&&n-1==sta[n-1].a[i])i++;
	while(j<=m&&n==sta[n].a[j])j++;
	while(i<=m&&j<=m)
	{
		if(i<j)
		{
			moe(n-1,n+1,m-i+1);
			moe(n,n-1,m-j+1);
			moe(n+1,n);
			moe(n-1,n+1);
			moe(n-1,n,m-j);
			moe(n+1,n-1,m-i+1);
		}
		else
		{
			moe(n,n+1,m-j+1);
			moe(n-1,n,m-i+1);
			moe(n+1,n-1);
			moe(n,n+1);
			moe(n,n-1,m-i);
			moe(n+1,n,m-j+1);
		}
		while(i<=m&&n-1==sta[n-1].a[i])i++;
		while(j<=m&&n==sta[n].a[j])j++;
	}
	write(ss);putchar('\n');
	for(int i=1;i<=ss;i++){write(Ans[i].x);putchar(' ');write(Ans[i].y);putchar('\n');}
	return 0;
}
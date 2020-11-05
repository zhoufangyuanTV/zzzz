#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[110000];int len,last[41000];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
bool b[410000];
int tot[410000];
int count(int x,int fa)
{
	tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&b[y])tot[x]+=count(y,x);
	}
	return tot[x];
}
int ce,ff,size;
void find(int x,int fa)
{
	int f=size-tot[x];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&b[y])
		{
			find(y,x);
			if(f<tot[y])f=tot[y];
		}
	}
	if(f<ff)ce=x,ff=f;
}
inline int lowbit(int x){return x&-x;}
int ka,c[21000];
inline void change(int x,int s)
{
	while(x<=ka)
	{
		c[x]+=s;
		x+=lowbit(x);
	}
}
inline int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=c[x];
		x-=lowbit(x);
	}
	return s;
}
long long ss=0;
void calc(int x,int d,int fa)
{
	if(d>ka)return ;
	ss+=sum(ka-d)+1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&b[y])calc(y,d+a[k].c,x);
	}
}
void add(int x,int d,int fa)
{
	if(d>ka)return ;
	change(d,1);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa&&b[y])add(y,d+a[k].c,x);
	}
}
void div(int x)
{
	count(x,0);
	ff=0x3f3f3f3f;size=tot[x];
	find(x,0);
	b[ce]=false;
	for(int i=1;i<=ka;i++)c[i]=0;
	for(int k=last[ce];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])
		{
			calc(y,a[k].c,0);
			add(y,a[k].c,0);
		}
	}
	for(int k=last[ce];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(b[y])div(y);
	}
}
int main()
{
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);ins(y,x,c);
	}
	scanf("%d",&ka);
	memset(b,true,sizeof(b));
	div(1);
	printf("%lld\n",ss);
	return 0;
}
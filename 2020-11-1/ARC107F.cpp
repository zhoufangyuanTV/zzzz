#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next,other;
}a[3100];int len,last[610];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
	len++;
	a[len].x=y;a[len].y=x;a[len].c=0;
	a[len].next=last[y];last[y]=len;
	a[len-1].other=len;
	a[len].other=len-1;
}
int st,ed;
int dep[610];
int list[610];
bool build()
{
	memset(dep,0,sizeof(dep));dep[st]=1;
	int head=1,tail=2;list[1]=st;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(a[k].c>0&&dep[y]==0)
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[ed];
}
int cur[610];
inline int mymin(int x,int y){return x<y?x:y;}
int find(int x,int f)
{
	if(x==ed)return f;
	int used=0;
	for(int &k=cur[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(a[k].c>0&&dep[y]==dep[x]+1&&used<f)
		{
			int tt=find(y,mymin(a[k].c,f-used));
			used+=tt;
			a[k].c-=tt;
			a[a[k].other].c+=tt;
			if(used==f)break;
		}
	}
	return used;
}
int A[310];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	int ss=0;
	st=n*2+1;ed=n*2+2;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)
	{
		int b;scanf("%d",&b);
		if(b>0)
		{
			ss+=b;
			ins(st,i,b*2);
			ins(i,n+i,A[i]+b);
			ins(n+i,ed,0);
		}
		else
		{
			ss-=b;
			ins(st,i,0);
			ins(i,n+i,A[i]-b);
			ins(n+i,ed,-b*2);
		}
	}
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		ins(n+u,v,0x3f3f3f3f);ins(n+v,u,0x3f3f3f3f);
	}
	while(build())
	{
		for(int i=1;i<=ed;i++)cur[i]=last[i];
		ss=ss-find(st,0x3f3f3f3f);
	}
	printf("%d\n",ss);
	return 0;
}
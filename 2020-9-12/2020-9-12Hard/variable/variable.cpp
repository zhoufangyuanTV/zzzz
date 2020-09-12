#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
struct node
{
	int x,y,c,next,other;
}a[21000];int len,last[510];
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
int dep[510];
int list[510];
bool bg()
{
	memset(dep,-1,sizeof(dep));dep[st]=1;
	int head=1,tail=2;list[1]=st;
	while(head<tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(dep[y]==-1&&a[k].c>0)
			{
				dep[y]=dep[x]+1;
				list[tail++]=y;
			}
		}
		head++;
	}
	return dep[ed]!=-1;
}
bool b[510];
int cur[510];
inline int mymin(int x,int y){return x<y?x:y;}
int find(int x,int f)
{
	if(x==ed)return f;
	if(b[x]==false)return 0;
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
	if(used==0)b[x]=false;
	return used;
}
int v[510],vv[510];
int main()
{
	freopen("variable.in","r",stdin);
	freopen("variable.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,W,p,q;scanf("%d%d%d%d",&n,&W,&p,&q);
		len=0;memset(last,0,sizeof(last));
		st=n+1;ed=n+2;
		for(int i=1;i<=n;i++)v[i]=1;
		memset(vv,0,sizeof(vv));
		for(int i=1;i<=p;i++)
		{
			int x,y,z,a,b,c,d,e,f;
			scanf("%d%d%d%d%d%d%d%d%d",&x,&y,&z,&a,&b,&c,&d,&e,&f);
			ins(x,y,a*2);ins(y,x,a*2);ins(y,z,b*2);ins(z,y,b*2);ins(x,z,c*2);ins(z,x,c*2);
			v[x]=v[x]+d-f;v[y]=v[y]-d+e;v[z]=v[z]-e+f;
		}
		for(int i=1;i<=q;i++)
		{
			int x,y,r;scanf("%d%d%d",&x,&y,&r);
			if(r==0)ins(x,y,0x3f3f3f3f);
			else if(r==1)ins(x,y,0x3f3f3f3f),ins(y,x,0x3f3f3f3f);
			else vv[x]=-1,vv[y]=1;
		}
		long long ss=0;
		for(int i=1;i<=n;i++)
		{
			int vvv=abs(v[i]);ss-=vvv;
			if(vv[i]==1)ins(st,i,0x3f3f3f3f);
			else ins(st,i,vvv-v[i]);
			if(vv[i]==-1)ins(i,ed,0x3f3f3f3f);
			else ins(i,ed,vvv+v[i]);
		}
		while(bg())
		{
			memset(b,true,sizeof(b));
			for(int i=1;i<=ed;i++)cur[i]=last[i];
			ss=ss+find(st,0x3f3f3f3f);
		}
		printf("%lld\n",1ll*W*ss);
	}
	return 0;
}
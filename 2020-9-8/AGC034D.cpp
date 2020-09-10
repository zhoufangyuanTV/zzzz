#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,w,next,other;
}a[21000];int len,last[2100];
inline void ins(int x,int y,int c,int w)
{
	len++;a[len].x=x;a[len].y=y;a[len].c=c;a[len].w=w;
	a[len].next=last[x];last[x]=len;a[len].other=len+1;
	len++;a[len].x=y;a[len].y=x;a[len].c=0;a[len].w=-w;
	a[len].next=last[y];last[y]=len;a[len].other=len-1;
}
int n;
long long d[2100];
int pre[2100];
bool v[2100];
int list[2100];
void BellmanFord(int st)
{
	memset(d,-64,sizeof(d));d[st]=0;
	memset(v,false,sizeof(v));v[st]=true;
	int head=1,tail=2;list[1]=st;
	while(head!=tail)
	{
		int x=list[head];
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(a[k].c>0&&d[y]<d[x]+a[k].w)
			{
				d[y]=d[x]+a[k].w;
				pre[y]=k;
				if(v[y]==false)
				{
					v[y]=true;
					list[tail++]=y;
					if(tail==n*2+7)tail=1;
				}
			}
		}
		v[x]=false;
		head++;if(head==n*2+7)head=1;
	}
}
int main()
{
	scanf("%d",&n);
	int st=n*2+1,ed=n*2+6;
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(st,i,c,0);
		ins(i,n*2+2,0x3f3f3f3f,x+y);
		ins(i,n*2+3,0x3f3f3f3f,-x+y);
		ins(i,n*2+4,0x3f3f3f3f,-x-y);
		ins(i,n*2+5,0x3f3f3f3f,x-y);
	}
	for(int i=1;i<=n;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(n+i,ed,c,0);
		ins(n*2+2,n+i,0x3f3f3f3f,-x-y);
		ins(n*2+3,n+i,0x3f3f3f3f,x-y);
		ins(n*2+4,n+i,0x3f3f3f3f,x+y);
		ins(n*2+5,n+i,0x3f3f3f3f,-x+y);
	}
	pre[st]=0;BellmanFord(st);
	long long ss=0;
	while(d[ed]!=0xc0c0c0c0c0c0c0c0ll)
	{
		int f=0x3f3f3f3f;
		for(int k=pre[ed];k>0;k=pre[a[k].x])if(a[k].c<f)f=a[k].c;
		for(int k=pre[ed];k>0;k=pre[a[k].x])a[k].c-=f,a[a[k].other].c+=f;
		ss+=d[ed]*f;
		BellmanFord(st);
	}
	printf("%lld\n",ss);
	return 0;
}
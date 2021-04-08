#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[410000];int len,last[210000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fa[210000];
int ff,ce,cnt;
void dfs(int x,int dep)
{
	if(ff<dep)
	{
		ff=dep;
		ce=x;
		cnt=1;
	}
	else if(ff==dep)cnt++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dfs(y,dep+1);
		}
	}
}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int n;scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,n+i);ins(n+i,y);
		ins(y,n+i);ins(n+i,x);
	}
	ff=-1;fa[1]=0;dfs(1,0);
	int xx=ce;
	ff=-1;fa[xx]=0;dfs(xx,0);
	int yy=ce,dis=ff;
	int M=yy,mid=dis/2;
	while(mid--)M=fa[M];
	int cc=0,gg=0;
	bool bk=false,bbk=false;
	for(int k=last[M];k>0;k=a[k].next)
	{
		int y=a[k].y;
		fa[y]=M;
		ff=-1;dfs(y,1);
		if(ff==dis/2)
		{
			cc+=cnt;
			gg++;
			if(cnt==1)bk=true;
			else bbk=true;
		}
	}
	dis=dis/2;
	if(n&1)
	{
		if(cc==2)printf("%d\n",dis-1);
		else printf("%d\n",dis);
	}
	else
	{
		if(gg>=4)printf("%d\n",dis);
		else if(gg==3)
		{
			if(bbk)printf("%d\n",dis);
			else printf("%d\n",dis-1);
		}
		else if(gg==2)
		{
			if(bbk==false)
			{
				if(dis==1)puts("0");
				else printf("%d\n",dis-2);
			}
			else if(bk==true)
			{
				printf("%d\n",dis-1);
			}
			else printf("%d\n",dis);
		}
	}
	return 0;
}

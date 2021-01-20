#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[6100];int len,last[3100];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int n,s[3100];
bool b[6100];
int rt,ss;
void dfs(int x)
{
	if(x==rt)dfs(x+1);
	else if(x==n+1)ss++;
	else
	{
		for(int i=2;i<=2*n;i++)
		{
			if(b[i])
			{
				bool bk=true;
				for(int k=last[x];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(y<x||y==rt)
					{
						if((s[y]<=n)==(i<=n)&&s[y]+1!=i&&s[y]-1!=i){bk=false;break;}
						if((s[y]<=n)!=(i<=n)&&s[y]+n!=i&&s[y]-n!=i){bk=false;break;}
					}
				}
				if(bk)
				{
					b[i]=false;
					s[x]=i;
					dfs(x+1);
					s[x]=0;
					b[i]=true;
				}
			}
		}
	}
}
int main()
{
	freopen("chess.in","r",stdin);
	freopen("chess.out","w",stdout);
	int q;scanf("%d%d",&n,&q);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	for(int i=1;i<=q;i++)
	{
		scanf("%d",&rt);s[rt]=1;
		ss=0;memset(b,true,sizeof(b));
		dfs(1);
		printf("%d\n",ss);
	}
	return 0;
}
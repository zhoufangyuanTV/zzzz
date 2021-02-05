#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,w,next;
}a[1100];int len,last[1100];
inline void ins(int x,int y,int w)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].w=w;
	a[len].next=last[x];last[x]=len;
}
int c[1100],cc[31];
bool b[31];bool bg;
void dfs(int x,int fa,int S)
{
	if(bg==false)return ;
	b[x]=true;
	for(int k=last[x];k>0;k=a[k].next)
	{
		if((S|1<<(k-1)/2)!=S)continue;
		int y=a[k].y;
		if(y!=fa)
		{
			if(b[y]){bg=false;return ;}
			dfs(y,x,S);
			if(bg==false)return ;
		}
	}
}
int ss,Ans[1100];
int main()
{
	freopen("forget.in","r",stdin);
	freopen("forget.out","w",stdout);
	int n,m,t;scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=t;i++)scanf("%d",&c[i]);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		ins(x,y,w);ins(y,x,w);
	}
	ss=0x3f3f3f3f;
	if(m<=20)
	{
		for(int i=0;i<1<<m;i++)
		{
			int sr=0;
			memset(cc,0,sizeof(cc));
			for(int j=1;j<=m;j++)
			{
				if((i|1<<j-1)==i)cc[a[j*2].w]++,sr++;
			}
			bool bk=true;
			for(int j=1;j<=t;j++)if(cc[j]>c[j]){bk=false;break;}
			if(bk)
			{
				memset(b,false,sizeof(b));bg=true;
				for(int j=1;j<=n;j++)if(b[j])dfs(j,0,i);
				if(bg&&m-sr<ss)
				{
					ss=0;
					for(int j=1;j<=m;j++)
					{
						if((i|1<<j-1)!=i)Ans[++ss]=j;
					}
				}
			}
		}
	}
	printf("%d\n",ss);
	for(int i=1;i<=ss;i++)printf("%d\n",Ans[i]);
	return 0;
}
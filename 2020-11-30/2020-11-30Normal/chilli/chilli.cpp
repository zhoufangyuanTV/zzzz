#include<cstdio>
#include<cstring>
#include<set>
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
int n,fa[210000],dep[210000],son[210000],tot[210000];
void dfs(int x)
{
	son[x]=0;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs(y);
			if(tot[son[x]]<tot[y])son[x]=y;
			tot[x]+=tot[y];
		}
	}
}
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
inline int abc(int a,int b,int c){return mymax(b-a,mymax(c-a,b-c));}
int ss;
set<int> SS,S[210000];
void dfs(int x,int tp)
{
	if(!SS.empty())
	{
		set<int>::iterator it=SS.lower_bound((tot[1]-tot[x]+1)/2);
		if(it==SS.end())
		{
			int l=*SS.rbegin();
			ss=mymin(ss,abc(l,tot[1]-tot[x]-l,tot[x]));
		}
		else
		{
			int r=*it;
			ss=mymin(ss,abc(tot[1]-tot[x]-r,r,tot[x]));
			if(it!=SS.begin())
			{
				it--;
				int l=*it;
				ss=mymin(ss,abc(l,tot[1]-tot[x]-l,tot[x]));
			}
		}
	}
	if(son[x]!=0)dfs(son[x],tp);
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x]&&y!=son[x])
		{
			dfs(y,y);
			S[tp].insert(S[y].begin(),S[y].end());
			S[y].clear();
		}
	}
	if(x!=1&&!S[tp].empty())
	{
		set<int>::iterator it=S[tp].lower_bound((tot[x]+1)/2);
		if(it==S[tp].end())
		{
			int l=*S[tp].rbegin();
			ss=mymin(ss,abc(l,tot[x]-l,tot[1]-tot[x]));
		}
		else
		{
			int r=*it;
			ss=mymin(ss,abc(tot[x]-r,r,tot[1]-tot[x]));
			if(it!=S[tp].begin())
			{
				it--;
				int l=*it;
				ss=mymin(ss,abc(l,tot[x]-l,tot[1]-tot[x]));
			}
		}
	}
	S[tp].insert(tot[x]);
	SS.insert(tot[x]);
}
int main()
{
	freopen("chilli.in","r",stdin);
	freopen("chilli.out","w",stdout);
	scanf("%d",&n);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dep[1]=1;dfs(1);
	ss=0x3f3f3f3f;
	dfs(1,1);
	printf("%d\n",ss);
	return 0;
}

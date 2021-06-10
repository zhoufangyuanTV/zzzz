#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct trnode
{
	int son[26],len,fail;
}tr[1010000];int trlen;
char s[510000];
int pos[510000];
vector<int> e[1010000];
int fa[1010000][20],ep[1010000];
struct node
{
	int x,y,next;
}a[1010000];int len,last[1010000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int list[1010000],d[1010000];
long long f[1010000],g[1010000];
void dfs1(int x)
{
	for(int k=last[x];k>0;k=a[x].next)
	{
		int y=a[k].y;
		dfs1(y);
		ep[x]+=ep[y];
	}
}
void dfs2(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		f[y]=(f[y]+f[x])%1000000007;
		g[y]=(g[y]+g[x]+f[x]*(tr[y].len-tr[x].len))%1000000007;
		dfs2(y);
	}
}
int lg2[1010000],dep[1010000];
void dfs3(int x)
{
	for(int i=1;i<=lg2[dep[x]];i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		dep[y]=dep[x]+1;
		dfs3(y);
	}
}
int ff[1010000];
long long Ans[1010000];
int ffa(int x){return ff[x]==x?x:ff[x]=ffa(ff[x]);}
int main()
{
	freopen("genshin.in","r",stdin);
	freopen("genshin.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1);
	trlen=0;
	memset(tr,0,sizeof(tr));
	tr[0].fail=-1;
	int lst=0;
	for(int i=1;i<=n;i++)
	{
		int c=s[i]-'a';
		tr[lst].son[c]=++trlen;
		tr[trlen].len=i;
		int k=tr[lst].fail;
		while(k!=-1&&tr[k].son[c]==0)k=tr[k].fail;
		lst=trlen;
		if(k==-1)tr[lst].fail=0;
		else
		{
			int p=tr[k].son[c];
			if(tr[p].len==tr[k].len+1)tr[lst].fail=p;
			else
			{
				tr[++trlen]=tr[p];
				tr[trlen].len=tr[k].len+1;
				tr[lst].fail=tr[p].fail=trlen;
				while(k!=-1&&tr[k].son[c]==p)
				{
					tr[k].son[c]=trlen;
					k=tr[k].fail;
				}
			}
		}
		pos[i]=lst;
	}
	len=0;memset(last,0,sizeof(last));
	for(int i=0;i<=trlen;i++)
	{
		for(int j=0;j<=25;j++)
		{
			if(tr[i].son[j]!=0)e[i].push_back(tr[i].son[j]);
		}
		fa[i][0]=tr[i].fail;
		if(fa[i][0]!=-1)ins(fa[i][0],i);
	}
	memset(ep,0,sizeof(ep));
	for(int i=1;i<=n;i++)ep[pos[i]]=1;
	dfs1(0);
	memset(d,0,sizeof(d));
	for(int i=0;i<=trlen;i++)
	{
		for(int j=0;j<e[i].size();j++)d[e[i][j]]++;
	}
	int head=1,tail=2;list[1]=0;
	f[0]=g[0]=0;
	while(head<tail)
	{
		int x=list[head];
		if(x!=0)
		{
			long long siz=tr[x].len-tr[tr[x].fail].len;
			f[x]=(f[x]+siz*ep[x])%1000000007;
			g[x]=(g[x]+siz*(siz+1)%1000000007*500000004%1000000007*ep[x])%1000000007;
		}
		for(int i=0;i<e[x].size();i++)
		{
			int y=e[x][i];
			f[y]=(f[y]+f[x])%1000000007;
			g[y]=(g[y]+g[x]+f[x]*(tr[y].len-tr[x].len-1))%1000000007;
		}
		head++;
	}
	dfs2(0);
	lg2[0]=-1;
	for(int i=1;i<=n;i++)lg2[i]=lg2[i/2]+1;
	dep[0]=0;
	dfs3(0);
	for(int i=0;i<=trlen;i++)ff[i]=i,Ans[i]=g[i];
	for(int i=0;i<=trlen;i++)
	{
		for(int j=0;j<e[i].size();j++)
		{
			int y=e[i][j];
			if(ep[i]==ep[y])
			{
				int fx=ffa(i),fy=ffa(y);
				if(fx!=fy)
				{
					ff[fx]=fy;
					Ans[fy]=(Ans[fy]+Ans[fx])%1000000007;
				}
			}
		}
	}
	int q;scanf("%d",&q);
	while(q--)
	{
		int l,r;scanf("%d%d",&l,&r);
		int x=pos[r];
		for(int i=lg2[dep[x]];i>=0;i--)
		{
			if(1<<i<=dep[x]&&r-l+1<=tr[fa[x][i]].len)x=fa[x][i];
		}
		printf("%lld\n",Ans[x]);
	}
	return 0;
}
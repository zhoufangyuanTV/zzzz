#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
struct node
{
	int x,y,next;
}a[1010000];int len,last[510000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int fa[510000];
void dfs(int x)
{
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa[x])
		{
			fa[y]=x;
			dfs(y);
		}
	}
}
bool gr[510000],fc[510000];
set<int> S[510000],SS,USS;
int cnt[510000];
int main()
{
	freopen("diyiti.in","r",stdin);
	freopen("diyiti.out","w",stdout);
	int n,m,q;read(n);read(m);read(q);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<n;i++)
	{
		int x,y;read(x);read(y);
		ins(x,y);ins(y,x);
	}
	fa[1]=0;dfs(1);
	memset(gr,false,sizeof(gr));
	memset(fc,false,sizeof(fc));
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=m;i++)
	{
		int x;read(x);
		gr[x]=true;
		if(fa[x]!=0)
		{
			if(gr[fa[x]])
			{
				S[fa[x]].erase(x);
				if(S[fa[x]].size()==0)SS.erase(fa[x]);
			}
			else
			{
				cnt[fa[x]]++;
				USS.insert(fa[x]);
			}
		}
		for(int k=last[x];k>0;k=a[k].next)
		{
			int y=a[k].y;
			if(y!=fa[x])
			{
				if(!gr[y])S[x].insert(y);
				else USS.erase(x);
			}
		}
		if(S[x].size()>0)SS.insert(x);
	}
	for(int i=1;i<=q;i++)
	{
		int opt;read(opt);
		if(opt==1)
		{
			int x;read(x);
			fc[x]=true;
			if(gr[x])
			{
				if(fa[x]!=0&&!gr[fa[x]])
				{
					cnt[fa[x]]--;
					if(cnt[fa[x]]==0)USS.erase(fa[x]);
				}
				SS.erase(x);
			}
			else
			{
				if(fa[x]!=0&&gr[fa[x]])
				{
					S[fa[x]].erase(x);
					if(S[fa[x]].size()==0)SS.erase(fa[x]);
				}
				USS.erase(x);
			}
		}
		else if(opt==2)
		{
			int x;read(x);
			fc[x]=false;
			if(gr[x])
			{
				if(fa[x]!=0&&!gr[fa[x]])
				{
					cnt[fa[x]]++;
					if(!fc[fa[x]])USS.insert(fa[x]);
				}
				if(S[x].size()>0)SS.insert(x);
			}
			else
			{
				if(fa[x]!=0&&gr[fa[x]])
				{
					S[fa[x]].insert(x);
					if(!fc[fa[x]])SS.insert(fa[x]);
				}
				if(cnt[x]>0)USS.insert(x);
			}
		}
		else if(opt==3)
		{
			int x;read(x);
			puts(gr[x]?"Y":"N");
		}
		else
		{
			set<int> SC,CCP;
			for(set<int>::iterator it=SS.begin();it!=SS.end();it++)
			{
				int x=*it;
				for(set<int>::iterator jt=S[x].begin();jt!=S[x].end();jt++)
				{
					int y=*jt;
					gr[y]=true;
					USS.erase(y);
					for(int k=last[y];k>0;k=a[k].next)
					{
						int yy=a[k].y;
						if(yy!=x)
						{
							if(!gr[yy]&&!fc[yy])S[y].insert(yy);
						}
					}
					if(S[y].size()>0)SC.insert(y);
				}
				S[x].clear();
			}
			SS.clear();
			SS=SC;
			for(set<int>::iterator it=USS.begin();it!=USS.end();it++)
			{
				int x=*it;
				gr[x]=true;
				if(fa[x]!=0)
				{
					if(gr[fa[x]])
					{
						S[fa[x]].erase(x);
						if(S[fa[x]].size()==0)SS.erase(fa[x]);
					}
					else
					{
						cnt[fa[x]]++;
						if(!fc[fa[x]])CCP.insert(fa[x]);
					}
				}
				for(int k=last[x];k>0;k=a[k].next)
				{
					int y=a[k].y;
					if(y!=fa[x])
					{
						if(!gr[y]&&!fc[y])S[x].insert(y);
					}
				}
				if(S[x].size()>0)SS.insert(x);
			}
			USS.clear();
			USS=CCP;
		}
	}
	return 0;
}
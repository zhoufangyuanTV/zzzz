#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int block,blk[110000];
struct edge
{
	int x,y,c;
}e[110000];
struct Query{int l,r,x,y,p;};
vector<Query> Q[21000];
int Ans[110000];
inline bool cmp(Query x,Query y){return x.r<y.r;}
vector<int> base[110000];
inline int mymin(int x,int y){return x<y?x:y;}
inline bool add(vector<int> &V,int x)
{
	for(vector<int>::iterator it=V.begin();it!=V.end();it++)
	{
		x=mymin(x,x^*it);
		if(x>*it)
		{
			V.insert(it,x);
			return true;
		}
	}
	if(x==0)return false;
	else
	{
		V.push_back(x);
		return true;
	}
}
inline int mymax(int x,int y){return x>y?x:y;}
inline int findmax(vector<int> &V,int x)
{
	for(vector<int>::iterator it=V.begin();it!=V.end();it++)x=mymax(x,x^*it);
	return x;
}
int f[110000],g[110000],siz[110000];
pair<int,int> fgind(int x)
{
	if(f[x]!=x)
	{
		pair<int,int> re=fgind(f[x]);
		return make_pair(re.first,re.second^g[x]);
	}
	return make_pair(x,0);
}
int t,T[110000];
vector<int> tbase[110000];
int tf[110000],tg[110000],tsiz[110000];
pair<int,int> tind(int x)
{
	if(f[x]!=x)
	{
		pair<int,int> re=tind(f[x]);
		return make_pair(re.first,re.second^g[x]);
	}
	if(t!=T[x])return make_pair(x,0);
	else
	{
		if(tf[x]!=x)
		{
			pair<int,int> re=tind(tf[x]);
			return make_pair(re.first,re.second^tg[x]);
		}
		return make_pair(x,0);
	}
}
int main()
{
	freopen("xor.in","r",stdin);
	freopen("xor.out","w",stdout);
	int n,m,q;scanf("%d%d%d",&n,&m,&q);
	block=ceil(m/sqrt(30.0*q));
	for(int i=1;i<=m;i++)blk[i]=(i-1)/block+1;
	for(int i=1;i<=m;i++)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].c);
	for(int i=1;i<=q;i++)
	{
		Query x;scanf("%d%d%d%d",&x.l,&x.r,&x.x,&x.y);x.p=i;
		if(blk[x.l]==blk[x.r])Q[0].push_back(x);
		else Q[blk[x.l]].push_back(x);
	}
	for(int i=1;i<=n;i++)f[i]=i,siz[i]=1;
	for(int i=0;i<Q[0].size();i++)
	{
		int l=Q[0][i].l,r=Q[0][i].r,x=Q[0][i].x,y=Q[0][i].y;
		for(int j=l;j<=r;j++)
		{
			pair<int,int> fgx=fgind(e[j].x),fgy=fgind(e[j].y);
			if(fgx.first==fgy.first)add(base[fgx.first],fgx.second^fgy.second^e[j].c);
			else
			{
				if(siz[fgx.first]<siz[fgy.first])swap(fgx,fgy);
				f[fgy.first]=fgx.first;
				g[fgy.first]=fgx.second^fgy.second^e[j].c;
				siz[fgx.first]+=siz[fgy.first];
				for(int i=0;i<base[fgy.first].size();i++)add(base[fgx.first],base[fgy.first][i]);
			}
		}
		pair<int,int> fgx=fgind(x),fgy=fgind(y);
		if(fgx.first!=fgy.first)Ans[Q[0][i].p]=-1;
		else Ans[Q[0][i].p]=findmax(base[fgx.first],fgx.second^fgy.second);
		for(int j=l;j<=r;j++)
		{
			f[e[j].x]=e[j].x;
			siz[e[j].x]=1;
			base[e[j].x].clear();
			f[e[j].y]=e[j].y;
			siz[e[j].y]=1;
			base[e[j].y].clear();
		}
	}
	memset(T,-1,sizeof(T));
	for(int i=1;i<=blk[m];i++)
	{
		sort(Q[i].begin(),Q[i].end(),cmp);
		for(int i=1;i<=n;i++)f[i]=i,siz[i]=1,base[i].clear();
		int r=i*block;
		for(int j=0;j<Q[i].size();j++)
		{
			while(r<Q[i][j].r)
			{
				r++;
				pair<int,int> fgx=fgind(e[r].x),fgy=fgind(e[r].y);
				if(fgx.first==fgy.first)add(base[fgx.first],fgx.second^fgy.second^e[r].c);
				else
				{
					if(siz[fgx.first]<siz[fgy.first])swap(fgx,fgy);
					f[fgy.first]=fgx.first;
					g[fgy.first]=fgx.second^fgy.second^e[r].c;
					siz[fgx.first]+=siz[fgy.first];
					for(int i=0;i<base[fgy.first].size();i++)add(base[fgx.first],base[fgy.first][i]);
				}
			}
			t=Q[i][j].p;
			for(int k=Q[i][j].l;k<=i*block;k++)
			{
				pair<int,int> fgx=tind(e[k].x),fgy=tind(e[k].y);
				if(t!=T[fgx.first])
				{
					T[fgx.first]=t;
					tbase[fgx.first]=base[fgx.first];
					tf[fgx.first]=f[fgx.first];
					tg[fgx.first]=g[fgx.first];
					tsiz[fgx.first]=siz[fgx.first];
				}
				if(t!=T[fgy.first])
				{
					T[fgy.first]=t;
					tbase[fgy.first]=base[fgy.first];
					tf[fgy.first]=f[fgy.first];
					tg[fgy.first]=g[fgy.first];
					tsiz[fgy.first]=siz[fgy.first];
				}
				if(fgx.first==fgy.first)add(tbase[fgx.first],fgx.second^fgy.second^e[k].c);
				else
				{
					if(tsiz[fgx.first]<tsiz[fgy.first])swap(fgx,fgy);
					tf[fgy.first]=fgx.first;
					tg[fgy.first]=fgx.second^fgy.second^e[k].c;
					tsiz[fgx.first]+=tsiz[fgy.first];
					for(int i=0;i<tbase[fgy.first].size();i++)add(tbase[fgx.first],tbase[fgy.first][i]);
				}
			}
			pair<int,int> fgx=tind(Q[i][j].x),fgy=tind(Q[i][j].y);
			if(fgx.first!=fgy.first)Ans[t]=-1;
			else
			{
				if(t==T[fgx.first])Ans[t]=findmax(tbase[fgx.first],fgx.second^fgy.second);
				else Ans[t]=findmax(base[fgx.first],fgx.second^fgy.second);
			}
		}
	}
	for(int i=1;i<=q;i++)printf("%d\n",Ans[i]);
	return 0;
}
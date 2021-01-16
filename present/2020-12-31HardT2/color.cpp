#pragma GCC optimize(2)
#include<ctime>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
int block,blk[110000];
int p[110000],q[110000],c[110000];
struct Query{int l,r,u,d;}Q[110000];
int Ans[110000];
vector<int> V[330][330];
inline bool cmp(int x,int y){return Q[x].d<Q[y].d;}
int cnt[110000];
int y[110000];
int n,cc[110000];
inline int lowbit(int x){return x&-x;}
int ST=0;
inline void change(int x,int s)
{
	ST++;
	while(x<=n)
	{
		cc[x]+=s;
		x+=lowbit(x);
	}
}
inline int sum(int x)
{
	int s=0;
	while(x>0)
	{
		s+=cc[x];
		x-=lowbit(x);
	}
	return s;
}
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	clock_t t0,t1,t2;
	double T=0,TT=0;
	int m;scanf("%d%d",&n,&m);
	block=2300;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i],&c[i]);
		q[p[i]]=i;
		blk[i]=(i-1)/block+1;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&Q[i].l,&Q[i].r,&Q[i].u,&Q[i].d);
		V[blk[Q[i].l]][blk[Q[i].r]].push_back(i);
	}
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=blk[n];i++)
	{
		for(int j:V[i][i])
		{
			for(int k=Q[j].l;k<=Q[j].r;k++)
			{
				if(Q[j].u<=p[k]&&p[k]<=Q[j].d&&cnt[c[k]]!=j)cnt[c[k]]=j,Ans[j]++;
			}
		}
		for(int j=i+1;j<=blk[n];j++)
		{
			sort(V[i][j].begin(),V[i][j].end(),cmp);
			int l=0,s=0;
			memset(y,0,sizeof(y));
			memset(cc,0,sizeof(cc));
			for(int k:V[i][j])
			{
				t0=clock();
				while(l<Q[k].d)
				{
					l++;
					if(i*block<q[l]&&q[l]<=(j-1)*block)
					{
						if(y[c[q[l]]]!=0)change(y[c[q[l]]],-1);
						else s++;
						y[c[q[l]]]=l;
						change(l,1);
					}
				}
				t1=clock();
				Ans[k]=s-sum(Q[k].u-1);
				for(int kk=Q[k].l;kk<=i*block;kk++)
				{
					if(cnt[c[kk]]!=k&&y[c[kk]]<Q[k].u&&Q[k].u<=p[kk]&&p[kk]<=Q[k].d)cnt[c[kk]]=k,Ans[k]++;
				}
				for(int kk=(j-1)*block+1;kk<=Q[k].r;kk++)
				{
					if(cnt[c[kk]]!=k&&y[c[kk]]<Q[k].u&&Q[k].u<=p[kk]&&p[kk]<=Q[k].d)cnt[c[kk]]=k,Ans[k]++;
				}
				t2=clock();
				T=T+double(t1-t0)/CLOCKS_PER_SEC;
				TT=TT+double(t2-t1)/CLOCKS_PER_SEC;
			}
		}
	}
	fprintf(stderr,"%d %lf %lf\n",ST,T,TT);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}
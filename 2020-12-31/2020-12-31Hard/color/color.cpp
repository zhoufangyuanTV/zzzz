#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int block,blk[110000];
int p[110000],q[110000],c[110000],cc[110000];
struct Query{int l,r,u,d,p;}Q[110000];
int Ans[110000];
inline bool cmp(Query x,Query y){return blk[x.l]^blk[y.l]?x.l<y.l:blk[x.r]^blk[y.r]?x.r<y.r:blk[x.u]^blk[y.u]?x.u<y.u:x.d<y.d;}
int cnt[110000];
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	block=pow(n,0.75);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&p[i],&c[i]);
		q[p[i]]=i;
		cc[p[i]]=c[i];
		blk[i]=(i-1)/block+1;
	}
	for(int i=1;i<=m;i++){scanf("%d%d%d%d",&Q[i].l,&Q[i].r,&Q[i].u,&Q[i].d);Q[i].p=i;}
	sort(Q+1,Q+m+1,cmp);
	int l=Q[1].l,r=Q[1].r,u=Q[1].u,d=Q[1].d,ss=0;
	memset(cnt,0,sizeof(cnt));
	for(int i=l;i<=r;i++)
	{
		if(u<=p[i]&&p[i]<=d)
		{
			if(cnt[c[i]]==0)ss++;
			cnt[c[i]]++;
		}
	}
	Ans[Q[1].p]=ss;
	for(int i=2;i<=m;i++)
	{
		while(l>Q[i].l)
		{
			l--;
			if(u<=p[l]&&p[l]<=d)
			{
				if(cnt[c[l]]==0)ss++;
				cnt[c[l]]++;
			}
		}
		while(r<Q[i].r)
		{
			r++;
			if(u<=p[r]&&p[r]<=d)
			{
				if(cnt[c[r]]==0)ss++;
				cnt[c[r]]++;
			}
		}
		while(u>Q[i].u)
		{
			u--;
			if(l<=q[u]&&q[u]<=r)
			{
				if(cnt[cc[u]]==0)ss++;
				cnt[cc[u]]++;
			}
		}
		while(d<Q[i].d)
		{
			d++;
			if(l<=q[d]&&q[d]<=r)
			{
				if(cnt[cc[d]]==0)ss++;
				cnt[cc[d]]++;
			}
		}
		while(l<Q[i].l)
		{
			if(u<=p[l]&&p[l]<=d)
			{
				cnt[c[l]]--;
				if(cnt[c[l]]==0)ss--;
			}
			l++;
		}
		while(r>Q[i].r)
		{
			if(u<=p[r]&&p[r]<=d)
			{
				cnt[c[r]]--;
				if(cnt[c[r]]==0)ss--;
			}
			r--;
		}
		while(u<Q[i].u)
		{
			if(l<=q[u]&&q[u]<=r)
			{
				cnt[cc[u]]--;
				if(cnt[cc[u]]==0)ss--;
			}
			u++;
		}
		while(d>Q[i].d)
		{
			if(l<=q[d]&&q[d]<=r)
			{
				cnt[cc[d]]--;
				if(cnt[cc[d]]==0)ss--;
			}
			d--;
		}
		Ans[Q[i].p]=ss;
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}
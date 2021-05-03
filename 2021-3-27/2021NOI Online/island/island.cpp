#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int block,blk[110000];
int a[110000],b[110000];
struct Query{int l,r,c,d,p;}Q[110000];
int Ans[110000];
inline bool cmp1(Query x,Query y){return x.d<y.d;}
int p[110000];
inline bool cmp2(int x,int y){return b[x]<b[y];}
int rta[110000],rtb[110000];
struct node
{
	int son[2],tot,sg;
}tr[5010000];int len;
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("island.in","r",stdin);
	freopen("island.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	block=9*sqrt(n);
	for(int i=1;i<=n;i++)blk[i]=(i-1)/block+1;
	for(int i=1;i<=n;i++)scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++)p[i]=i;
	sort(p+1,p+n+1,cmp2);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",&Q[i].l,&Q[i].r,&Q[i].c,&Q[i].d);
		Q[i].p=i;
	}
	sort(Q+1,Q+m+1,cmp1);
	len=blk[n]*2;
	for(int i=1;i<=blk[n];i++)
	{
		rta[i]=i*2-1;
		rtb[i]=i*2;
	}
	for(int i=1;i<=n;i++)
	{
		int x=rta[blk[i]];
		tr[x].tot++;
		for(int j=23;j>=0;j--)
		{
			int c=(a[i]>>j)&1;
			if(tr[x].son[c]==0)tr[x].son[c]=++len;
			x=tr[x].son[c];
			tr[x].tot++;
		}
	}
	int ii=1;
	for(int i=1;i<=m;i++)
	{
		while(ii<=n&&b[p[ii]]<Q[i].d)
		{
			int A=a[p[ii]],B=b[p[ii]];
			int x=rta[blk[p[ii]]];
			tr[x].tot--;
			for(int j=23;j>=0;j--)
			{
				int c=(A>>j)&1;
				x=tr[x].son[c];
				tr[x].tot--;
			}
			x=rtb[blk[p[ii]]];
			for(int j=23;j>=0;j--)
			{
				int c=((A^B)>>j)&1,cc=(B>>j)&1;
				if(tr[x].son[c]==0)tr[x].son[c]=++len;
				x=tr[x].son[c];
				tr[x].tot+=cc;
			}
			tr[x].sg++;
			ii++;
		}
		int l=Q[i].l,r=Q[i].r,c=Q[i].c,d=Q[i].d,ss=0;
		if(blk[l]==blk[r])
		{
			for(int j=l;j<=r;j++)ss+=(c^a[j])<=mymin(d,b[j]);
		}
		else
		{
			int st=blk[l]+1,ed=blk[r]-1;
			if(blk[l-1]==blk[l])for(int j=l;j<=blk[l]*block;j++)ss+=(c^a[j])<=mymin(d,b[j]);
			else st--;
			if(blk[r+1]==blk[r])for(int j=(blk[r]-1)*block+1;j<=r;j++)ss+=(c^a[j])<=mymin(d,b[j]);
			else ed++;
			for(int j=st;j<=ed;j++)
			{
				int x=rta[j];
				for(int k=23;k>=0;k--)
				{
					int cc=(c>>k)&1,dd=(d>>k)&1;
					if(dd==1)
					{
						ss+=tr[tr[x].son[cc]].tot;
						x=tr[x].son[cc^1];
					}
					else x=tr[x].son[cc];
					if(tr[x].tot==0)break;
				}
				ss+=tr[x].tot;
				x=rtb[j];
				for(int k=23;k>=0;k--)
				{
					int cc=(c>>k)&1;
					ss+=tr[tr[x].son[cc^1]].tot;
					x=tr[x].son[cc];
					if(x==0)break;
				}
				ss+=tr[x].sg;
			}
		}
		Ans[Q[i].p]=ss;
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}
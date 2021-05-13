#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
struct node
{
	int l,r,lc,rc,c,cc;
}tr[210000];int len;
int a[110000];
inline int mymin(int x,int y){return x<y?x:y;}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;tr[now].cc=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		tr[now].c=mymin(tr[tr[now].lc].c,tr[tr[now].rc].c);
	}
	else tr[now].c=a[l];
}
void change(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)
	{
		tr[now].c--;
		tr[now].cc--;
		return ;
	}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	tr[lc].c+=tr[now].cc;tr[lc].cc+=tr[now].cc;
	tr[rc].c+=tr[now].cc;tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(r<=mid)change(lc,l,r);
	else if(l>=mid+1)change(rc,l,r);
	else change(lc,l,mid),change(rc,mid+1,r);
	tr[now].c=mymin(tr[lc].c,tr[rc].c);
}
int findr(int now,int x)
{
	if(tr[now].c>2)return -1;
	if(tr[now].l==tr[now].r)return tr[now].l;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	tr[lc].c+=tr[now].cc;tr[lc].cc+=tr[now].cc;
	tr[rc].c+=tr[now].cc;tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(x<=mid)
	{
		int re=findr(lc,x);
		if(re==-1)return findr(rc,mid+1);
		else return re;
	}
	else return findr(rc,x);
}
int findl(int now,int x)
{
	if(tr[now].c>2)return -1;
	if(tr[now].l==tr[now].r)return tr[now].l;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	tr[lc].c+=tr[now].cc;tr[lc].cc+=tr[now].cc;
	tr[rc].c+=tr[now].cc;tr[rc].cc+=tr[now].cc;
	tr[now].cc=0;
	if(x<=mid)return findl(lc,x);
	else
	{
		int re=findl(rc,x);
		if(re==-1)return findl(lc,mid);
		else return re;
	}
}
struct seg
{
	int l,r,p;
}c[110000],C[110000];
vector<int> L[110000];
int Ans[110000],A[110000];
inline bool in(int l,int r,int x){return l<=r?l<=x&&x<=r:x<=r||l<=x;}
int P[110000];
int main()
{
	freopen("pdd.in","r",stdin);
	freopen("pdd.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&c[i].l,&c[i].r);
		c[i].p=i;
		if(c[i].l<=c[i].r)
		{
			a[c[i].l]++,a[c[i].r+1]--;
		}
		else
		{
			a[1]++;a[c[i].r+1]--;a[c[i].l]++;a[n+1]--;
		}
	}
	for(int i=2;i<=n;i++)a[i]+=a[i-1];
	bool bk=true;
	for(int i=1;i<=n;i++)
	{
		if(a[i]<2){bk=false;break;}
	}
	if(bk==false)
	{
		puts("impossible");
		return 0;
	}
	for(int i=1;i<=m;i++)P[i]=i;
	int T=4;
	while(T--)
	{
		random_shuffle(P+1,P+m+1);
		len=0;bt(1,n);
		int cc=0;
		for(int t=1;t<=m;t++)
		{
			int i=P[t];
			if(c[i].l<=c[i].r)
			{
				int ll=findr(1,c[i].l),rr=findl(1,c[i].r);
				if(ll!=-1&&ll<=c[i].r)
				{
					C[++cc]=(seg){ll,rr,i};
					if(c[i].l<ll)change(1,c[i].l,ll-1);
					if(rr<c[i].r)change(1,rr+1,c[i].r);
				}
				else change(1,c[i].l,c[i].r);
			}
			else
			{
				int ll=findr(1,c[i].l);
				if(ll==-1)
				{
					ll=findr(1,1);
					if(ll!=-1&&ll<=c[i].r)
					{
						int rr=findl(1,c[i].r);
						C[++cc]=(seg){ll,rr,i};
						change(1,c[i].l,n);
						if(1<ll)change(1,1,ll-1);
						if(rr<c[i].r)change(1,rr+1,c[i].r);
					}
					else
					{
						change(1,1,c[i].r);
						change(1,c[i].l,n);
					}
				}
				else
				{
					int rr=findl(1,c[i].r);
					if(rr==-1)
					{
						rr=findl(1,n);
						C[++cc]=(seg){ll,rr,i};
						change(1,1,c[i].r);
						if(c[i].l<ll)change(1,c[i].l,ll-1);
						if(rr<n)change(1,rr+1,n);
					}
					else
					{
						C[++cc]=(seg){ll,rr,i};
						if(c[i].l<ll)change(1,c[i].l,ll-1);
						if(rr<c[i].r)change(1,rr+1,c[i].r);
					}
				}
			}
		}
		for(int i=1;i<=n;i++)L[i].clear();
		for(int i=1;i<=cc;i++)
		{
			L[C[i].l].push_back(i);
		}
		int p=-1,x=-1,y;
		for(int i=1;i<=n;i++)
		{
			if(L[i].size()==2)
			{
				p=i;
				break;
			}
		}
		if(p==-1)
		{
			for(int i=1;i<=cc;i++)
			{
				if(C[i].l==1)
				{
					if(x==-1)x=i;
					else y=i;
				}
				else if(C[i].l>C[i].r)
				{
					if(x==-1)x=i;
					else y=i;
				}
			}
		}
		else x=L[p][0],y=L[p][1];
		int hx=x,hy=y;
		memset(Ans,0,sizeof(Ans));
		Ans[C[hx].p]=1;
		while(C[x].r%n+1!=C[hx].l&&C[x].r%n+1!=C[hy].l||C[y].r%n+1!=C[hy].l&&C[y].r%n+1!=C[hx].l)
		{
			if((C[x].r%n+1!=C[hx].l&&C[x].r%n+1!=C[hy].l)&&in(C[hy].l,C[y].r,C[x].r)||(C[y].r%n+1==C[hy].l||C[y].r%n+1==C[hx].l))
			{
				int xx=C[x].r%n+1;
				x=L[xx][L[xx].size()-1];
				L[xx].pop_back();
				Ans[C[x].p]=1;
			}
			else
			{
				int yy=C[y].r%n+1;
				y=L[yy][L[yy].size()-1];
				L[yy].pop_back();
			}
		}
		memset(A,0,sizeof(A));
		for(int i=1;i<=m;i++)
		{
			if(Ans[i]==0)
			{
				if(c[i].l<=c[i].r)
				{
					A[c[i].l]++,A[c[i].r+1]--;
				}
				else
				{
					A[1]++;A[c[i].r+1]--;A[c[i].l]++;A[n+1]--;
				}
			}
		}
		bk=true;
		for(int i=2;i<=n;i++)A[i]+=A[i-1];
		for(int i=1;i<=n;i++)
		{
			if(A[i]==0){bk=false;break;}
		}
		if(bk==false)continue;
		memset(A,0,sizeof(A));
		for(int i=1;i<=m;i++)
		{
			if(Ans[i]==1)
			{
				if(c[i].l<=c[i].r)
				{
					A[c[i].l]++,A[c[i].r+1]--;
				}
				else
				{
					A[1]++;A[c[i].r+1]--;A[c[i].l]++;A[n+1]--;
				}
			}
		}
		for(int i=2;i<=n;i++)A[i]+=A[i-1];
		for(int i=1;i<=n;i++)
		{
			if(A[i]==0){bk=false;break;}
		}
		if(bk==false)continue;
		for(int i=1;i<=m;i++)printf("%d",Ans[i]);
		return 0;
	}
	puts("impossible");
	return 0;
}
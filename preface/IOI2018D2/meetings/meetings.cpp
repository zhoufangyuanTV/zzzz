#include"meetings.h"
#include<algorithm>
using namespace std;
long long f[5100][5100];
vector<long long> Ans;
struct third
{
	int c,lc,rc;bool bk;
};
inline third operator+(third x,third y)
{
	third z;
	z.c=max(max(x.c,y.c),x.rc+y.lc);
	if(x.bk)z.lc=x.c+y.lc;
	else z.lc=x.lc;
	if(y.bk)z.rc=y.c+x.rc;
	else z.rc=y.rc;
	z.bk=x.bk&&y.bk;
	return z;
}
struct node
{
	int l,r,lc,rc;
	third c;
}tr[210000];int len;
int a[110000];
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		tr[now].c=tr[tr[now].lc].c+tr[tr[now].rc].c;
	}
	else tr[now].c=(third){a[l],a[l],a[l],a[l]};
}
third query(int now,int l,int r)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return query(lc,l,r);
	else if(l>=mid+1)return query(rc,l,r);
	else return query(lc,l,mid)+query(rc,mid+1,r);
}
vector<long long> minimum_costs(vector<int> H,vector<int> L,vector<int> R)
{
	int n=H.size(),q=L.size();
	Ans.resize(q);
	if(n<=5000&&q<=5000)
	{
		for(int i=0;i<n;i++)
		{
			f[i][i]=H[i];
			for(int j=i-1;j>=0;j--)
			{
				f[i][j]=max(f[i][j+1],(long long)H[j]);
			}
			for(int j=i+1;j<n;j++)
			{
				f[i][j]=max(f[i][j-1],(long long)H[j]);
			}
			for(int j=1;j<n;j++)f[i][j]+=f[i][j-1];
		}
		for(int i=0;i<q;i++)
		{
			long long ss=0x3f3f3f3f3f3f3f3fll;
			for(int j=L[i];j<=R[i];j++)
			{
				long long s=f[j][R[i]];
				if(L[i]>0)s-=f[j][L[i]-1];
				ss=min(ss,s);
			}
			Ans[i]=ss;
		}
	}
	else
	{
		for(int i=0;i<n;i++)
		{
			if(H[i]==1)a[i]=1;
			else a[i]=0;
		}
		len=0;bt(0,n-1);
		for(int i=0;i<q;i++)
		{
			Ans[i]=2*(R[i]-L[i]+1)-query(1,L[i],R[i]).c;
		}
	}
	return Ans;
}

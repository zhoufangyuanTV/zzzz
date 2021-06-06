#include<cstdio>
#include<cstring>
using namespace std;
template<int n,int m>
struct matrix{long long a[n][m];};
template<int n,int m,int nm>
inline matrix<n,m> operator*(const matrix<n,nm> &x,const matrix<nm,m> &y)
{
	matrix<n,m> z;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			z.a[i][j]=0;
			for(int k=0;k<nm;k++)z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j])%1000000007;
		}
	}
	return z;
}
template<int n,int m,int nm>
inline void mul(matrix<n,m> &z,const matrix<n,nm> &x,const matrix<nm,m> &y)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			z.a[i][j]=0;
			for(int k=0;k<nm;k++)z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j])%1000000007;
		}
	}
}
int a[510000];
char s[510000];
int bl[110000],br[110000],blk[510000];
struct node
{
	int l,r,lc,rc;
	matrix<10,10> c;
}tr[110000];int len;
inline void plus(long long &x,const long long &y){x+y<1000000007?x+=y:x+=y-1000000007;}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
		mul(tr[now].c,tr[tr[now].lc].c,tr[tr[now].rc].c);
	}
	else
	{
		for(int i=0;i<10;i++)tr[now].c.a[i][i]=1;
		for(int i=br[l];i>=bl[l];i--)
		{
			for(int j=0;j<10;j++)
			{
				if(j==a[i])continue;
				for(int k=0;k<10;k++)plus(tr[now].c.a[a[i]][k],tr[now].c.a[j][k]);
			}
		}
	}
}
matrix<10,1> query(int now,int l,int r,matrix<10,1> c)
{
	if(tr[now].l==l&&tr[now].r==r)return tr[now].c*c;
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	if(r<=mid)return query(lc,l,r,c);
	else if(l>=mid+1)return query(rc,l,r,c);
	else return query(lc,l,mid,query(rc,mid+1,r,c));
}
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
matrix<10,1> f[510000];
inline void jian(long long &x,const long long &y){x<y?x-=y-1000000007:x-=y;}
const long long one=1;
int main()
{
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	scanf("%s",s+1);
	int n=strlen(s+1),m;read(m);
	for(int i=1;i<=n;i++)a[i]=s[i]-'a';
	for(int i=1;i<=n;i++)blk[i]=(i-1)/10+1;
	for(int i=1;i<=blk[n];i++)bl[i]=(i-1)*10+1;
	for(int i=1;i<blk[n];i++)br[i]=i*10;
	br[blk[n]]=n;
	len=0;bt(1,blk[n]);
	for(int i=n;i>=1;i--)
	{
		f[i]=f[i+1];
		for(int j=0;j<10;j++)
		{
			if(j==a[i])plus(f[i].a[j][0],one);
			else plus(f[i].a[a[i]][0],f[i].a[j][0]);
		}
	}
	while(m--)
	{
		int l,r;read(l);read(r);
		matrix<10,1> g=f[r+1];
		if(blk[r]-blk[l]>1)
		{
			for(int i=r;i>=bl[blk[r]];i--)
			{
				for(int j=0;j<10;j++)
				{
					if(j==a[i])continue;
					else plus(g.a[a[i]][0],g.a[j][0]);
				}
			}
			g=query(1,blk[l]+1,blk[r]-1,g);
			for(int i=br[blk[l]];i>=l;i--)
			{
				for(int j=0;j<10;j++)
				{
					if(j==a[i])continue;
					else plus(g.a[a[i]][0],g.a[j][0]);
				}
			}
		}
		else
		{
			for(int i=r;i>=l;i--)
			{
				for(int j=0;j<10;j++)
				{
					if(j==a[i])continue;
					else plus(g.a[a[i]][0],g.a[j][0]);
				}
			}
		}
		long long ss=0;
		for(int i=0;i<10;i++)
		{
			plus(ss,f[l].a[i][0]);
			jian(ss,g.a[i][0]);
		}
		printf("%lld\n",ss);
	}
	return 0;
}

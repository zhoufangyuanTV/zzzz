#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
int block[110000],l[333],r[333];
int a[110000],b[110000];
int m[333][333],c[333],cc[333];
char s[110];
inline void pushdown(int blk)
{
	for(int i=l[blk];i<=r[blk];i++)
	{
		int ll=1,rr=m[blk][0]+1;
		while(ll<rr)
		{
			int mid=(ll+rr)/2;
			if(a[i]<m[blk][mid])rr=mid;
			else ll=mid+1;
		}
		if(rr<=m[blk][0])a[i]=m[blk][m[blk][0]];
		b[i]+=m[blk][0]-rr+1;
		a[i]+=c[blk];
		b[i]+=cc[blk];
	}
	m[blk][0]=c[blk]=cc[blk]=0;
}
int main()
{
	int n;scanf("%d",&n);
	int blk=sqrt(n),bk=(n-1)/blk+1;
	for(int i=1;i<=n;i++)block[i]=(i-1)/blk+1;
	for(int i=1;i<=bk;i++){l[i]=(i-1)*blk+1;r[i]=i*blk;}r[bk]=n;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),b[i]=0;
	int t;scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		scanf("%s",s+1);
		if(s[1]=='A')
		{
			int ll,rr,cg;scanf("%d%d%d",&ll,&rr,&cg);
			if(cg==0)continue;
			pushdown(block[ll]);
			pushdown(block[rr]);
			if(block[ll]==block[rr])
			{
				for(int i=ll;i<=rr;i++)
				{
					a[i]+=cg;b[i]++;
				}
			}
			else
			{
				for(int i=ll;i<=r[block[ll]];i++)
				{
					a[i]+=cg;b[i]++;
				}
				for(int i=block[ll]+1;i<=block[rr]-1;i++)
				{
					c[i]+=cg;cc[i]++;
				}
				for(int i=l[block[rr]];i<=rr;i++)
				{
					a[i]+=cg;b[i]++;
				}
			}
		}
		else if(s[1]=='M')
		{
			int ll,rr,cg;scanf("%d%d%d",&ll,&rr,&cg);
			pushdown(block[ll]);
			pushdown(block[rr]);
			if(block[ll]==block[rr])
			{
				for(int i=ll;i<=rr;i++)
				{
					if(cg>a[i])a[i]=cg,b[i]++;
				}
			}
			else
			{
				for(int i=ll;i<=r[block[ll]];i++)
				{
					if(cg>a[i])a[i]=cg,b[i]++;
				}
				for(int i=block[ll]+1;i<=block[rr]-1;i++)
				{
					if(m[i][0]==0||cg-c[i]>m[i][m[i][0]])
					{
						m[i][++m[i][0]]=cg-c[i];
						if(m[i][0]==blk)pushdown(i);
					}
				}
				for(int i=l[block[rr]];i<=rr;i++)
				{
					if(cg>a[i])a[i]=cg,b[i]++;
				}
			}
		}
		else if(s[1]=='Q')
		{
			int x;scanf("%d",&x);
			pushdown(block[x]);
			printf("%d %d\n",a[x],b[x]);
		}
	}
	return 0;
}
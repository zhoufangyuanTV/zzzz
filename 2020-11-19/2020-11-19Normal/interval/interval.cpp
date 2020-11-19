#include<cstdio>
#include<cstring>
using namespace std;
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
inline int mymin(int x,int y){return x<y?x:y;}
int lg2[510000];
int stgcd[510000][19],stmin[510000][19];
inline bool pand(int l,int r)
{
	int c=lg2[r-l+1];
	int gg=gcd(stgcd[l][c],stgcd[r-(1<<c)+1][c]);
	int mm=mymin(stmin[l][c],stmin[r-(1<<c)+1][c]);
	return gg==mm;
}
int n;
bool pand(int len)
{
	for(int i=1;i<=n-len+1;i++)
	{
		if(pand(i,i+len-1))return true;
	}
	return false;
}
int p[510000];
int main()
{
	freopen("interval.in","r",stdin);
	freopen("interval.out","w",stdout);
	scanf("%d",&n);
	lg2[0]=-1;
	for(int i=1;i<=n;i++)lg2[i]=lg2[i/2]+1;
	for(int i=1;i<=n;i++)
	{
		int x;scanf("%d",&x);
		stgcd[i][0]=stmin[i][0]=x;
	}
	for(int j=1;j<=lg2[n];j++)
	{
		for(int i=1;i<=n-(1<<j)+1;i++)
		{
			stgcd[i][j]=gcd(stgcd[i][j-1],stgcd[i+(1<<j-1)][j-1]);
			stmin[i][j]=mymin(stmin[i][j-1],stmin[i+(1<<j-1)][j-1]);
		}
	}
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(pand(mid))l=mid;
		else r=mid-1;
	}
	l--;
	int ss=0;
	for(int i=1;i<=n-l;i++)
	{
		if(pand(i,i+l))p[++ss]=i;
	}
	printf("%d %d\n",ss,l);
	for(int i=1;i<ss;i++)printf("%d ",p[i]);
	printf("%d\n",p[ss]);
	return 0;
}
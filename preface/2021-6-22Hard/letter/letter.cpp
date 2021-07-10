#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int sa[1010000],rk[1010000];
int y[1010000],Y[1010000];
long long solve(int l,int r,int L,int R)
{
	if(l>r)return 0;
	if(L==R)
	{
		long long ss=0;
		for(int i=l;i<=r;i++)ss+=abs(Y[L]-y[i]);
		return ss;
	}
	int mid=(L+R)/2;
	long long ss=0;
	for(int i=l;i<=r;i++)ss+=abs(Y[mid]-y[i]);
	int p=r;long long ms=ss;
	for(int i=r;i>=l;i--)
	{
		ss+=abs(Y[mid+1]-y[i])-abs(Y[mid]-y[i]);
		if(ss<ms){p=i-1;ms=ss;}
	}
	return solve(l,p,L,mid)+solve(p+1,r,mid+1,R);
}
int main()
{
	freopen("letter.in","r",stdin);
	freopen("letter.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	sa[0]=n+1;rk[n+1]=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&sa[i]);
		rk[sa[i]]=i;
	}
	for(int i=1;i<=n;i++)scanf("%d",&y[rk[i]]);
	int s=0;
	for(int i=1;i<n;i++)
	{
		if(rk[sa[i]+1]>rk[sa[i+1]+1])s++;
		y[i+1]-=s;
	}
	m-=s;
	if(m<1)
	{
		puts("-1");
		return 0;
	}
	long long ss=0;
	for(int i=1;i<=n;i++)
	{
		if(y[i]<1)
		{
			ss+=1-y[i];
			y[i]=1;
		}
		if(y[i]>m)
		{
			ss+=y[i]-m;
			y[i]=m;
		}
	}
	for(int i=1;i<=n;i++)Y[i]=y[i];
	sort(Y+1,Y+n+1);
	int N=unique(Y+1,Y+n+1)-Y-1;
	printf("%lld\n",ss+solve(1,n,1,N));
	return 0;
}
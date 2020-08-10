#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[2100];int len,last[1100];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%1000000007;
		x=x*x%1000000007;
		k>>=1;
	}
	return s;
}
long long jc[1100],fjc[1100];
long long C(int n,int m){return jc[n]*fjc[n-m]%1000000007*fjc[m]%1000000007;}
long long f[1100][1100],g[1100],tot[1100];
void treedp(int x,int fa)
{
	f[x][0]=1;tot[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			treedp(y,x);
			memset(g,0,sizeof(g));
			for(int i=0;i<tot[x];i++)
			{
				for(int j=0;j<=tot[y];j++)
				{
					if(a[k].c==0)g[i+j]=(g[i+j]+f[x][i]*(f[y][tot[y]-1]-f[y][j-1]+1000000007)%1000000007*C(i+j,i)%1000000007*C(tot[x]+tot[y]-i-j-1,tot[x]-i-1)%1000000007)%1000000007;
					else g[i+j]=(g[i+j]+f[x][i]*f[y][j-1]%1000000007*C(i+j,i)%1000000007*C(tot[x]+tot[y]-i-j-1,tot[x]-i-1)%1000000007)%1000000007;
				}
			}
			tot[x]+=tot[y];
			for(int i=0;i<tot[x];i++)f[x][i]=g[i];
		}
	}
	for(int i=0;i<tot[x];i++)f[x][i]=(f[x][i-1]+f[x][i])%1000000007;
}
char s[11];
int main()
{
	jc[0]=1;
	for(int i=1;i<=1000;i++)jc[i]=jc[i-1]*i%1000000007;
	fjc[1000]=ksm(jc[1000],1000000005);
	for(int i=999;i>=0;i--)fjc[i]=fjc[i+1]*(i+1)%1000000007;
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d",&n);
		len=0;memset(last,0,sizeof(last));
		for(int i=1;i<n;i++)
		{
			int x,y;scanf("%d%s%d",&x,s+1,&y);
			ins(x,y,s[1]=='>');ins(y,x,s[1]=='<');
			if(i==500)
			{
				x++;y++;
			}
		}
		treedp(0,-1);
		printf("%lld\n",f[0][tot[0]-1]);
	}
	return 0;
}
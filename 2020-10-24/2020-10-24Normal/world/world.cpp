#include<cstdio>
#include<cstring>
using namespace std;
bool b[10010000];
int p[1010000],s;
void Euler(int n)
{
	memset(b,true,sizeof(b));s=0;
	for(int i=3;i<=n;i+=2)
	{
		if(b[i])p[++s]=i;
		for(int j=1;j<=s&&i*p[j]<=n;j++)
		{
			b[i*p[j]]=false;
			if(i%p[j]==0)break;
		}
	}
}
inline long long ksm(long long x,long long k,long long p)
{
	long long xk=1;
	while(k>0)
	{
		if(k&1)xk=xk*x%p;
		x=x*x%p;
		k>>=1;
	}
	return xk;
}
int main()
{
	freopen("world.in","r",stdin);
	freopen("world.out","w",stdout);
	int n;scanf("%d",&n);
	Euler(n+1);
	int ss=0;long double Ans=0;
	for(int i=1;i<=s;i++)
	{
		int g=p[i]-1;
		if(ksm(2,(p[i]-1)/2,p[i])!=1)
		{
			while(g%2==0)g=g/2;
			bool bk=true;
			for(int j=1;!b[g];j++)
			{
				if(g%p[j]==0)
				{
					if(ksm(2,(p[i]-1)/p[j],p[i])==1){bk=false;break;}
					while(g%p[j]==0)g=g/p[j];
				}
			}
			if(g>1&&ksm(2,(p[i]-1)/g,p[i])==1)bk=false;
			if(bk)ss++,Ans=Ans+p[i]-1;
		}
	}
	printf("%.5Lf\n",Ans/(n/2));
	return 0;
}
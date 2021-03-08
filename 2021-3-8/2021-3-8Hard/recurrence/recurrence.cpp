#include<cstdio>
#include<cstring>
using namespace std;
int p;
char str[110];
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%p;
		x=x*x%p;
		k>>=1;
	}
	return s;
}
int main()
{
	freopen("recurrence.in","r",stdin);
	freopen("recurrence.out","w",stdout);
	int t;scanf("%d%d",&t,&p);
	while(t--)
	{
		int x,y,m,C;scanf("%d%d%s%d",&x,&y,str+1,&C);
		if(x==0||y==0)puts("0");
		else
		{
			if(str[1]=='+')puts("error");
			else
			{
				sscanf(str+1,"%d",&m);
				C=ksm(C,p-2);
				long long A=1,B=0,cc=1,ss=0;
				for(int i=0;i<=m;i++,cc=cc*C%p)
				{
					ss=(ss+A*B%p*cc)%p;
					long long AA=(A*x-B*y%p+p)%p,BB=(B*x+A*y)%p;
					A=AA;B=BB;
				}
				printf("%lld\n",ss);
			}
		}
	}
	return 0;
}
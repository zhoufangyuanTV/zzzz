#include<cmath>
#include<cstdio>
#include<cstring>
#include<unordered_map>
using namespace std;
int p;
long long ksm(long long x,long long k)
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
unordered_map<long long,int> M;
int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		long long a,b,x1,t;
		scanf("%d%lld%lld%lld%lld",&p,&a,&b,&x1,&t);
		if(a==0)
		{
			if(x1==t)printf("1\n");
			else if(b==t)printf("2\n");
			else printf("-1\n");
		}
		else if(a==1)
		{
			if(x1==t)printf("1\n");
			else if(b==0)printf("-1\n");
			else printf("%lld\n",(t-x1+p)*ksm(b,p-2)%p+1);
		}
		else
		{
			long long c=b*ksm(a-1,p-2)%p;
			if((x1+c)%p==0)
			{
				if(x1==t)printf("1\n");
				else printf("-1\n");
			}
			else
			{
				long long d=(t+c)*ksm(x1+c,p-2)%p;
				M.clear();
				bool bk=false;
				int n=sqrt(p);
				long long j=1;
				for(int i=0;i<n;i++,j=(j*a)%p)
				{
					if(M.find(j)==M.end())M[j]=i;
				}
				long long an=ksm(a,n);j=1;
				for(int i=0;i<=p;i+=n,j=(j*an)%p)
				{
					long long k=d*ksm(j,p-2)%p;
					if(M.find(k)!=M.end())
					{
						printf("%d\n",i+M[k]+1);
						bk=true;break;
					}
				}
				if(bk==false)printf("-1\n");
			}
		}
	}
	return 0;
}
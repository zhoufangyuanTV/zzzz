#include<cstdio>
#include<cstring>
using namespace std;
int a[1100],b[1100];
int main()
{
	freopen("div.in","r",stdin);
	freopen("div.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		memset(a,0,sizeof(a));
		int ss=0;
		for(int i=1;i<=n;i++)
		{
			int c,x;scanf("%d%d",&c,&x);
			a[(x+1)%m]+=c;a[x%m]-=c;
			ss+=c;
		}
		if(ss%m==0)ss=1;
		else ss=0;
		bool bk=true;
		for(int i=0;i<m;i++)if(a[i]!=0){bk=false;break;}
		if(bk){puts("-1");continue;}
		for(int i=2;i<=2*n+1;i++)
		{
			int s=0;
			for(int j=0;j<m;j++)
			{
				b[j]=((a[j]+s)%i+i)%i;
				s=(a[j]+s-b[j])/i;
			}
			if(s<0)
			{
				s=0;
				for(int j=0;j<m;j++)
				{
					b[j]=((-a[j]+s)%i+i)%i;
					s=(-a[j]+s-b[j])/i;
				}
			}
			b[0]+=s;
			while(b[0]>=i)
			{
				s=0;
				for(int j=0;j<m;j++)
				{
					int c=(b[j]+s)%i;
					s=(b[j]+s-c)/i;
					b[j]=c;
				}
				b[0]+=s;
			}
			bk=true;bool bbk=true;
			for(int j=0;j<m;j++)
			{
				if(b[j]!=i-1)bk=false;
				if(b[j]!=0)bbk=false;
			}
			if(bk||bbk)ss++;
		}
		printf("%d\n",ss);
	}
	return 0;
}
#include<cstdio>
#include<cstring>
using namespace std;
long double f[110000];
int g[110000];
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=39989;i++)f[i]=0,g[i]=0;
	int lastans=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		int opt;scanf("%d",&opt);
		if(opt==1)
		{
			cnt++;int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1=(x1+lastans-1)%39989+1;
			y1=(y1+lastans-1)%1000000000+1;
			x2=(x2+lastans-1)%39989+1;
			y2=(y2+lastans-1)%1000000000+1;
			if(x1==x2)
			{
				if(y1-f[x1]>1e-9)f[x1]=y1,g[x1]=cnt;
				if(y2-f[x2]>1e-9)f[x2]=y2,g[x2]=cnt;
				continue;
			}
			if(x1>x2)x1^=x2^=x1^=x2,y1^=y2^=y1^=y2;
			long double k=(long double)(y1-y2)/(x1-x2);
			for(int j=x1;j<=x2;j++)
			{
				long double yy=k*(j-x1)+y1;
				if(yy-f[j]>1e-9)f[j]=yy,g[j]=cnt;
			}
		}
		else
		{
			int k;scanf("%d",&k);
			k=(k+lastans-1)%39989+1;
			printf("%d\n",lastans=g[k]);
		}
	}
	return 0;
}
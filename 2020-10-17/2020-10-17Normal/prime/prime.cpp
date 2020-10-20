#include<cstdio>
#include<cstring>
using namespace std;
struct complex{long long real,image;}a[210000];
inline complex operator*(complex x,complex y){return (complex){x.real*y.real-x.image*y.image,x.real*y.image+x.image*y.real};}
bool b[30010000];
int main()
{
	freopen("prime.in","r",stdin);
	freopen("prime.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	memset(b,true,sizeof(b));
	for(int i=2;i<=30000000;i++)
	{
		if(b[i]==true)
		{
			for(int j=i*2;j<=30000000;j+=i)b[j]=false;
		}
	}
	int cnt=0;
	for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].real,&a[i].image);
	for(int i=1;i<=m;i++)
	{
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);
		if(opt==1||opt==2)
		{
			complex c;scanf("%lld%lld",&c.real,&c.image);
			for(int j=l;j<=r;j++)
			{
				if(opt==1)a[j]=c;
				else a[j]=a[j]*c;
				if(a[j].real>30000000||a[j].real<-30000000||a[j].image>30000000||a[j].image<-30000000)a[j]=(complex){0,0};
			}
		}
		else
		{
			cnt++;
			int ss=0;
			for(int j=l;j<=r;j++)
			{
				if(a[j].real>1&&b[a[j].real]&&a[j].image==0)ss++;
			}
			printf("%d\n",ss);
		}
	}
	return 0;
}
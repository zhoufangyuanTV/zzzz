#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
bool b[110000];
int pl,p[110000],f[110000];
int a[110000],s[110000];
inline bool cmp(int x,int y){return x>y;}
int main()
{
	memset(b,true,sizeof(b));
	pl=0;b[1]=false;f[1]=0;
	for(int i=2;i<=100000;i++)
	{
		if(b[i])
		{
			p[++pl]=i;
			f[i]=1;
		}
		for(int j=1;j<=pl&&i*p[j]<=100000;j++)
		{
			b[i*p[j]]=false;
			f[i*p[j]]=f[i]+1;
			if(i%p[j]==0)break;
		}
	}
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		for(int i=0;i<m;i++)scanf("%d",&a[i]);
		sort(a,a+m,cmp);
		bool bk=true;
		for(int i=1;i<=n;i++)
		{
			if(f[i]>=m)
			{
				bk=false;
				break;
			}
			s[i]=a[f[i]];
		}
		if(bk==false)
		{
			puts("-1");
		}
		else
		{
			for(int i=1;i<=n;i++)printf("%d%c",s[i],i==n?'\n':' ');
		}
	}
	return 0;
}
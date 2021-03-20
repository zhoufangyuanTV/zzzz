#include<cstdio>
#include<cstring>
using namespace std;
int a[1210000];
int cnt[310000];
int last[1210000];
int p[310000];
long long f[1210000];
int main()
{
	freopen("arc.in","r",stdin);
	freopen("arc.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=3*n;i++)scanf("%d",&a[i]);
	for(int i=3*n+1;i<=6*n;i++)a[i]=a[i-3*n];
	long long ss=0;
	for(int st=1;st<=3*n;st++)
	{
		if(a[st]==1)
		{
			f[st]=f[st-1]=0;
			int i,g=st;last[st]=st;
			int v=0;
			memset(cnt,0,sizeof(cnt));
			cnt[1]=1;
			memset(p,0,sizeof(p));
			p[1]=1;
			for(i=st+1;i<=6*n;i++)
			{
				cnt[a[i]]++;
				if(cnt[a[i]]==2){last[i]=g=i+1;v++;}
				else last[i]=g;
				f[i]=0;
				p[a[i]]=i;
				if(a[i]==1)break;
			}
			if(st<last[i-1])continue;
			f[i]=1;
			if(v==n)ss=(ss+1)%998244353;
			for(i=i+1;i<=st+3*n-1;i++)
			{
				cnt[a[i]]++;
				if(cnt[a[i]]==2){last[i]=g=i+1;v++;}
				else last[i]=g;
				if(cnt[a[i]]<2||a[i]==1)f[i]=f[i-1];
				else
				{
					if(last[i-1]<=p[a[i]]+1)
					{
						long long ff=(f[p[a[i]]-1]-f[last[p[a[i]]-1]-2]+998244353)%998244353;
						f[i]=(f[i-1]+ff)%998244353;
						if(v==n)ss=(ss+ff)%998244353;
					}
					else f[i]=f[i-1];
				}
				p[a[i]]=i;
			}
		}
	}
	printf("%lld\n",ss);
	return 0;
}
#include<cstdio>
#include<cstring>
using namespace std;
int x[310],y[310];
long long u[310],v[310],w[310];
long long Ans[310],tot[310],du[310][310],dv[310][310];
int f,fa[310];long long p[310];
int main()
{
	freopen("loquat.in","r",stdin);
	freopen("loquat.out","w",stdout);
	int n;scanf("%d",&n);
	Ans[0]=du[0][0]=dv[0][0]=0;tot[0]=1;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%lld%lld%lld",&x[i],&y[i],&u[i],&v[i],&w[i]);
		tot[i]=tot[x[i]]+tot[y[i]];
		f=0;int z=x[i];long long t=u[i];
		while(z>0)
		{
			fa[++f]=z;
			p[f]=t;
			if(t<tot[x[z]])z=x[z];
			else
			{
				t-=tot[x[z]];
				z=y[z];
			}
		}
		du[i][0]=0;
		for(int j=f;j>=1;j--)
		{
			z=fa[j];t=p[j];
			long long tt=t<tot[x[z]]?u[z]:tot[x[z]]+v[z];
			if(t==tt)du[i][z]=0;
			else
			{
				while((t<tot[x[z]])==(tt<tot[x[z]]))
				{
					if(t<tot[x[z]])z=x[z];
					else
					{
						t-=tot[x[z]];
						tt-=tot[x[z]];
						z=y[z];
					}
				}
				du[i][fa[j]]=(du[i][z]+w[z]+(p[j]<tot[x[fa[j]]]?du[fa[j]][z]:dv[fa[j]][z]))%1000000007;
			}
			if(p[j]<tot[x[fa[j]]])du[i][0]=(du[i][0]+dv[fa[j]][0]+tot[y[fa[j]]]%1000000007*(w[fa[j]]+du[i][fa[j]]))%1000000007;
			else du[i][0]=(du[i][0]+du[fa[j]][0]+tot[x[fa[j]]]%1000000007*(w[fa[j]]+du[i][fa[j]]))%1000000007;
		}
		f=0;z=y[i];t=v[i];
		while(z>0)
		{
			fa[++f]=z;
			p[f]=t;
			if(t<tot[x[z]])z=x[z];
			else
			{
				t-=tot[x[z]];
				z=y[z];
			}
		}
		dv[i][0]=0;
		for(int j=f;j>=1;j--)
		{
			z=fa[j];t=p[j];
			long long tt=t<tot[x[z]]?u[z]:tot[x[z]]+v[z];
			if(t==tt)dv[i][z]=0;
			else
			{
				while((t<tot[x[z]])==(tt<tot[x[z]]))
				{
					if(t<tot[x[z]])z=x[z];
					else
					{
						t-=tot[x[z]];
						tt-=tot[x[z]];
						z=y[z];
					}
				}
				dv[i][fa[j]]=(dv[i][z]+w[z]+(p[j]<tot[x[fa[j]]]?du[fa[j]][z]:dv[fa[j]][z]))%1000000007;
			}
			if(p[j]<tot[x[fa[j]]])dv[i][0]=(dv[i][0]+dv[fa[j]][0]+tot[y[fa[j]]]%1000000007*(w[fa[j]]+dv[i][fa[j]]))%1000000007;
			else dv[i][0]=(dv[i][0]+du[fa[j]][0]+tot[x[fa[j]]]%1000000007*(w[fa[j]]+dv[i][fa[j]]))%1000000007;
		}
		printf("%lld\n",Ans[i]=(Ans[x[i]]+Ans[y[i]]+tot[y[i]]%1000000007*du[i][0]+tot[x[i]]%1000000007*dv[i][0]+(tot[x[i]]%1000000007)*(tot[y[i]]%1000000007)%1000000007*w[i])%1000000007);
	}
	return 0;
}
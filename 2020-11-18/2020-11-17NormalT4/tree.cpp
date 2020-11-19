#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
inline long long ksm(long long x,long long k)
{
	long long s=1;
	while(k>0)
	{
		if(k&1)s=s*x%998244353;
		x=x*x%998244353;
		k>>=1;
	}
	return s;
}
int p[110000];
bool b[110000];
long long Omega[110000],Alpha[110000],Beta[110000],Gamma[110000],Delta[110000];
void dfs(int x,int f)
{
	Delta[x]=1;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=f)dfs(y,x);
		Delta[x]+=p[y];
	}
	Delta[x]=ksm(Delta[x],998244351);
}
long long ToF[110000];
inline void give(int x,int f,int g)
{
	Omega[f]=(Omega[f]-ToF[x]*Beta[x]%998244353+998244353)%998244353;
	Beta[f]=(Beta[f]+ToF[x]*Alpha[x])%998244353;
	Gamma[f]=(Gamma[f]+ToF[x]*Gamma[x])%998244353;
	Omega[g]=(Omega[g]-Delta[g]*Alpha[x]%998244353+998244353)%998244353;
	Gamma[g]=(Gamma[g]+Delta[g]*Gamma[x])%998244353;
	ToF[f]=(ToF[f]+Delta[g]*Beta[x])%998244353;
}
void dfs(int x,int f,int g)
{
	Omega[x]=1;
	Alpha[x]=Delta[x];
	Beta[x]=Delta[x];
	Gamma[x]=1;
	ToF[x]=Delta[f];
	long long SA=0,SB=0,SG=0,SD=0;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=f)
		{
			dfs(y,x,f);
			SA=(SA+Alpha[y])%998244353;
			SB=(SB+Beta[y])%998244353;
			SG=(SG+Gamma[y])%998244353;
			SD=(SD+Delta[y])%998244353;
		}
	}
	SD=ksm(998244354-SD,998244351);
	SA=SA*SD%998244353;
	SB=SB*SD%998244353;
	SG=SG*SD%998244353;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=f)
		{
			Alpha[y]=(Alpha[y]+Delta[y]*SA)%998244353;
			Beta[y]=(Beta[y]+Delta[y]*SB)%998244353;
			Gamma[y]=(Gamma[y]+Delta[y]*SG)%998244353;
			give(y,x,f);
		}
	}
	if(b[x])Omega[x]=1,Alpha[x]=Beta[x]=Gamma[x]=Delta[x]=0;
	else
	{
		Omega[x]=ksm(Omega[x],998244351);
		Alpha[x]=Alpha[x]*Omega[x]%998244353;
		Beta[x]=Beta[x]*Omega[x]%998244353;
		Gamma[x]=Gamma[x]*Omega[x]%998244353;
		Delta[x]=Delta[x]*Omega[x]%998244353;
	}
}
long long E[110000];
void Ans(int x,int f,int g)
{
	E[x]=(Alpha[x]*E[g]+Beta[x]*E[f]+Gamma[x])%998244353;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=f)Ans(y,x,f);
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	memset(p,0,sizeof(p));
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
		p[x]++;p[y]++;
	}
	memset(b,false,sizeof(b));
	for(int i=1;i<=m;i++)
	{
		int x;scanf("%d",&x);
		b[x]=true;
	}
	dfs(1,0);
	dfs(1,0,0);
	long long OO=ksm(998244354-Delta[1],998244351);
	Alpha[1]=Alpha[1]*OO%998244353;
	Beta[1]=Beta[1]*OO%998244353;
	Gamma[1]=Gamma[1]*OO%998244353;
	Ans(1,0,0);
	for(int i=1;i<=n;i++)printf("%lld\n",E[i]);
	return 0;
}
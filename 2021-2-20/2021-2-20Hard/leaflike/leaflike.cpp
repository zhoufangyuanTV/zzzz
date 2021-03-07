#include<cstdio>
#include<cstring>
using namespace std;
int A,B,id[2100];
bool LeRi[2100];
bool mp[2100][2100];
int match[2100];
int T,v[2100];
bool find_muniu(int x)
{
	for(int y=1;y<=B;y++)
	{
		if(T!=v[y]&&mp[x][y])
		{
			v[y]=T;
			if(match[y]==-1||find_muniu(match[y]))
			{
				match[y]=x;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	freopen("leaflike.in","r",stdin);
	freopen("leaflike.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	A=B=0;
	for(int i=1;i<=n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		LeRi[i]=(x+y)&1;
		if(LeRi[i])id[i]=++A;
		else id[i]=++B;
	}
	memset(mp,true,sizeof(mp));
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		if(LeRi[x]==LeRi[y])continue;
		if(!LeRi[x])x^=y^=x^=y;
		mp[id[x]][id[y]]=false;
	}
	int ss=0;
	memset(v,0,sizeof(v));
	memset(match,-1,sizeof(match));
	for(int i=1;i<=A;i++)
	{
		T=i;
		if(find_muniu(i))ss++;
	}
	printf("%d\n",n-ss);
	return 0;
}
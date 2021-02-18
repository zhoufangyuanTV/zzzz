#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
long long F[210000],f[210000],a[210000],b[210000],c[210000],d[210000];
int p[210000];
vector<int> e[210000];
bool v[210000];
inline bool cmp(int x,int y){return f[x]<f[y];}
int main()
{
	int n1,n2,n3,n4;scanf("%d%d%d%d",&n1,&n2,&n3,&n4);
	for(int i=1;i<=n1;i++)scanf("%lld",&a[i]);
	for(int i=1;i<=n2;i++)scanf("%lld",&b[i]);
	for(int i=1;i<=n3;i++)scanf("%lld",&c[i]);
	for(int i=1;i<=n4;i++)scanf("%lld",&d[i]);
	for(int i=1;i<=n1;i++)f[i]=a[i];
	int m;scanf("%d",&m);
	for(int i=1;i<=n2;i++)e[i].clear();
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n1;i++)p[i]=i;
	sort(p+1,p+n1+1,cmp);
	for(int i=1;i<=n2;i++)
	{
		sort(e[i].begin(),e[i].end(),cmp);
		int j=1;
		while(j<=n1&&j<=e[i].size()&&p[j]==e[i][j-1])j++;
		if(j<=n1)F[i]=f[p[j]]+b[i];
		else F[i]=0x3f3f3f3f3f3f3fll;
	}
	for(int i=1;i<=n2;i++)f[i]=F[i];
	scanf("%d",&m);
	for(int i=1;i<=n3;i++)e[i].clear();
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n2;i++)p[i]=i;
	sort(p+1,p+n2+1,cmp);
	for(int i=1;i<=n3;i++)
	{
		sort(e[i].begin(),e[i].end(),cmp);
		int j=1;
		while(j<=n2&&j<=e[i].size()&&p[j]==e[i][j-1])j++;
		if(j<=n2)F[i]=f[p[j]]+c[i];
		else F[i]=0x3f3f3f3f3f3f3fll;
	}
	for(int i=1;i<=n3;i++)f[i]=F[i];
	scanf("%d",&m);
	for(int i=1;i<=n4;i++)e[i].clear();
	for(int i=1;i<=m;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		e[y].push_back(x);
	}
	for(int i=1;i<=n3;i++)p[i]=i;
	sort(p+1,p+n3+1,cmp);
	for(int i=1;i<=n4;i++)
	{
		sort(e[i].begin(),e[i].end(),cmp);
		int j=1;
		while(j<=n3&&j<=e[i].size()&&p[j]==e[i][j-1])j++;
		if(j<=n3)F[i]=f[p[j]]+d[i];
		else F[i]=0x3f3f3f3f3f3f3fll;
	}
	for(int i=1;i<=n4;i++)f[i]=F[i];
	for(int i=1;i<=n4;i++)p[i]=i;
	sort(p+1,p+n4+1,cmp);
	if(f[p[1]]>=0x3f3f3f3f3f3f3fll)puts("-1");
	else printf("%lld\n",f[p[1]]);
	return 0;
}
#include<cstdio>
#include<cstring>
using namespace std;
#define print(s) {printf("%d",s);return 0;}
int hang[51],lie[51];
int f[51][2]
int main()
{
	freopen("two.in","r",stdin);
	freopen("two.out","w",stdout);
	int ss=0;
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	memset(hang,-1,sizeof(hang));
	memset(lie,-1,sizeof(lie));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		int hc=(c+1)/2,lc=(c&2)+((c&2)^1);
		if(x%2==0)hc^=3;
		if(y%2==0)lc^=3;
		if(hang[y]==-1)hang[y]=hc;
		if(lie[x]==-1)lie[x]=lc;
		if(hang[y]!=-1&&hang[y]!=hc)print(ss);
		if(lie[x]!=-1&&lie[x]!=lc)print(ss);
	}
}

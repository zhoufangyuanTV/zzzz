#include<ctime>
#include<cstdio>
#include<cstring>
#include<random>
#include<algorithm>
using namespace std;
int pailie[1100];
int w[1100][310],a[1100],b[310];
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
struct node{int x,p;}p[310];int plen;
int Ans[1100];
char sh[110];
int main()
{
	freopen("drawer.in","r",stdin);
	mt19937 myrand(time(0));
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&w[i][j]);
	for(int i=1;i<=n;i++)pailie[i]=i;
	shuffle(pailie+1,pailie+n+1,myrand);
	int ss=0;
	for(int t=1;t<=n;t++)
	{
		int i=pailie[t];
		p[0].x=0;plen=0;
		for(int j=1;j<=m;j++)
		{
			if(a[i]<=b[j]&&10*a[i]<w[i][j]&&1250<w[i][j])
			{
				plen++;
				p[plen]=(node){p[plen-1].x+w[i][j],j};
			}
		}
		if(plen>0)
		{
			int v=myrand()%p[plen].x;
			int l=1,r=plen;
			while(l<r)
			{
				int mid=(l+r)/2;
				if(v<p[mid].x)r=mid;
				else l=mid+1;
			}
			b[p[r].p]-=a[i];
			Ans[i]=p[r].p;
			ss+=w[i][p[r].p];
		}
	}
	sprintf(sh+1,"sheep/new/%d",ss);
	FILE *fp=fopen(sh+1,"w");
	for(int i=1;i<=n;i++)fprintf(fp,"%d\n",Ans[i]);
	fclose(fp);
	return 0;
}
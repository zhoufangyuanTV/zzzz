#pragma GCC optimize("O2")
#include<cstdio>
#include<cstring>
#include<set>
#include<utility>
#include<algorithm>
using namespace std;
pair<int,int> p[1010000];int plen;
struct node{pair<int,int> X;int D;}list[2010000];
set<pair<int,int> > S;set<int> SS;
int f[110][110],a[110],w[110];
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("dalao.in","r",stdin);
	freopen("dalao.out","w",stdout);
	int n,m,mc;scanf("%d%d%d",&n,&m,&mc);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	memset(f,-1,sizeof(f));f[0][mc]=0;
	int ss=-1;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=mc;j++)
		{
			ss=mymax(ss,f[i][j]);
			if(f[i][j]!=-1&&j>=a[i+1])
			{
				f[i+1][mymin(j-a[i+1]+w[i+1],mc)]=mymax(f[i+1][mymin(j-a[i+1]+w[i+1],mc)],f[i][j]);
				f[i+1][j-a[i+1]]=mymax(f[i+1][j-a[i+1]],f[i][j]+1);
			}
		}
	}
	for(int i=0;i<=mc;i++)ss=mymax(ss,f[n][i]);
	int head=1,tail=2;list[1]=(node){make_pair(1,0),1};
	p[plen=1]=make_pair(1,1);S.insert(make_pair(1,0));SS.insert(1);
	while(head<tail)
	{
		node x=list[head];
		if(tail>1300000)break;
		if(x.D<ss)
		{
			int F=x.X.first,L=x.X.second;
			if(L>1&&F<=100000000/L)
			{
				pair<int,int> Y(F*L,L);
				if(S.find(Y)==S.end())
				{
					S.insert(Y);
					list[tail++]=(node){Y,x.D+1};
					if(SS.find(F*L)==SS.end())
					{
						SS.insert(F*L);
						p[++plen]=make_pair(F*L,x.D+1);
					}
				}
			}
			pair<int,int> Y(F,L+1);
			if(S.find(Y)==S.end())
			{
				S.insert(Y);
				list[tail++]=(node){Y,x.D+1};
			}
		}
		head++;
	}
	sort(p+1,p+plen+1);
	for(int i=1;i<=m;i++)
	{
		int C;scanf("%d",&C);
		if(ss==-1){printf("0\n");continue;}
		bool bk=false;int k=1,minc=0;
		for(int j=plen;j>=1;j--)
		{
			if(p[j].first>C)continue;
			while(k<=plen&&p[k].first+p[j].first<=C)
			{
				minc=mymin(minc,p[k].second-p[k].first);
				k++;
			}
			if(C+minc+p[j].second-p[j].first<=ss){bk=true;break;}
		}
		printf("%d\n",bk);
	}
	return 0;
}
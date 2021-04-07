#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
struct node{int x,y;}a[110],b[110];int al,bl;
inline bool cmp(node x,node y){return x.x<y.x;}
int at,bt,ta[11000],tb[11000];
long long va[11000][2],vb[11000][2];
struct Query{int x,p;}Q[1010000];
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
struct gg
{
	int g,y;bool bk;
}g[210];
inline bool ggp(gg x,gg y){return x.g>y.g;}
multiset<int> S;
long long calc(int t)
{
	for(int i=1;i<=al;i++)
	{
		g[i*2-1].g=a[i].x;
		g[i*2-1].bk=false;
		g[i*2-1].y=a[i].y;
		g[i*2].g=a[i].x+t+1;
		g[i*2].y=a[i].y;
		g[i*2].bk=true;
	}
	sort(g+1,g+2*al+1,ggp);
	S.clear();
	long long ss=0,s=0;
	for(int i=1;i<2*al;i++)
	{
		if(g[i].bk)
		{
			int y=g[i].y;
			multiset<int>::iterator pre=S.lower_bound(y);
			if(pre==S.end())
			{
				if(S.size()>0)
				{
					int yy=*S.rbegin();
					if(yy+t<y)s+=t+1;
					else s+=t+1-(yy+t-y+1);
				}
				else s+=t+1;
			}
			else
			{
				if(*pre!=y)
				{
					int yy=*pre;
					if(y+t<yy)
					{
						if(pre==S.begin())s+=t+1;
						else
						{
							pre--;
							if(*pre+t<y)s+=t+1;
							else s+=t+1-(*pre+t-y+1);
						}
					}
					else
					{
						if(pre==S.begin())s+=yy-y;
						else
						{
							pre--;
							if(*pre+t<yy)
							{
								if(*pre+t<y)s+=yy-y;
								else s+=(yy-y);
							}
						}
					}
				}
			}
			S.insert(y);
		}
	}
}
int main()
{
	freopen("lifegame.in","r",stdin);
	freopen("lifegame.out","w",stdout);
	int n,q;scanf("%d%d",&n,&q);
	if(n==1)
	{
		scanf("%*d%*d");
		long long p=998244353,two=499122177,three=332748118;
		for(int i=1;i<=q;i++)
		{
			long long t;scanf("%lld",&t);t++;
			printf("%lld\n",((t*t%p*t%p+3*t*t%p+3*t+1)%p-(3*t*(t+1)%p*two%p)+p-t-1+p)%p*three%p);
		}
		return 0;
	}
	al=bl=0;
	for(int i=1;i<=n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		if((x+y)&1)a[++al]=(node){(x-y)/2,(x+y)/2};
		else b[++bl]=(node){(x-y)/2,(x+y)/2};
	}
	sort(a+1,a+al+1,cmp);
	sort(b+1,b+bl+1,cmp);
	ta[1]=0;at=1;
	for(int i=1;i<=al;i++)
	{
		for(int j=i+1;j<=al;j++)
		{
			if(a[i].y<a[j].y)ta[++at]=mymax(a[j].x-a[i].x,a[j].y-a[i].y);
			else ta[++at]=mymax(a[j].x-a[i].x,a[i].y-a[j].y);
		}
	}
	tb[1]=0;bt=1;
	for(int i=1;i<=bl;i++)
	{
		for(int j=i+1;j<=bl;j++)
		{
			if(b[i].y<b[j].y)tb[++bt]=mymax(b[j].x-b[i].x,b[j].y-b[i].y);
			else tb[++bt]=mymax(b[j].x-b[i].x,b[i].y-b[j].y);
		}
	}
	sort(ta+1,ta+at+1);
	sort(tb+1,tb+bt+1);
	return 0;
}

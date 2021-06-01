#include<cmath>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;
map<long long,int> M;
long long x[410000],y[410000];
template<typename T>
inline T mymax(T x,T y){return x>y?x:y;}
template<typename T>
inline T mymin(T x,T y){return x<y?x:y;}
long long to[210000][18],f[210000][18],g[210000][18];
struct point
{
	long double x,y,z;
}p[1010000];int len;
inline bool cmp(point x,point y){return x.z<y.z;}
int list[1010000];
inline long double mul(point p0,point p1,point p2)
{
	long double x1=p1.x-p0.x,y1=p1.y-p0.y;
	long double x2=p2.x-p0.x,y2=p2.y-p0.y;
	return x1*y2-x2*y1;
}
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout);
	long long ax,ay,bx,by,px,py,n;
	scanf("%lld%lld%lld%lld%lld%lld%lld%lld%lld",&x[0],&y[0],&ax,&ay,&bx,&by,&px,&py,&n);
	for(int i=1;i<=400000;i++)x[i]=(ax*x[i-1]+bx)%px;
	for(int i=1;i<=400000;i++)y[i]=(ay*y[i-1]+by)%py;
	M[x[0]]=0;
	int stx,ringx;
	for(int i=1;i<=400000;i++)
	{
		map<long long,int>::iterator it=M.find(x[i]);
		if(it!=M.end())
		{
			stx=it->second;
			ringx=i-stx;
			break;
		}
		else M[x[i]]=i;
	}
	M.clear();
	M[y[0]]=0;
	int sty,ringy;
	for(int i=1;i<=400000;i++)
	{
		map<long long,int>::iterator it=M.find(y[i]);
		if(it!=M.end())
		{
			sty=it->second;
			ringy=i-sty;
			break;
		}
		else M[y[i]]=i;
	}
	int st=mymax(stx,sty);
	if(n<st+ringx)
	{
		len=0;
		for(int i=0;i<n;i++)p[++len]=(point){x[i],y[i],0};
	}
	else
	{
		len=0;
		for(int i=0;i<st;i++)p[++len]=(point){x[i],y[i],0};
		int r=ringx%ringy;
		for(int i=0;i<ringy;i++)f[i][0]=g[i][0]=y[st+i],to[i][0]=(i+r)%ringy;
		for(int i=1;i<18;i++)
		{
			for(int j=0;j<ringy;j++)
			{
				f[j][i]=mymax(f[j][i-1],f[to[j][i-1]][i-1]);
				g[j][i]=mymin(g[j][i-1],g[to[j][i-1]][i-1]);
				to[j][i]=to[to[j][i-1]][i-1];
			}
		}
		for(int i=0;i<ringx;i++)
		{
		    long long N=(n-st-i-1)/ringx+1;
			if(N>ringy)N=ringy;
			int pos=i%ringy;
			long long maxx=-1,minn=py;
			for(int j=0;j<18;j++)
			{
				if(N>>j&1)
				{
					maxx=mymax(maxx,f[pos][j]);
					minn=mymin(minn,g[pos][j]);
					pos=to[pos][j];
				}
			}
			p[++len]=(point){x[st+i],maxx,0};
			p[++len]=(point){x[st+i],minn,0};
		}
	}
	for(int i=2;i<=len;i++)
	{
		if(p[i].x<p[1].x)swap(p[1],p[i]);
		else if(p[i].x==p[1].x&&p[i].y<p[1].y)swap(p[1],p[i]);
	}
	for(int i=2;i<=len;i++)p[i].z=atan2(p[i].y-p[1].y,p[i].x-p[1].x);
	sort(p+2,p+len+1,cmp);
	int head=1,tail=1;list[1]=1;
	for(int i=2;i<=len;i++)
	{
		while(head<tail&&mul(p[list[tail-1]],p[list[tail]],p[i])<1e-9)tail--;
		list[++tail]=i;
	}
	long double S=0;
	for(int i=2;i<tail;i++)S+=mul(p[1],p[list[i]],p[list[i+1]]);
	printf("%.Lf\n",S);
	return 0;
}

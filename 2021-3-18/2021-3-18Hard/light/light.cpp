#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int fa[3010000];
vector<int> g[3010000];
int h[3010000],son[3010000];
int z;
bool leaf[3010000];
vector<int> e[3010000];
int f[3010000];
int dfs(int x)
{
	int zz=++z;
	if(son[x]==0)leaf[zz]=true;
	else
	{
		dfs(son[x]);
		int siz=g[x].size()-1;
		e[zz].resize(siz);
		for(int k=0,j=0;k<=siz;k++)
		{
			if(g[x][k]!=son[x])e[zz][j++]=dfs(g[x][k]);
		}
	}
	return zz;
}
int main()
{
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	int n;long long ka;scanf("%d%lld",&n,&ka);
	for(int i=2;i<=n;i++)
	{
		read(fa[i]);
		g[fa[i]].push_back(i);
	}
	h[0]=-1;
	for(int i=n;i>=2;i--)
	{
		if(h[son[fa[i]]]<h[i])son[fa[i]]=i;
		if(h[fa[i]]<h[i]+1)h[fa[i]]=h[i]+1;
	}
	z=0;
	dfs(1);
	int l=1,r=n-1;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		long long ss=0,s=0;
		for(int i=n;i>=1;i--)
		{
			f[i]=1;
			if(leaf[i])s=0;
			else
			{
				for(int y:e[i])
				{
					int j,k;
					for(j=i+1,k=y;!leaf[k];j++,k++)
					{
						if(f[j]<mid){f[j]+=f[k];s+=f[j]>=mid;}
					}
					if(f[j]<mid){f[j]+=f[k];s+=f[j]>=mid;}
				}
				ss+=s;
			}
		}
		if(ss<ka)r=mid-1;
		else l=mid;
	}
	long long ss=0,s=0,SS=0,S=0;
	for(int i=n;i>=1;i--)
	{
		f[i]=1;
		if(leaf[i]){ss+=s=l==1;SS+=S=l==1;}
		else
		{
			s+=l==1;
			S+=l==1;
			for(int y:e[i])
			{
				int j,k;
				for(j=i+1,k=y;!leaf[k];j++,k++)
				{
					if(f[j]<l)
					{
						f[j]+=f[k];
						s+=f[j]>=l?f[j]:0;
						S+=f[j]>=l;
					}
					else f[j]+=f[k],s+=f[k];
				}
				if(f[j]<l)
				{
					f[j]+=f[k];
					s+=f[j]>=l?f[j]:0;
					S+=f[j]>=l;
				}
				else f[j]+=f[k],s+=f[k];
			}
			ss+=s;
			SS+=S;
		}
	}
	printf("%lld\n",ss-(SS>ka?(SS-ka)*l:0));
	return 0;
}
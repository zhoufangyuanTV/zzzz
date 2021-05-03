#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int a,b,c,d;
	inline int f(int x){return a*x*x*x+b*x*x+c*x+d;}
}f[110];
int l[110],r[110];
inline int mymax(int x,int y){return x>y?x:y;}
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("sleep.in","r",stdin);
	freopen("sleep.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		if(n==1)
		{
			for(int i=1;i<=n;i++)scanf("%d%d%d%d%d%d",&f[i].a,&f[i].b,&f[i].c,&f[i].d,&l[i],&r[i]);
			bool bk=true;
			for(int i=1;i<=m;i++)
			{
				int D;scanf("%*d%*d%d",&D);
				if(D<0)bk=false;
			}
			if(bk==false)
			{
				puts("mei ji ge");
				continue;
			}
			int ss=0xc0c0c0c0;
			for(int i=l[1];i<=r[1];i++)ss=mymax(ss,f[1].f(i));
			printf("%d\n",ss);
		}
		else if(n==2)
		{
			for(int i=1;i<=n;i++)scanf("%d%d%d%d%d%d",&f[i].a,&f[i].b,&f[i].c,&f[i].d,&l[i],&r[i]);
			bool bk=true;
			int dd=0x3f3f3f3f,ddd=0x3f3f3f3f;
			for(int i=1;i<=m;i++)
			{
				int x,y,D;scanf("%d%d%d",&x,&y,&D);
				if(x==y&&D<0)bk=false;
				if(x==1&&y==2)dd=mymax(dd,D);
				else if(x==2&&y==1)ddd=mymax(ddd,D);
			}
			if(bk==false)
			{
				puts("mei ji ge");
				continue;
			}
			bk=false;
			int ss=0xc0c0c0c0;
			for(int i=l[1];i<=r[1];i++)
			{
				for(int j=l[2];j<=r[2];j++)
				{
					if(i<=j+dd&&j<=i+ddd)
					{
						bk=true;
						ss=mymax(ss,f[1].f(i)+f[2].f(j));
					}
				}
			}
			if(bk)printf("%d\n",ss);
			else puts("mei ji ge");
		}
		else if(n==0)puts("0");
		else if(m==0)
		{
			for(int i=1;i<=n;i++)scanf("%d%d%d%d%d%d",&f[i].a,&f[i].b,&f[i].c,&f[i].d,&l[i],&r[i]);
			int ss=0;
			for(int j=1;j<=n;j++)
			{
				int s=0xc0c0c0c0;
				for(int i=l[j];i<=r[j];i++)s=mymax(s,f[j].f(i));
				ss+=s;
			}
			printf("%d\n",ss);
		}
		else if(m==1)
		{
			for(int i=1;i<=n;i++)scanf("%d%d%d%d%d%d",&f[i].a,&f[i].b,&f[i].c,&f[i].d,&l[i],&r[i]);
			int x,y,D;scanf("%d%d%d",&x,&y,&D);
			if(x==y)
			{
				if(D<0)puts("mei ji ge");
				else
				{
					int ss=0;
					for(int j=1;j<=n;j++)
					{
						int s=0xc0c0c0c0;
						for(int i=l[j];i<=r[j];i++)s=mymax(s,f[j].f(i));
						ss+=s;
					}
					printf("%d\n",ss);
				}
			}
			else
			{
				int ss=0;
				for(int j=1;j<=n;j++)
				{
					if(j==x||j==y)continue;
					int s=0xc0c0c0c0;
					for(int i=l[j];i<=r[j];i++)s=mymax(s,f[j].f(i));
					ss+=s;
				}
				bool bk=false;
				for(int i=l[x];i<=r[x];i++)
				{
					for(int j=l[y];j<=r[y];j++)
					{
						if(i<=j+D)
						{
							bk=true;
							ss=mymax(ss,f[x].f(i)+f[y].f(j));
						}
					}
				}
				if(bk==false)puts("mei ji ge");
				else printf("%d\n",ss);
			}
		}
		else
		{
			for(int i=1;i<=n;i++)scanf("%d%d%d%d%d%d",&f[i].a,&f[i].b,&f[i].c,&f[i].d,&l[i],&r[i]);
			for(int i=1;i<=m;i++)scanf("%*d%*d%*d");
			puts("mei ji ge");
		}
	}
	return 0;
}

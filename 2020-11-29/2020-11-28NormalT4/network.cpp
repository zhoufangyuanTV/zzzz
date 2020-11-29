#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
int Friend[510000],x[5010000],y[5010000],fx[5010000],fy[5010000];
bool b[510000];
char Ans[5010000];
int main()
{
	freopen("network.in","r",stdin);
	freopen("network.out","w",stdout);
	int n,m;read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		if(i&1)
		{
			if(i==n)Friend[i]=0;
			else Friend[i]=i+1;
		}
		else Friend[i]=i-1;
	}
	memset(fx,0,sizeof(fx));
	memset(fy,0,sizeof(fy));
	for(int i=1;i<=m;i++)
	{
		read(x[i]);read(y[i]);
		if(Friend[x[i]]==0)
		{
			Friend[x[i]]=y[i];
			fy[i]=Friend[y[i]];
			Friend[Friend[y[i]]]=0;
			Friend[y[i]]=x[i];
		}
		else if(Friend[y[i]]==0)
		{
			Friend[y[i]]=x[i];
			fx[i]=Friend[x[i]];
			Friend[Friend[x[i]]]=0;
			Friend[x[i]]=y[i];
		}
		else
		{
			Friend[Friend[x[i]]]=Friend[y[i]];
			Friend[Friend[y[i]]]=Friend[x[i]];
			fx[i]=Friend[x[i]];
			fy[i]=Friend[y[i]];
			Friend[x[i]]=y[i];
			Friend[y[i]]=x[i];
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(Friend[i]<i)b[i]=true;
		else b[i]=false;
	}
	Ans[m+1]='\0';
	for(int i=m;i>=1;i--)
	{
		Friend[x[i]]=fx[i];
		Friend[y[i]]=fy[i];
		if(b[x[i]])Ans[i]='0';
		else Ans[i]='1';
		b[x[i]]=!b[fx[i]];
		b[y[i]]=!b[fy[i]];
	}
	puts("YES");
	puts(Ans+1);
	return 0;
}
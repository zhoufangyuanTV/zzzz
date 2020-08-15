#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int x,y,c,next;
}a[310];int len,last[51];
inline void ins(int x,int y,int c)
{
	len++;
	a[len].x=x;a[len].y=y;a[len].c=c;
	a[len].next=last[x];last[x]=len;
}
int n,b[51];bool bk[51];
double ss=2500;
void dfs(int k,int x)
{
	if(x==n)
	{
		double s=0,sss=0;
		for(int i=1;i<k;i++)s+=b[i];
		s/=k-1;
		for(int i=1;i<k;i++)sss+=(b[i]-s)*(b[i]-s);
		sss/=k-1;
		if(sss<ss)ss=sss;
	}
	else if(k==20)bk[x]=false;
	else if(bk[x])
	{
		bk[x]=false;
		for(int kk=last[x];kk>0;kk=a[kk].next)
		{
			int y=a[kk].y;
			b[k]=a[kk].c;
			dfs(k+1,y);
			if(bk[y])bk[x]=true;
		}
	}
}
int main()
{
	freopen("library.in","r",stdin);
	freopen("library.out","w",stdout);
	int m;scanf("%d%d",&n,&m);
	len=0;memset(last,0,sizeof(last));
	for(int i=1;i<=m;i++)
	{
		int x,y,c;scanf("%d%d%d",&x,&y,&c);
		ins(x,y,c);
	}
	memset(bk,true,sizeof(bk));
	dfs(1,1);
	printf("%.4lf\n",ss);
	return 0;
}
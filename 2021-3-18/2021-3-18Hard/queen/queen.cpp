#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int n;
int Ansx[5100],Ansy[5100];
struct node
{
	int y;
	int l,r,u,d;
}*a;int len;
int cnt[31000];
void remove(int x)
{
	a[a[x].r].l=a[x].l;a[a[x].l].r=a[x].r;
	for(int i=a[x].d;i!=x;i=a[i].d)
	{
		for(int j=a[i].r;j!=i;j=a[j].r)
		{
			a[a[j].d].u=a[j].u;a[a[j].u].d=a[j].d;cnt[a[j].y]--;
		}
	}
}
void recover(int x)
{
	for(int i=a[x].u;i!=x;i=a[i].u)
	{
		for(int j=a[i].l;j!=i;j=a[j].l)
		{
			a[a[j].d].u=j;a[a[j].u].d=j;cnt[a[j].y]++;
		}
	}
	a[a[x].l].r=x;a[a[x].r].l=x;
}
void solve(int k)
{
	if(k==n+1)
	{
		for(int i=1;i<=n;i++)printf("%d %d\n",Ansx[i],Ansy[i]);
		delete []a;
		exit(0);
	}
	int x,f=0x3f3f3f3f;
	for(int i=a[0].r;i!=0&&i<=n*2;i=a[i].r)if(cnt[i]<f){x=i;f=cnt[i];}
	if(f==0)return ;
	remove(x);
	for(int i=a[x].d;i!=x;i=a[i].d)
	{
		int g=(i-n*6+1)/4;
		Ansx[k]=g/n+1;Ansy[k]=g%n+1;
		for(int j=a[i].r;j!=i;j=a[j].r)remove(a[j].y);
		solve(k+1);
		for(int j=a[i].l;j!=i;j=a[j].l)recover(a[j].y);
	}
	recover(x);
}
int main()
{
	freopen("queen14.in","r",stdin);
	freopen("queen14.out","w",stdout);
	scanf("%d",&n);
	a=new node[100030001];
	for(int i=0;i<=n*6-2;i++)a[i].y=a[i].u=a[i].d=i;
	for(int i=0;i<=n*6-1;i++)a[i].r=i+1;
	a[n*6-2].r=0;
	a[0].l=n*6-2;
	for(int i=1;i<=n*6-2;i++)a[i].l=i-1;
	len=n*6-2;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			int b=n+j,c=n*2+i+j-1,d=n*5+i-j-1;
			cnt[i]++;cnt[b]++;cnt[c]++;cnt[d]++;
			a[len+1].y=i;a[len+2].y=b;a[len+3].y=c;a[len+4].y=d;
			a[len+1].l=len+4;a[len+2].l=len+1;a[len+3].l=len+2;a[len+4].l=len+3;
			a[len+1].r=len+2;a[len+2].r=len+3;a[len+3].r=len+4;a[len+4].r=len+1;
			int e;
			a[len+1].u=i;a[len+1].d=e=a[i].d;a[i].d=len+1;a[e].u=len+1;
			a[len+2].u=b;a[len+2].d=e=a[b].d;a[b].d=len+2;a[e].u=len+2;
			a[len+3].u=c;a[len+3].d=e=a[c].d;a[c].d=len+3;a[e].u=len+3;
			a[len+4].u=d;a[len+4].d=e=a[d].d;a[d].d=len+4;a[e].u=len+4;
			len+=4;
		}
	}
	solve(1);
	return 0;
}
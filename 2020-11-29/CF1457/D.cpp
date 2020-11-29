#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int son[2],f;
}tr[3010000];int len;
void bt(int c,int p)
{
	int x=0;
	for(int i=29;i>=0;i--)
	{
		int cc=c>>i;
		if(tr[x].son[cc]==0)tr[x].son[cc]=++len;
		x=tr[x].son[cc];
		tr[x].f=p;
	}
}
int a[110000];
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	len=0;memset(tr,0,sizeof(tr));
	int ss=0x3f3f3f3f,s=0;
	bt(0,0);
	for(int i=1;i<n;i++)
	{
		s^=a[i];
		int sj=-1,x=0;
		for(int j=29;j>=0;j--)
		{
			int cu=s>>j&1,cr=a[i+1]>>j&1;
			if(cr==1)
			{
				if(tr[x].son[cu^1]==0)break;
				else x=tr[x].son[cu^1];
			}
			else
			{
				if(tr[x].son[cu^1]!=0)sj=mymax(sj,tr[tr[x].son[cu^1]].f);
				x=tr[x].son[cu];
			}
		}
		if(sj!=-1)ss=mymin(ss,i-sj);
		bt(s,i);
	}
	len=0;memset(tr,0,sizeof(tr));
	s=0;
	bt(0,n+1);
	for(int i=n;i>=2;i--)
	{
		s^=a[i];
		int sj=0x3f3f3f3f,x=0;
		for(int j=29;j>=0;j--)
		{
			int cu=s>>j&1,cr=a[i-1]>>j&1;
			if(cr==0)
			{
				if(tr[x].son[cu]==0)break;
				else x=tr[x].son[cu];
			}
			else
			{
				if(tr[x].son[cu]!=0)sj=mymin(sj,tr[tr[x].son[cu]].f);
				x=tr[x].son[cu^1];
			}
		}
		if(sj!=0x3f3f3f3f)ss=mymin(ss,sj-i);
		bt(s,i);
	}
	if(ss!=0x3f3f3f3f)printf("%d\n",ss-1);
	else printf("-1\n");
	return 0;
}
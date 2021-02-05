#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int son[26],f;
}tr[110000];int len;
char a[2100][110];
int f[2100];
int main()
{
	freopen("player.in","r",stdin);
	freopen("player.out","w",stdout);
	int n,m;scanf("%d%d",&n,&m);
	memset(tr[0].son,0,sizeof(tr[0].son));tr[0].f=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			scanf("%s",a[j]+1);
			int x=0;
			bool bk=true;
			for(int k=1;k<i;k++)
			{
				int c=a[j][k]-'a';
				if(tr[x].son[c]==0){bk=false;break;}
				x=tr[x].son[c];
			}
			if(bk)
			{
				f[j]=tr[x].f;
				int p=0;
				bk=true;
				for(int k=2;k<=i;k++)
				{
					int c=a[j][k]-'a';
					if(tr[p].son[c]==0){bk=false;break;}
					p=tr[p].son[c];
				}
				if(bk&&x!=p)f[j]=(f[j]+tr[p].f)%1000000007;
			}
			else
			{
				x=0;bk=true;
				for(int k=2;k<=i;k++)
				{
					int c=a[j][k]-'a';
					if(tr[x].son[c]==0){bk=false;break;}
					x=tr[x].son[c];
				}
				if(bk)f[j]=tr[x].f;
				else f[j]=0;
			}
		}
		memset(tr[0].son,0,sizeof(tr[0].son));tr[0].f=0;
		len=0;
		for(int j=1;j<=m;j++)
		{
			int x=0;
			for(int k=1;k<=i;k++)
			{
				int c=a[j][k]-'a';
				if(tr[x].son[c]==0)
				{
					len++;
					memset(tr[len].son,0,sizeof(tr[len].son));
					tr[len].f=0;
					tr[x].son[c]=len;
				}
				x=tr[x].son[c];
			}
			tr[x].f=(tr[x].f+f[j])%1000000007;
		}
	}
	int ss=0;
	for(int i=1;i<=m;i++)ss=(ss+f[i])%1000000007;
	printf("%d\n",ss);
	return 0;
}

#include<cstdio>
#include<cstring>
using namespace std;
int f[1048576];
char s[21];
int p[21];
int main()
{
	freopen("string.in","r",stdin);
	freopen("string.ans","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n;scanf("%d%s",&n,s);
		memset(f,-1,sizeof(f));
		for(int i=1;i<1<<n;i++)
		{
			int plen=0;
			for(int j=0;j<n;j++)if((i|1<<j)==i)p[++plen]=j;
			bool bk=false;
			for(int j=1;j<=plen/2;j++)if(s[p[j]]!=s[p[plen-j+1]]){bk=true;break;}
			if(bk)f[i]=1;
		}
		for(int i=1;i<1<<n;i++)
		{
			if(f[i]==-1)
			{
				int plen=0;
				for(int j=0;j<n;j++)if((i|1<<j)==i)p[++plen]=j;
				for(int l=1;l<=plen;l++)
				{
					for(int r=l;r<=plen;r++)
					{
						int x=0;
						for(int k=l;k<=r;k++)x+=1<<p[k];
						if(f[x]==1&&f[i-x]!=-1)
						{
							if(f[i]==-1||f[i-x]+1<f[i])f[i]=f[i-x]+1;
						}
					}
				}
			}
		}
		printf("%d\n",f[(1<<n)-1]);
	}
	return 0;
}
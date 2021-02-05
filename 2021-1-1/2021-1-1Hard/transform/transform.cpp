#include<cstdio>
#include<cstring>
using namespace std;
int f[4097][4097];
char a[4098],b[2050];
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("transform.in","r",stdin);
	freopen("transform.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%s%s",a+1,b+1);
		int n=strlen(a+1),m=strlen(b+1);
		for(int i=n;i>=1;i--)
		{
			f[i][i]=a[i]==b[1];
			for(int j=i+1;j<=n;j++)
			{
				int fl=f[i][j-1],fr=f[i+1][j];
				if(fl<m&&a[j]==b[fl+1])fl++;
				if(fr<m&&a[i]==b[fr+1])fr++;
				f[i][j]=mymax(fl,fr);
			}
		}
		int ss=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=i;j<=n;j++)
			{
				if(f[i][j]==m)ss++;
			}
		}
		printf("%d\n",ss);
	}
	return 0;
}
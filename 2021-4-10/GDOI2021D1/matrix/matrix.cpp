#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int a[510][510],b[510][510],c[510][510];
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
int main()
{
	freopen("matrix.in","r",stdin);
	freopen("matrix.out","w",stdout);
	int t;scanf("%d",&t);
	while(t--)
	{
		int n,m;scanf("%d%d",&n,&m);
		for(int i=1;i<n;i++)
		{
			for(int j=1;j<m;j++)scanf("%d",&b[i][j]);
		}
		for(int i=1;i<=n;i++)c[i][1]=0;
		for(int i=1;i<=m;i++)c[1][i]=0;
		for(int i=2;i<=n;i++)
		{
			for(int j=2;j<=m;j++)c[i][j]=b[i-1][j-1]-c[i-1][j]-c[i][j-1]-c[i-1][j-1];
		}
		if(m==2)
		{
			int mi=0,ma=2000000;
			for(int i=2;i<=n;i++)
			{
				if(i&1)
				{
					if(c[i][2]<0)mi=mymax(mi,-c[i][2]);
					else if(1000000<c[i][2]+1000000)ma=mymin(ma,2000000-c[i][2]);
				}
				else
				{
					if(1000000<c[i][2]-1000000)mi=mymax(mi,c[i][2]-2000000);
					else if(c[i][2]-2000000<0)ma=mymin(ma,c[i][2]);
				}
			}
			if(mi>ma)puts("NO");
			else
			{
				puts("YES");
				if(mi>1000000)a[1][1]=1000000,a[1][2]=mi-1000000;
				else a[1][1]=mi,a[1][2]=0;
				for(int i=2;i<=n;i++)
				{
					int mmi=0,mma=1000000;
					if(i&1)mmi=mymax(mmi,c[i][2]-1000000+mi);
					else mmi=mymax(mmi,c[i][2]-1000000-mi);
					a[i][1]=mmi;
				}
				for(int i=2;i<=n;i++)
				{
					for(int j=2;j<=m;j++)a[i][j]=b[i-1][j-1]-a[i-1][j]-a[i][j-1]-a[i-1][j-1];
				}
				for(int i=1;i<=n;i++)
				{
					for(int j=1;j<m;j++)printf("%d ",a[i][j]);
					printf("%d\n",a[i][m]);
				}
			}
		}
		else
		{
			for(int i=1;i<=n;i++)a[i][1]=rand()%1000001;
			for(int i=1;i<=m;i++)a[1][i]=rand()%1000001;
			bool bk=false;
			int cnt=0;
			while(bk==false&&cnt<=200000)
			{
				cnt++;
				bk=true;
				for(int i=2;i<=n;i++)
				{
					for(int j=2;j<=m;j++)
					{
						a[i][j]=b[i-1][j-1]-a[i-1][j]-a[i][j-1]-a[i-1][j-1];
						if(a[i][j]<0||a[i][j]>1000000)
						{
							bk=false;
							a[1][1]=rand()%1000001;
							a[i][1]=rand()%1000001;
							a[1][j]=rand()%1000001;
							break;
						}
					}
				}
			}
			if(bk==false)puts("NO");
			else
			{
				puts("YES");
				for(int i=1;i<=n;i++)
				{
					for(int j=1;j<m;j++)printf("%d ",a[i][j]);
					printf("%d\n",a[i][m]);
				}
			}
		}
	}
	return 0;
}

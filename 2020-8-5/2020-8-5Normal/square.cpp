#include<cstdio>
#include<cstring>
using namespace std;
int f[59049],g[59049],gg[11];
inline int mymin(int x,int y){return x<y?x:y;}
int get(){char c=getchar();while(c<'0'||c>'9')c=getchar();return c-'0';}
int main()
{
	freopen("square.in","r",stdin);
	freopen("square.out","w",stdout);
	gg[0]=1;gg[1]=3;gg[2]=9;gg[3]=27;gg[4]=81;gg[5]=243;
	gg[6]=729;gg[7]=2187;gg[8]=6561;gg[9]=19683;gg[10]=59049;
	int n,m;scanf("%d%d",&n,&m);
	while(n!=0&&m!=0)
	{
		memset(f,63,sizeof(f));
		int c;c=get();
		f[gg[m]-3+c]=0;f[gg[m]-1]=1;f[gg[m]-3+(c^1)]=2;
		for(int i=1;i<m;i++)
		{
			c=get();
			memset(g,63,sizeof(g));
			for(int j=0;j<gg[m];j++)
			{
				if(f[j]!=0x3f3f3f3f)
				{
					int gc=j/gg[i-1]%3;
					g[j-(2-(c^(gc==2)))*gg[i]]=mymin(g[j-(2-(c^(gc==2)))*gg[i]],f[j]);
					g[j-(gc-(gc^1))*(gc!=2)*gg[i-1]]=mymin(g[j-(gc-(gc^1))*(gc!=2)*gg[i-1]],f[j]+1);
					g[j-(2-(c^(gc==2)^1))*gg[i]]=mymin(g[j-(2-(c^(gc==2)^1))*gg[i]],f[j]+2);
				}
			}
			for(int j=0;j<gg[m];j++)f[j]=g[j];
		}
		for(int i=1;i<n;i++)
		{
			c=get();
			memset(g,63,sizeof(g));
			for(int j=0;j<gg[m];j++)
			{
				if(f[j]!=0x3f3f3f3f)
				{
					int gc=j%3;
					if(gc==1)g[j+1]=mymin(g[j+1],f[j]+1);
					else
					{
						g[j-(gc-(c^(gc==2)))]=mymin(g[j-(gc-(c^(gc==2)))],f[j]);
						if(gc==2)g[j]=mymin(g[j],f[j]+1);
						g[j-(gc-(c^(gc==2)^1))]=mymin(g[j-(gc-(c^(gc==2)^1))],f[j]+2);
					}
				}
			}
			for(int j=0;j<gg[m];j++)f[j]=g[j];
			for(int j=1;j<m;j++)
			{
				c=get();
				memset(g,63,sizeof(g));
				for(int k=0;k<gg[m];k++)
				{
					if(f[k]!=0x3f3f3f3f)
					{
						int gc=k/gg[j-1]%3,gcc=k/gg[j]%3;
						if(gcc==1)g[k-(gc-(gc^1))*(gc!=2)*gg[j-1]+gg[j]]=mymin(g[k-(gc-(gc^1))*(gc!=2)*gg[j-1]+gg[j]],f[k]+1);
						else
						{
							g[k-(gcc-(c^(gc==2)^(gcc==2)))*gg[j]]=mymin(g[k-(gcc-(c^(gc==2)^(gcc==2)))*gg[j]],f[k]);
							if(gcc==2)g[k-(gc-(gc^1))*(gc!=2)*gg[j-1]]=mymin(g[k-(gc-(gc^1))*(gc!=2)*gg[j-1]],f[k]+1);
							g[k-(gcc-(c^(gc==2)^(gcc==2)^1))*gg[j]]=mymin(g[k-(gcc-(c^(gc==2)^(gcc==2)^1))*gg[j]],f[k]+2);
						}
					}
				}
				for(int k=0;k<gg[m];k++)f[k]=g[k];
			}
		}
		int ss=0x3f3f3f3f;
		for(int i=0;i<gg[m];i++)
		{
			bool bk=true;
			for(int j=0;j<m;j++)
			{
				if(i/gg[j]%3==1){bk=false;break;}
			}
			if(bk)ss=mymin(ss,f[i]);
		}
		printf("%d\n",ss);
		scanf("%d%d",&n,&m);
	}
	return 0;
}
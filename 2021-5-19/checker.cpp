#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
FILE *fin,*fout;
void WA(int t)
{
	FILE *result=fopen("result.txt","w");
	fprintf(result,"WA %d\n",t);
	printf("WA %d\n",t);
	fclose(fin);
	fclose(fout);
	fclose(result);
	exit(1);
}
void AC()
{
	FILE *result=fopen("result.txt","w");
	fprintf(result,"AC\n");
	printf("AC\n");
	fclose(fin);
	fclose(fout);
	fclose(result);
	exit(0);
}
char M[510][510];
int f[310000];
int findfa(int x){return x!=f[x]?f[x]=findfa(f[x]):x;}
int main()
{
	fin=fopen("M.in","r");
	fout=fopen("M.out","r");
	int t;fscanf(fin,"%d",&t);
	for(int tt=1;tt<=t;tt++)
	{
		int n,m;fscanf(fin,"%d%d",&n,&m);
		int cnt1,cnt2,cnt3;fscanf(fin,"%d%d%d",&cnt1,&cnt2,&cnt3);
		for(int i=1;i<=n;i++)
		{
			fscanf(fout,"%s",M[i]+1);
		}
		int x1,y1,x2,y2,x3,y3;
		fscanf(fin,"%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(M[i][j]=='A')cnt1--;
				else if(M[i][j]=='B')cnt2--;
				else if(M[i][j]=='C')cnt3--;
				else WA(tt);
			}
		}
		if(cnt1!=0||cnt2!=0||cnt3!=0)WA(tt);
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				f[(i-1)*m+j]=(i-1)*m+j;
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				int x,y;
				if(i==1)x=n;
				else x=i-1;
				if(j==1)y=m;
				else y=j-1;
				if(M[x][j]==M[i][j])
				{
					int fx=findfa((i-1)*m+j),fy=findfa((x-1)*m+j);
					f[fx]=fy;
				}
				if(M[i][y]==M[i][j])
				{
					int fx=findfa((i-1)*m+j),fy=findfa((i-1)*m+y);
					f[fx]=fy;
				}
			}
		}
		int ss=0;
		for(int i=1;i<=n*m;i++)
		{
			if(f[i]==i)ss++;
		}
		if(ss>3)WA(tt);
		if(M[x1][y1]!='A'||M[x2][y2]!='B'||M[x3][y3]!='C')WA(tt);
	}
	AC();
	return 0;
}
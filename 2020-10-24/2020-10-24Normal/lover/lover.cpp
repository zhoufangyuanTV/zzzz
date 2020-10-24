#pragma GCC optimize("Ofast")
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
long long f[18][55][37][19][19],g[55][37][19][19],G[55][37][19][19],three[37],five[19],seven[19];
inline int mymin(int x,int y){return x<y?x:y;}
int main()
{
	freopen("lover.in","r",stdin);
	freopen("lover.out","w",stdout);
	three[0]=1;for(int i=1;i<=36;i++)three[i]=three[i-1]*3;
	five[0]=1;for(int i=1;i<=18;i++)five[i]=five[i-1]*5;
	seven[0]=1;for(int i=1;i<=18;i++)seven[i]=seven[i-1]*7;
	long long n,m;scanf("%lld%lld",&n,&m);
	if(n==1000000000000000000ll)n--;
	long long dg=0,gs=1;
	while(gs<=n/10)dg++,gs=gs*10;
	memset(f,0,sizeof(f));f[0][0][0][0][0]=1;
	memset(g,0,sizeof(g));
	for(register int d=1;d<=dg;d++)
	{
		for(register int i=0;i<=d*3;i++)
		{
			for(register int j=0;j<=(d*3-i)*2/3;j++)
			{
				for(register int k=0;k<=((d*3-i)*2/3-j)/2;k++)
				{
					for(register int l=0;l<=((d*3-i)*2/3-j)/2-k;l++)
					{
						f[d][i][j][k][l]+=f[d-1][i][j][k][l];
						if(i>0)f[d][i][j][k][l]+=f[d-1][i-1][j][k][l];
						if(j>0)f[d][i][j][k][l]+=f[d-1][i][j-1][k][l];
						if(i>1)f[d][i][j][k][l]+=f[d-1][i-2][j][k][l];
						if(k>0)f[d][i][j][k][l]+=f[d-1][i][j][k-1][l];
						if(i>0&&j>0)f[d][i][j][k][l]+=f[d-1][i-1][j-1][k][l];
						if(l>0)f[d][i][j][k][l]+=f[d-1][i][j][k][l-1];
						if(i>2)f[d][i][j][k][l]+=f[d-1][i-3][j][k][l];
						if(j>1)f[d][i][j][k][l]+=f[d-1][i][j-2][k][l];
						f[d][i][j][k][l]%=998244353;
						g[i][j][k][l]=(g[i][j][k][l]+f[d][i][j][k][l])%998244353;
					}
				}
			}
		}
	}
	int a=0,b=0,c=0,d=0,dn=dg+1;
	while(gs>0)
	{
		int ci=n/gs;
		for(register int di=1;di<ci;di++)
		{
			int aa=0,bb=0,cc=0,dd=0;
			if(di==2)aa++;
			else if(di==3)bb++;
			else if(di==4)aa+=2;
			else if(di==5)cc++;
			else if(di==6)aa++,bb++;
			else if(di==7)dd++;
			else if(di==8)aa+=3;
			else if(di==9)bb+=2;
			for(register int i=0;i<=dg*3;i++)
			{
				for(register int j=0;j<=(dg*3-i)*2/3;j++)
				{
					for(register int k=0;k<=((dg*3-i)*2/3-j)/2;k++)
					{
						for(register int l=0;l<=((dg*3-i)*2/3-j)/2-k;l++)
						{
							g[a+aa+i][b+bb+j][c+cc+k][d+dd+l]=(g[a+aa+i][b+bb+j][c+cc+k][d+dd+l]+f[dg][i][j][k][l])%998244353;
						}
					}
				}
			}
		}
		if(ci==0)break;
		if(ci==2)a++;
		else if(ci==3)b++;
		else if(ci==4)a+=2;
		else if(ci==5)c++;
		else if(ci==6)a++,b++;
		else if(ci==7)d++;
		else if(ci==8)a+=3;
		else if(ci==9)b+=2;
		n=n%gs;gs=gs/10;dg--;
	}
	if(gs==0)g[a][b][c][d]++;
	long long ss=0;
	for(register int i=0;i<=54;i++)
	{
		for(register int j=0;j<=36;j++)
		{
			for(register int k=0;k<=18;k++)
			{
				for(register int l=0;l<=18;l++)
				{
					G[i][j][k][l]=g[i][j][k][l];
					if(i>0)G[i][j][k][l]=(G[i][j][k][l]+G[i-1][j][k][l])%998244353;
				}
			}
		}
	}
	register int i,j,k,l,ii,jj,kk,ll;
	register long long mj,mk,ml;
	for(i=0;i<=dn*3;i++)
	{
		for(j=0;j<=(dn*3-i)*2/3;j++)
		{
			for(k=0;k<=((dn*3-i)*2/3-j)/2;k++)
			{
				for(l=0;l<=((dn*3-i)*2/3-j)/2-k;l++)
				{
					if(g[i][j][k][l]>0)
					{
						for(jj=0;jj<=dn*2;jj++)
						{
							mj=m/three[mymin(j,jj)];
							if(mj==0)break;
							for(kk=0;kk<=(dn*2-jj)/2;kk++)
							{
								mk=mj/five[mymin(k,kk)];
								if(mk==0)break;
								for(ll=0;ll<=(dn*2-jj)/2-kk;ll++)
								{
									ml=mk/seven[mymin(l,ll)];
									if(ml==0)break;
									ii=log2(ml);
									if(ii>=0)ss=(ss+g[i][j][k][l]*G[ii<i?ii:54][jj][kk][ll])%998244353;
								}
							}
						}
					}
				}
			}
		}
	}
	printf("%lld\n",ss);
	return 0;
}
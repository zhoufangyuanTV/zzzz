#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int n;
double A[310][310],B[310][310],ruta[310][310],R[310];
void Gauss()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i==j)continue;
			ruta[j][i]=-A[j][i]/A[i][i];
			for(int k=1;k<i;k++)ruta[j][k]+=ruta[j][i]*ruta[i][k];
			for(int k=i;k<=n;k++)A[j][k]+=ruta[j][i]*A[i][k];
		}
	}
}
vector<int> V[310];
bool b[310];
int match[310],mp[310];
bool find_muniu(int x)
{
	for(int y:V[x])
	{
		if(b[y]==true)
		{
			b[y]=false;
			if(match[y]==0||find_muniu(match[y])==true)
			{
				match[y]=x;mp[x]=y;
				return true;
			}
		}
	}
	return false;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)scanf("%lf",&A[i][j]);
	}
	for(int i=1;i<=n;i++)ruta[i][i]=1;
	Gauss();
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)R[j]=0;
		for(int j=1;j<=n;j++)
		{
			scanf("%lf",&B[i][j]);
			double r=B[i][j]/A[j][j];
			for(int k=1;k<=n;k++)R[k]+=r*ruta[j][k];
		}
		for(int j=1;j<=n;j++)
		{
			if(fabs(R[j])>1e-2)
			{
				V[j].push_back(i);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		memset(b,true,sizeof(b));
		if(find_muniu(i)==false)
		{
			printf("NIE\n");
			return 0;
		}
	}
	printf("TAK\n");
	memset(b,true,sizeof(b));
	for(int i=1;i<=n;i++)
	{
		for(int j:V[i])
		{
			if(j==mp[i])break;
			if(b[j]==false)continue;
			b[j]=false;match[mp[i]]=0;
			if(find_muniu(match[j])==false)
			{
				for(int k=1;k<=n;k++)
				{
					if(match[k]>i)b[k]=true;
				}
				match[mp[i]]=i;
				b[j]=true;
			}
			else
			{
				for(int k=1;k<=n;k++)
				{
					if(match[k]>i)b[k]=true;
				}
				match[j]=i;mp[i]=j;
				break;
			}
		}
		b[mp[i]]=false;
	}
	for(int i=1;i<=n;i++)printf("%d\n",mp[i]);
	return 0;
}
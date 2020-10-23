#include<cstdio>
#include<cstring>
using namespace std;
int f[21][2097152];
char s[1048577];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	memset(f,0,sizeof(f));
	for(int i=0;i<=n;i++)
	{
		scanf("%s",s);
		for(int j=0;j<1<<i;j++)f[0][(1<<i)+j]=s[j]-'0';
	}
	int s=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<1<<i;j++)
		{
			for(int k=i;k<=n;k++)
			{
				for(int l=0;l<1<<k-i;l++)
				{
					int kk=0;
					while(i+kk<k&&l&1<<kk)kk++;
					if(i+kk<k)f[i+1][(1<<k-kk)+(j|l>>kk<<i)]+=f[i][(1<<k)+(j|l<<i)];
					kk=0;
					while(i+kk<k&&~l&1<<kk)kk++;
					if(i+kk<k)f[i+1][(1<<k-kk)+(j|l>>kk<<i)]+=f[i][(1<<k)+(j|l<<i)];
				}
			}
		}
	}
	for(int i=n;i>=0;i--)
	{
		for(int j=0;j<1<<i;j++)
		{
			int ss=s;
			for(int k=i;k<=n;k++)
			{
				for(int l=0;l<1<<k-i;l++)ss+=f[i][(1<<k)+(j|l<<i)];
			}
			if(m<=ss)
			{
				for(int k=i-1;k>=0;k--)putchar((j>>k&1)+'0');
				return 0;
			}
		}
	}
}
#include<cstdio>
#include<cstring>
using namespace std;
int a[51000],b[110],h[110];
int plen,p[51000];
int main(int argc,char* argv[])
{
	FILE *fin=fopen(argv[1],"r"),*fout=fopen(argv[2],"r");
	int n,m,X,A;fscanf(fin,"%d%d%d%d",&n,&m,&X,&A);
	for(int i=1;i<=n;i++)fscanf(fin,"%d",&a[i]);
	for(int i=1;i<=m;i++)fscanf(fin,"%d%d",&b[i],&h[i]);
	b[0]=0;
	int s;fscanf(fout,"%d%d",&s,&plen);
	for(int i=1;i<=plen;i++)fscanf(fout,"%d",&p[i]);
	for(int i=1;i<=n;i++)
	{
		int sss=A-i*X;
		for(int j=1;j<=plen;j++)if(p[j]<=i)sss+=a[p[j]]+X;
		if(sss<0)
		{
			puts("Wrong Answer!");
			return 0;
		}
	}
	int ss=0;
	for(int i=1;i<=m;i++)
	{
		int sss=b[i]-b[i-1];
		for(int j=1;j<=plen;j++)if(b[i-1]<p[j]&&p[j]<=b[i])sss--;
		if(sss>=h[i])ss++;
	}
	if(s==ss)puts("Accept!");
	else puts("Wrong Answer!");
	return 0;
}
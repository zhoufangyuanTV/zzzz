#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
long double f[110],jc[110];
int main()
{
	jc[0]=1;
	for(int i=1;i<=10;i++)jc[i]=jc[i-1]*i;
	int n;scanf("%d",&n);
	for(int l=1;l<=n;l++)
	{
		for(int r=l;r<=n;r++)
		{
			if(2*r-l+1<=n)for(int i=l;i<=r;i++)f[i]+=jc[2*r-2*l]/jc[2*r-2*l+1+(l>1)];
			if(2*l-r-2>=1)for(int i=l;i<=r;i++)f[i]+=jc[2*r-2*l+1]/jc[2*r-2*l+2+(r<n)];
		}
	}
	for(int i=1;i<n;i++)printf("%Lf ",f[i]);
	printf("%Lf\n",f[n]);
	return 0;
}
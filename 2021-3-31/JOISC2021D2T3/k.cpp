#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
long double f[410];
int main()
{
	f[0]=1;
	for(int i=1;i<=400;i++)
	{
		f[i]=0;
		for(int j=0;j<i;j++)f[i]+=f[j]*f[i-j-1];
		printf("%Lf %Lf\n",log2(f[i]),f[i]);
	}
	return 0;
}
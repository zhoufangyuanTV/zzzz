#include<cstdio>
#include<cstring>
using namespace std;
int x[310000],t[310000];
bool b[310000];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&x[i]);
	int ss=0;
	for(int j=1;j<=n;j++)
	{
		scanf("%d",&t[j]);
		ss=ss+t[j]/(2*m);
		t[j]=t[j]%(2*m);
		if(t[j]==0)t[j]+=2*m,ss--;
	}
	int i=1,j=1;
	memset(b,false,sizeof(b));
	while(j<n)
	{
		while(i<=n&&(t[i]>2*x[i]||b[i]))i++;
		if(j<=i)j=i+1;
		while(j<=n&&(t[j]>2*m-2*x[j]||b[j]))j++;
		if(j<=n)b[i]=b[j]=true,ss--;
	}
	if(b[n]==false&&t[n]<=2*m-2*x[n])ss--;
	ss=ss+n+1;
	printf("%lld\n",1ll*ss*2*m);
	return 0;
}
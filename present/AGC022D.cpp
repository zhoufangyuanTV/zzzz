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
		if(t[j]==0)j--,n--;
	}
	memset(b,false,sizeof(b));
	int i=1,j=n;bool bk=true;
	while(i<j)
	{
		while(i<j&&t[i]>2*x[i])i++;
		while(i<j&&t[j]>2*m-2*x[j])bk=false,j--;
		if(i<j)b[i]=true,b[j]=true,i++,j--,ss--;
	}
	i=1;int jj=n;
	while(i<j&&t[i]>2*x[i])i++;
	while(i<j&&t[j]>2*m-2*x[j]||b[j]==true)j--;
	if((i>1||bk)&&i<j)ss--;
	ss=ss+n+1;
	printf("%lld\n",1ll*ss*2*m);
	return 0;
}
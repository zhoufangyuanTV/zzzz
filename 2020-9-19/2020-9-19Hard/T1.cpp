#include<cstdio>
#include<cstring>
/*#include<utility>*/
using namespace std;
/*
struct node
{
	int a[1100],len;
	node(){memset(a,0,sizeof(a));len=1;}
};
bool operator<(node x,node y)
{
	if(x.len!=y.len)return x.len<y.len;
	for(int i=x.len;i>=1;i--)
	{
		if(x.a[i]!=y.a[i])return x.a[i]<y.a[i];
	}
	return false;
}
inline int mymax(int x,int y){return x>y?x:y;}
node operator+(node x,node y)
{
	node z;
	z.len=mymax(x.len,y.len);
	for(int i=1;i<=z.len;i++)z.a[i]=x.a[i]+y.a[i];
	for(int i=1;i<=z.len;i++)
	{
		z.a[i+1]+=z.a[i]/10;
		z.a[i]=z.a[i]%10;
	}
	int i=z.len;
	while(z.a[i+1]>0)
	{
		i++;
		z.a[i+1]+=z.a[i]/10;
		z.a[i]=z.a[i]%10;
	}
	while(i>1&&z.a[i]==0)i--;
	z.len=i;
	return z;
}
node operator*(node x,node y)
{
	node z;
	z.len=x.len+y.len-1;
	for(int i=1;i<=x.len;i++)
	{
		for(int j=1;j<=y.len;j++)
		{
			z.a[i+j-1]+=x.a[i]*y.a[j];
		}
	}
	for(int i=1;i<=z.len;i++)
	{
		z.a[i+1]+=z.a[i]/10;
		z.a[i]=z.a[i]%10;
	}
	int i=z.len;
	while(z.a[i+1]>0)
	{
		i++;
		z.a[i+1]+=z.a[i]/10;
		z.a[i]=z.a[i]%10;
	}
	while(i>1&&z.a[i]==0)i--;
	z.len=i;
	return z;
}
char s[1100];*/
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		long long a,b,l;scanf("%lld%lld%lld",&a,&b,&l);
		if(a<0)a=-a;if(b<0)b=-b;l--;
		if((a+b)%2==0)printf("%lld\n",(a+b)/2/l+((a+b)/2%l!=0));
		else printf("Poor MLG!\n");
	}
}
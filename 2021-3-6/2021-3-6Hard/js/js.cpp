#include<cstdio>
#include<cstring>
using namespace std;
int a[1100],d[1100],ss[1100];
int main()
{
	freopen("js.in","r",stdin);
	freopen("js.out","w",stdout);
	int n;unsigned s;scanf("%d%u",&n,&s);
	for(int i=n;i>=1;i--)
	{
		d[i]=(s>>10)%10;
		s=747796405*s-1403630843;
	}
	memset(ss,0,sizeof(ss));
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=n;j++)a[j]=d[j];
		for(int j=n;j>=i;j--)
		{
			int p=a[j];bool bk=true;
			for(int k=j;k>=j-i+1;k--)
			{
				if(a[k]<p){bk=false;break;}
				else if(a[k]>p)break;
			}
			if(bk==false)p--;
			ss[j-i+1]=ss[j-i+1]+p;
			for(int k=j-i+1;k<=j;k++)
			{
				a[k]-=p;
				if(a[k]<0)a[k+1]--,a[k]+=10;
			}
		}
	}
	int len=0;
	while(ss[len+1]>0)
	{
		len++;
		ss[len+1]+=ss[len]/10;
		ss[len]%=10;
	}
	for(int i=len;i>=1;i--)putchar(ss[i]+'0');
	putchar('\n');
	return 0;
}
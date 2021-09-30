#include<cstdio>
#include<cstring>
using namespace std;
char a[1100],s[1100];
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int n;scanf("%d%s",&n,a);
	int ss=0;
	for(int i=0;i<1<<n;i++)
	{
		for(int j=0;j<n;j++)s[j]='0'+(i>>j&1);
		bool bk=true;
		for(int j=0;j<n;j++)
		{
			if(a[j]!='?'&&a[j]!=s[j]){bk=false;break;}
		}
		if(bk==false)continue;
		for(int j=1;j<n;j++)
		{
			int sss=0;
			for(int k=0;k<2*n;k++)
			{
				sss+=s[(k+j)%n]-s[k%n];
				if(sss<0)sss=0;
				if(sss==2){bk=false;break;}
			}
			if(bk==false)break;
		}
		if(bk)ss++;
	}
	printf("%d\n",ss);
	return 0;
}
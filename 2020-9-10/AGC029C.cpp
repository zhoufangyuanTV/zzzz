#include<cstdio>
#include<cstring>
using namespace std;
int n,a[210000];
struct node
{
	int x,p;
}sta[210000];int top;
bool pand(int x)
{
	sta[0].p=0;top=1;
	sta[1].x=0;sta[1].p=a[1];
	for(int i=2;i<=n;i++)
	{
		if(sta[top].p<a[i])
		{
			if(sta[top].x==0)sta[top].p=a[i];
			else sta[++top]=(node){0,a[i]};
		}
		else
		{
			if(x==1)return false;
			while(sta[top].p>a[i])top--;
			if(sta[top].p!=a[i])sta[++top]=(node){0,a[i]};
			sta[top].x++;
			while(sta[top].x==x)
			{
				if(sta[top-1].p!=sta[top].p-1)
				{
					sta[top].x=1;
					sta[top].p=sta[top].p-1;
				}
				else
				{
					top--;
					if(top==0)return false;
					sta[top].x++;
				}
			}
			if(sta[top].p!=a[i])sta[++top]=(node){0,a[i]};
		}
	}
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(pand(mid))r=mid;
		else l=mid+1;
	}
	printf("%d\n",r);
	return 0;
}
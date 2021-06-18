#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110000],b[110000],c[110000],e[110000];
bool d[110000];
int Ans[110000],len;
int A[110000],L;
int main()
{
	freopen("equipment.in","r",stdin);
	freopen("equipment.out","w",stdout);
	int n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	memset(e,-1,sizeof(e));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a[i],&b[i]);
		e[a[i]]=i;
	}
	memset(d,false,sizeof(d));
	len=0;
	for(int i=m;i>=1;i--)
	{
		if(len==k)break;
		if(d[i]==false)
		{
			if(c[a[i]]<c[b[i]])
			{
				int x=i;L=0;
				while(x!=-1&&d[x]==false)
				{
					A[++L]=x;
					d[x]=true;
					swap(a[x],b[x]);
				    swap(x,e[a[x]]);
				}
				if(x!=-1||len+L>k)
				{
					e[a[A[L]]]=x;
					for(int i=L;i>=1;i--)
					{
						swap(a[A[i]],b[A[i]]);
						if(x==-1&&len+L-i+1<=k)d[A[i]]=false;
						e[a[A[i]]]=A[i];
					}
				}
				else
				{
					e[b[i]]=-1;
					len+=L;
					for(int i=L;i>=1;i--)Ans[len-i+1]=A[i];
				}
			}
			else if(c[a[i]]>c[b[i]])d[i]=true;
		}
	}
	printf("%d\n",len);
	for(int i=1;i<=len;i++)printf("%d\n",Ans[i]);
	return 0;
}

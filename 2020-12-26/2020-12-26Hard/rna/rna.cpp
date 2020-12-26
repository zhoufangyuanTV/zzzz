#include<cstdio>
#include<cstring>
using namespace std;
int fa[610000],dep[610000],fail[610000],a[610000];
long long f[610000],fc[610000];
char opt[11];
bool b[610000];
int main()
{
	freopen("rna.in","r",stdin);
	freopen("rna.out","w",stdout);
	fc[1]=1;
	for(int i=2;i<=600010;i++)fc[i]=(998244353-fc[998244353%i])*(998244353/i)%998244353;
	int id;scanf("%d",&id);
	if(id==1||id==2)return 0;
	int n,l,q,enc;scanf("%d%d%d%d",&n,&l,&q,&enc);
	memset(b,false,sizeof(b));
	for(int i=1;i<l;i++)
	{
		scanf("%d",&a[q+i]);
		if(i==1)fa[q+i]=-1,fail[q+i]=-1,dep[q+i]=1,f[q+i]=2*n;
		else
		{
			fa[q+i]=q+i-1;
			dep[q+i]=dep[fa[q+i]]+1;
			int k=fail[q+i-1],x=q+i,y=q+i;
			while(fa[x]!=k)x=fa[x];
			while(a[x]!=a[q+i])
			{
				if(b[a[x]]==false)
				{
					b[a[x]]=true;
					f[]+=x;
				}
				if(k==-1){x=-1;break;}
				k=fail[k];
				while(fa[x]!=k)x=fa[x];
			}
			fail[q+i]=x;
		}
	}
	scanf("%d",&a[0]);
	if(l==1)fa[0]=-1,fail[0]=-1,dep[0]=1,f[0]=2*n;
	else
	{
		fa[0]=q+l-1;
		dep[0]=dep[fa[0]]+1;
		int k=fail[q+l-1],x=0;
		while(fa[x]!=k)x=fa[x];
		while(a[x]!=a[0])
		{
			if(k==-1){x=-1;break;}
			k=fail[k];
			while(fa[x]!=k)x=fa[x];
		}
		fail[0]=x;
	}
	int tot=1,lastans=0;
	while(q--)
	{
		int ff,g;scanf("%s%d%d",opt+1,&ff,&g);
		if(opt[1]=='Q')
		{
			g=(g+lastans*enc)%(2*n);
			a[tot]=g;
			fa[tot]=ff;
			dep[tot]=dep[fa[tot]]+1;
			int k=fail[ff],x=tot;
			while(fa[x]!=k)x=fa[x];
			while(a[x]!=a[tot])
			{
				if(k==-1){x=-1;break;}
				k=fail[k];
				while(fa[x]!=k)x=fa[x];
			}
			fail[tot]=x;
			tot++;
		}
		else
		{
			g=(g+lastans*enc)%(dep[ff]+1);
			int x=ff;long long ss=0;
			while(dep[x]!=g)
			{
				ss=ss+f[x];
				x=fa[x];
			}
			printf("%lld\n",ss);
		}
	}
	return 0;
}
#include<cstdio>
#include<cstring>
#include<set>
#include<algorithm>
using namespace std;
struct node
{
	int x,p;
}z[210000];
inline bool cmp(node x,node y){return x.x<y.x;}
int f[210000][17],a[110000],b[110000];
inline int mymin(int x,int y){return x<y?x:y;}
struct qj{int l,r,c;};
struct sp{bool operator()(const qj &x,const qj &y)const{return x.l<y.l;}};
set<qj,sp> S;
int qiu(int l,int r)
{
	int x=l,ss=0;
	for(int i=16;i>=0;i--)
	{
		if(f[x][i]<=r)
		{
			x=f[x][i];
			ss+=1<<i;
		}
	}
	return ss;
}
int Ans[110000],len;
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&z[i*2-1].x,&z[i*2].x);
	for(int i=1;i<=n*2;i++)z[i].p=i;
	sort(z+1,z+n*2+1,cmp);
	int zz=0;z[0].x=0;
	for(int i=1;i<=n*2;i++)
	{
		if(z[i-1].x<z[i].x)zz++;
		if(z[i].p&1)a[z[i].p/2+1]=zz;
		else b[z[i].p/2]=zz;
	}
	memset(f,63,sizeof(f));
	for(int i=1;i<=n;i++)f[a[i]][0]=mymin(f[a[i]][0],b[i]);
	for(int i=zz-1;i>=1;i--)f[i][0]=mymin(f[i][0],f[i+1][0]);
	for(int j=1;j<17;j++)
	{
		for(int i=1;i<=zz;i++)
		{
			int k=f[i][j-1];
			if(k<=zz)f[i][j]=f[k][j-1];
		}
	}
	int ss=qiu(1,zz);
	if(ss<m)
	{
		puts("-1");
		return 0;
	}
	S.insert({1,zz,ss});
	len=0;
	for(int i=1;i<=n;i++)
	{
		set<qj,sp>::iterator it=S.upper_bound({a[i],b[i],1});
		it--;
		int l=it->l,r=it->r,c=it->c;
		if(l<=a[i]&&b[i]<=r)
		{
			int lc=qiu(l,a[i]),rc=qiu(b[i],r);
			if(ss-c+lc+rc+1>=m)
			{
				ss=ss-c+lc+rc+1;
				Ans[++len]=i;
				if(len==m)break;
				S.erase(it);
				if(l<a[i])S.insert({l,a[i],lc});
				if(b[i]<r)S.insert({b[i],r,rc});
			}
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}
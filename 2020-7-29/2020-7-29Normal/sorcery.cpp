#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int son[26],fail;
	bool last;
}tr[110];int len;
char a[110];
void bt(int x)
{
	int n=strlen(a+1);
	for(int i=1;i<=n;i++)
	{
		int c=a[i]-'a';
		if(tr[x].son[c]==0)tr[x].son[c]=++len;
		x=tr[x].son[c];
	}
	tr[x].last=true;
}
int list[110];
void makefail()
{
	int head=1,tail=1;
	for(int i=0;i<26;i++)
	{
		int y=tr[0].son[i];
		if(y!=0)list[tail++]=y;
	}
	while(head<tail)
	{
		int x=list[head];
		for(int i=0;i<26;i++)
		{
			int y=tr[x].son[i];
			if(y==0)tr[x].son[i]=tr[tr[x].fail].son[i];
			else
			{
				list[tail++]=y;
				tr[y].fail=tr[tr[x].fail].son[i];
				if(tr[tr[y].fail].last)tr[y].last=true;
			}
		}
		head++;
	}
}
int ac(int x,char str[])
{
	int n=strlen(str+1);
	for(int i=1;i<=n;i++)
	{
		int c=str[i]-'a';
		x=tr[x].son[c];
		if(tr[x].last)return -1;
	}
	return x;
}
char str[110][110];
int stl[110];
int to[110][110];
int f[210][110];
struct matrix
{
	int n,m,a[210][210];
}A,B,C,D,S;
matrix operator*(matrix x,matrix y)
{
	matrix z;z.n=x.n;z.m=y.m;
	for(int i=0;i<=z.n;i++)
	{
		for(int j=0;j<=z.m;j++)
		{
			z.a[i][j]=0;
			for(int k=0;k<=x.m;k++)
			{
				z.a[i][j]=(z.a[i][j]+(long long)x.a[i][k]*y.a[k][j])%1000000007;
			}
		}
	}
	return z;
}
int one[110],two[110];
int main()
{
	freopen("sorcery.in","r",stdin);
	freopen("sorcery.out","w",stdout);
	int n,m,l;scanf("%d%d%d",&n,&m,&l);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str[i]+1);
		stl[i]=strlen(str[i]+1);
	}
	len=0;memset(tr,0,sizeof(tr));
	for(int i=1;i<=m;i++)
	{
		scanf("%s",a+1);
		bt(0);
	}
	makefail();
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=len;j++)to[i][j]=ac(j,str[i]);
	}
	if(l<=100)
	{
		memset(f,0,sizeof(f));f[0][0]=1;
		for(int i=0;i<=l;i++)
		{
			for(int j=1;j<=n;j++)
			{
				if(i+stl[j]>l)continue;
				for(int k=0;k<=len;k++)
				{
					if(to[j][k]!=-1)
					{
						f[i+stl[j]][to[j][k]]=(f[i+stl[j]][to[j][k]]+f[i][k])%1000000007;
					}
				}
			}
		}
		int ss=0;
		for(int i=0;i<=len;i++)ss=(ss+f[l][i])%1000000007;
		printf("%d\n",ss);
	}
	else
	{
		one[0]=two[0]=0;
		for(int i=1;i<=n;i++)
		{
			if(stl[i]==1)one[++one[0]]=i;
			else two[++two[0]]=i;
		}
		A.n=len;A.m=len;
		for(int i=1;i<=one[0];i++)
		{
			for(int j=0;j<=len;j++)
			{
				if(to[one[i]][j]!=-1)
				{
					A.a[j][to[one[i]][j]]=(A.a[j][to[one[i]][j]]+1)%1000000007;
				}
			}
		}
		B.n=len;B.m=len;
		for(int i=1;i<=two[0];i++)
		{
			for(int j=0;j<=/*len*/0;j++)
			{
				if(to[two[i]][j]!=-1)
				{
					B.a[j][to[two[i]][j]]=(B.a[j][to[two[i]][j]]+1)%1000000007;
				}
			}
		}
		C.n=len*2+1;C.m=len*2+1;
		for(int i=0;i<=len;i++)
		{
			for(int j=0;j<=len;j++)
			{
				C.a[i+len+1][j]=(C.a[i+len+1][j]+A.a[i][j])%1000000007;
			}
		}
		for(int i=0;i<=len;i++)
		{
			for(int j=0;j<=len;j++)
			{
				C.a[i][j]=(C.a[i][j]+B.a[i][j])%1000000007;
				//C.a[i+len+1][j+len+1]=(C.a[i+len+1][j+len+1]+B.a[i][j])%1000000007;
			}
		}
		D=A*A;
		for(int i=0;i<=len;i++)
		{
			for(int j=0;j<=len;j++)
			{
				//C.a[i+len+1][j+len+1]=(C.a[i+len+1][j+len+1]+D.a[i][j])%1000000007;
			}
		}
		D=B*A;
		for(int i=0;i<=len;i++)
		{
			for(int j=0;j<=len;j++)
			{
				//C.a[i][j+len+1]=(C.a[i][j+len+1]+D.a[i][j])%1000000007;
			}
		}
		S.n=0;S.m=2*len+1;
		S.a[0][0]=1;
		for(int i=0;i<=len;i++)S.a[0][i+len+1]=A.a[0][i];
		int k=l/2;
		while(k>0)
		{
			if(k&1)S=S*C;
			C=C*C;
			k>>=1;
		}
		int ss=0;
		if(l&1)for(int i=0;i<=len;i++)ss=(ss+S.a[0][i+len+1])%1000000007;
		else for(int i=0;i<=len;i++)ss=(ss+S.a[0][i])%1000000007;
		printf("%d\n",ss);
	}
	return 0;
}

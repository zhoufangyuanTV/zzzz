#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
#define PI 3.14159263538979323846
struct complex
{
	double real,image;
	complex(double r=0,double i=0){real=r;image=i;}
};
inline complex operator+(complex x,complex y){return (complex){x.real+y.real,x.image+y.image};}
inline complex operator-(complex x,complex y){return (complex){x.real-y.real,x.image-y.image};}
inline complex operator*(complex x,complex y){return (complex){x.real*y.real-x.image*y.image,x.real*y.image+x.image*y.real};}
struct poly
{
	complex a[262144];
	void fft(int);
}A,B;int LEN;
int r[262144];
complex w[262144];
void poly::fft(int type)
{
	for(int i=0;i<LEN;i++)
	{
		if(i<r[i])
		{
			complex t=a[i];
			a[i]=a[r[i]];
			a[r[i]]=t;
		}
	}
	w[0]=(complex){1,0};
	for(int i=1;i<LEN;i<<=1)
	{
		complex wi(type*cos(PI/i),type*sin(PI/i));
		for(int j=i-2;j>=2;j-=2)w[j]=w[j>>1];
		for(int j=1;j<i;j+=2)w[j]=w[j-1]*wi;
		for(int j=0;j<LEN;j+=i<<1)
		{
			for(int k=0;k<i;k++)
			{
				complex ak=a[j+k],awk=w[k]*a[i+j+k];
				a[j+k]=ak+awk;a[i+j+k]=ak-awk;
			}
		}
	}
}
struct node
{
	int x,y,next;
}a[210000];int len,last[110000];
inline void ins(int x,int y)
{
	len++;a[len].x=x;a[len].y=y;
	a[len].next=last[x];last[x]=len;
}
int c[110000];
int z,in[110000],out[110000];
int block,blk[110000];
int cnt,ce[110000];
int sta[110000],top;
vector<int> pos[110000],mem[110000];
void dfs(int x,int fa)
{
	in[x]=++z;
	int t=top;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)
		{
			dfs(y,x);
			if(block<=top-t)
			{
				ce[++cnt]=x;
				pos[x].push_back(cnt);
				while(top>t)
				{
					blk[sta[top]]=cnt;
					mem[cnt].push_back(sta[top]);
					top--;
				}
			}
		}
	}
	if(x!=1)sta[++top]=x;
	out[x]=z;
}
long long ss=0;
int ctt[130000];
void dfs1(int x,int fa,int grand)
{
	if(x!=grand)
	{
		int gx=c[grand]-c[x];
		if(-60000<=gx&&gx<=60000)ss+=ctt[gx+60000];
	}
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(blk[y]==blk[x]&&y!=fa)dfs1(y,x,grand);
	}
}
void dfs2(int x,int fa)
{
	dfs1(x,fa,x);
	ctt[c[x]+60000]++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(blk[y]==blk[x]&&y!=fa)dfs2(y,x);
	}
	ctt[c[x]+60000]--;
}
int ttc[110][130000];
vector<int> e[110000];
void dfs3(int x,int fa)
{
	ctt[c[x]+60000]++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(blk[y]!=blk[x]&&y!=fa)dfs2(y,x);
	}
	ttc[blk[x]][c[x]+60000]++;
	for(int k=last[x];k>0;k=a[k].next)
	{
		int y=a[k].y;
		if(y!=fa)dfs3(y,x);
	}
	if(pos[x].size()>0)
	{
		for(int i=0;i<=120000;i++)A.a[i]=complex(ctt[i],0);
		for(int i=120001;i<LEN;i++)A.a[i]=complex(0,0);
		A.fft(1);
	}
	for(int i=0;i<pos[x].size();i++)
	{
		int y=pos[x][i];
		for(int j=0;j<e[y].size();j++)
		{
			int yy=e[y][j];
			for(int k=0;k<mem[y].size();k++)
			{
				if(in[mem[y][k]]<=in[ce[yy]]&&in[ce[yy]]<=out[mem[y][k]])
				{
					for(int l=0;l<mem[y].size();l++)
					{
						if(in[mem[y][l]]<=in[mem[y][k]]&&in[mem[y][k]]<=out[mem[y][l]])
						{
							int cc=c[mem[y][k]]-c[mem[y][l]];
							if(-60000<=cc&&cc<=60000)ss+=ttc[yy][cc+60000];
						}
					}
				}
			}
			for(int i=0;i<=120000;i++)B.a[i]=complex(ttc[yy][i],0);
			for(int i=120001;i<LEN;i++)B.a[i]=complex(0,0);
			B.fft(1);
			for(int i=0;i<LEN;i++)B.a[i]=A.a[i]*B.a[i];
			B.fft(-1);
			for(int i=0;i<=120000;i++)ttc[yy][i]=int(B.a[i].real/len+0.5);
			for(int k=0;k<mem[y].size();k++)ss+=ttc[yy][c[mem[y][k]]+60000];
		}
	}
	ctt[c[x]+60000]--;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	for(int i=1;i<n;i++)
	{
		int x,y;scanf("%d%d",&x,&y);
		ins(x,y);ins(y,x);
	}
	block=1423;
	blk[1]=1;cnt=1;
	z=top=0;dfs(1,0);
	if(top>0)
	{
		ce[++cnt]=1;
		pos[1].push_back(cnt);
		while(top>0)blk[sta[top--]]=cnt;
	}
	for(int i=2;i<=cnt;i++)e[blk[ce[i]]].push_back(i);
	LEN=262144;r[0]=0;
	for(int i=1;i<LEN;i++)r[i]=r[i>>1]>>1|(i&1)<<17;
	dfs3(1,0);
	printf("%lld\n",ss);
	return 0;
}
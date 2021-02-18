#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char a[2100],b[2100];
long long base[2100];
long long hA[2100],hB[2100];
inline long long sa(int l,int r){return (hA[r]-hA[l-1]*base[r-l+1]%1000000009+1000000009)%1000000009;}
inline long long sb(int l,int r){return (hB[r]-hB[l-1]*base[r-l+1]%1000000009+1000000009)%1000000009;}
struct node{int l,r;long long h;}Q[2010000];
inline bool cmp(node x,node y){return x.h^y.h?x.h<y.h:x.l<y.l;}
int L[2100],R[2100];
int main()
{
	freopen("curiosity.in","r",stdin);
	freopen("curiosity.out","w",stdout);
	int A=0,B=0;
	char c=getchar();
	while(c=='\n'||c=='\r')c=getchar();
	while(c!='\n'&&c!='\r'){a[++A]=c;c=getchar();}
	while(c=='\n'||c=='\r')c=getchar();
	while(c!='\n'&&c!='\r'&&c!=EOF){b[++B]=c;c=getchar();}
	base[0]=1;
	for(int i=1;i<=2000;i++)base[i]=base[i-1]*997%1000000009;
	hA[0]=0;
	for(int i=1;i<=A;i++)hA[i]=(hA[i-1]*997+a[i])%1000000009;
	hB[0]=0;
	for(int i=1;i<=B;i++)hB[i]=(hB[i-1]*997+b[i])%1000000009;
	int qlen=0;
	for(int i=1;i<=A;i++)
	{
		for(int j=i;j<=A;j++)
		{
			Q[++qlen]=(node){i,j,sa(i,j)};
		}
	}
	sort(Q+1,Q+qlen+1,cmp);
	int i=1,lal=1,rar=A,lbl=1,rbr=B;
	while(i<=qlen)
	{
		int be=i;
		long long H=Q[i].h;
		int lr=0;R[0]=0;
		do
		{
			if(R[lr]<Q[i].l)
			{
				lr++;
				L[lr]=Q[i].l;
				R[lr]=Q[i].r;
			}
			i++;
		}while(i<=qlen&&H==Q[i].h);
		if((A-B)%lr!=0)continue;
		int len=Q[be].r-Q[be].l+1-(A-B)/lr;
		if(len<0)continue;
		long long HH=sb(Q[be].l,Q[be].l+len-1);
		bool bk=true;
		int k=0;
		for(int j=1;j<=lr;j++)
		{
			if(sa(R[j-1]+1,L[j]-1)!=sb(k+1,k+(L[j]-R[j-1]-1)))
			{
				bk=false;break;
			}
			k+=L[j]-R[j-1]-1;
			if(HH!=sb(k+1,k+len))
			{
				bk=false;break;
			}
			k+=len;
		}
		if(bk&&sa(R[lr]+1,A)==sb(k+1,B))
		{
			if(Q[be].r-Q[be].l+len-1<rar-lal+rbr-lbl)
			{
				lal=Q[be].l;
				rar=Q[be].r;
				lbl=Q[be].l;
				rbr=Q[be].l+len-1;
			}
		}
	}
	a[rar+1]='\0';b[rbr+1]='\0';
	printf("s/%s/%s/g\n",a+lal,b+lbl);
	return 0;
}
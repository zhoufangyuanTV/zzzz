#include <bits/stdc++.h>
#define fo(a,b,c) for (a=b; a<=c; a++)
#define fd(a,b,c) for (a=b; a>=c; a--)
#define ll long long
//#define file
using namespace std;

int f[2097152][21],s0[2097152],s1[2097152],p[22],n,K,i,j,k,l,I,ans1,ans2,t1,t2,S0,S1;
char ch;

void get(int x,int y,int tp)
{
	switch (tp)
	{
		case 0:{if (S1>>1) {k=t1+((S1>>1)<<(y+1)),l=y+1; return;}break;}
		case 1:{if (S0>>1) {k=t1+((S0>>1)<<(y+1))+p[y],l=y+1; return;}break;}
		case 2:{if (t2>1) {k=t1+p[y],l=y; return;}break;}
	}
	k=l=-1;
}

int main()
{
	p[0]=1;
	fo(i,1,21) p[i]=p[i-1]*2;
	#ifdef file
	freopen("agc024F.in","r",stdin);
	#endif
	
	scanf("%d%d",&n,&K);
	s0[0]=s1[0]=0;
	fo(i,0,p[n]-1)
	{
		if (i)
		s0[i*2]=s0[i],s1[i*2]=i*2;
		s0[i*2+1]=i*2+1,s1[i*2+1]=s1[i];
	}
	
	fo(i,0,n)
	{
		fo(j,0,p[i]-1)
		{
			ch=getchar();
			while (ch!='0' && ch!='1') ch=getchar();
			f[j+p[i]][0]+=ch=='1';
		}
	}
	
	fo(i,0,n)
	{
		fd(j,p[n+1]-1,0)
		if (f[j][i])
		{
			t1=j&(p[i]-1),t2=j>>i,S0=s0[t2],S1=s1[t2];
			fo(I,0,2)
			{
				get(j,i,I);
				if (k>-1)
				f[k][l]+=f[j][i];
			}
		}
	}
	
	ans1=-1;
	fo(i,1,p[n+1]-1)
	{
		fo(j,0,n)
		if (p[j]>i)
		break;
		--j;
		
		if (f[i][j]>=K && j>ans1)
		ans1=j,ans2=i;
	}
	if (ans1>-1)
	{
		fd(i,ans1-1,0)
		putchar(((ans2&p[i])>0)+'0');
		putchar('\n');
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
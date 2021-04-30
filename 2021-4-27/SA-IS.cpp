#include<cstdio>
#include<cstring>
using namespace std;
bool pt[210000];
int pS[210000],psa[210000],pst[210000],pLMS[210000],cntL[110000],cntS[110000];
void SAIS(int p,int n,int Sigma)
{
	bool *t=pt+p;
	int *S=pS+p,*sa=psa+p,*st=pst+p,*LMS=pLMS+p;
	t[n]=true;
	for(int i=n-1;i>=0;i--)
	{
		if(S[i]!=S[i+1])t[i]=S[i]<S[i+1];
		else t[i]=t[i+1];
	}
	int m=0;
	memset(st,-1,n*4);
	for(int i=1;i<n;i++)
	{
		if(t[i-1]==false&&t[i]==true)
		{
			st[i]=m;
			LMS[m]=i;
			m++;
		}
	}
	st[n]=m;
	LMS[m]=n;
	memset(cntL+1,0,Sigma*4);
	memset(cntS+1,0,Sigma*4);
	for(int i=0;i<n;i++)
	{
		if(t[i]==false)cntL[S[i]]++;
		else cntS[S[i]]++;
	}
	cntS[0]=0;
	for(int i=1;i<=Sigma;i++)
	{
		cntS[i]+=cntS[i-1]+cntL[i];
		cntL[i]=cntS[i-1]+1;
	}
	memset(sa+1,-1,n*4);
	for(int i=0;i<=m;i++)sa[cntS[S[LMS[i]]]--]=LMS[i];
	for(int i=0;i<Sigma;i++)cntS[i]=cntL[i+1]-1;
	cntS[Sigma]=n;
	for(int i=0;i<=n;i++)
	{
		if(sa[i]>0&&t[sa[i]-1]==false)sa[cntL[S[sa[i]-1]]++]=sa[i]-1;
	}
	for(int i=n;i>=0;i--)
	{
		if(sa[i]>0&&t[sa[i]-1]==true)sa[cntS[S[sa[i]-1]]--]=sa[i]-1;
	}
	int M=0,last=-1;
	for(int i=0;i<=n;i++)
	{
		if(st[sa[i]]!=-1)
		{
			if(last!=-1)
			{
				if(last==m)M++;
				else
				{
					for(int j=LMS[last],k=sa[i];j<=LMS[last+1]&&k<=LMS[st[sa[i]]+1];j++,k++)
					{
						if(S[j]!=S[k]||t[j]!=t[k]){M++;break;}
					}
				}
			}
			S[n+1+st[sa[i]]]=M;
			last=st[sa[i]];
		}
	}
	if(M<m)SAIS(p+n+1,m,M);
	memset(cntL+1,0,Sigma*4);
	memset(cntS+1,0,Sigma*4);
	for(int i=0;i<n;i++)
	{
		if(t[i]==false)cntL[S[i]]++;
		else cntS[S[i]]++;
	}
	cntS[0]=0;
	for(int i=1;i<=Sigma;i++)
	{
		cntS[i]+=cntS[i-1]+cntL[i];
		cntL[i]=cntS[i-1]+1;
	}
	memset(sa+1,-1,n*4);
	if(M<m)
	{
		for(int i=m;i>=0;i--)sa[cntS[S[LMS[sa[p+n+1+i]]]]--]=LMS[sa[p+n+1+i]];
	}
	else
	{
		for(int i=n;i>=0;i--)
		{
			if(pt[sa[i]]!=-1)sa[cntS[S[sa[i]]]--]=sa[i];
		}
	}
	for(int i=0;i<Sigma;i++)cntS[i]=cntL[i+1]-1;
	cntS[Sigma]=n;
	for(int i=0;i<=n;i++)
	{
		if(sa[i]>0&&t[sa[i]-1]==false)sa[cntL[S[sa[i]-1]]++]=sa[i]-1;
	}
	for(int i=n;i>=0;i--)
	{
		if(sa[i]>0&&t[sa[i]-1]==true)sa[cntS[S[sa[i]-1]]--]=sa[i]-1;
	}
}
char str[110000];
int cnt[26],rk[110000],height[110000];
int main()
{
	scanf("%s",str);
	int n=strlen(str);
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<n;i++)cnt[str[i]-'a']=1;
    for(int i=1;i<26;i++)cnt[i]+=cnt[i-1];
	for(int i=0;i<n;i++)pS[i]=cnt[str[i]-'a'];
	pS[n]=0;
	SAIS(0,n,cnt[25]);
	for(int i=0;i<n;i++)rk[psa[i]]=i;
	int j=0;
	for(int i=0;i<n;i++)
	{
		if(j>0)j--;
		if(rk[i]>0)while(str[psa[rk[i]-1]+j]==str[i+j])j++;
		height[rk[i]]=j;
	}
	for(int i=0;i<n;i++)printf("%d ",psa[i]+1);
	putchar('\n');
	for(int i=1;i<n;i++)printf("%d ",height[i]);
	return 0;
}

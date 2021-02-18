#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
map<unsigned long long,unsigned long long> UM,lgn2;
unsigned long long f[1048576],a[110],b[110];
inline unsigned long long lowbit(unsigned long long x){return x&-x;}
char re[110];
int main()
{
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%llu",&a[i]);
	unsigned long long s;scanf("%llu",&s);
	for(int i=0;i<n;i++)lgn2[1ull<<i]=i;
	if(n<=40)
	{
		int A=n/2,B=(n+1)/2;
		f[0]=0;UM[0]=0;
		for(int i=1;i<1<<A;i++)
		{
			f[i]=f[i-lowbit(i)]+a[lgn2[lowbit(i)]];
			UM[f[i]]=i;
		}
		f[0]=0;
		for(int i=1;i<1<<B;i++)f[i]=f[i-lowbit(i)]+a[A+lgn2[lowbit(i)]];
		unsigned long long Ans;
		for(int i=0;i<1<<B;i++)
		{
			auto it=UM.find(s-f[i]);
			if(it!=UM.end())
			{
				Ans=it->second|(unsigned long long)i<<A;
				break;
			}
		}
		for(int i=0;i<n;i++)putchar((Ans>>i&1)+'0');
		putchar('\n');
	}
	else
	{
		unsigned long long st=lowbit(a[0]);
		unsigned long long x=a[0]/st,inv=1;
		for(unsigned long long k=2;k<=(1ull<<63)/st;k<<=1)
		{
			if((x*inv&k)==k)inv|=k;
			if(k==(1ull<<63)/st)break;
		}
		if(a[0]*inv!=st)
		{
			puts("-1");
			return 0;
		}
		for(unsigned long long i=1;i*st<1ull<<(65-n);i+=2)
		{
			unsigned long long sg=0,pp=inv*i;
			if(st!=1)pp=pp%((1ull<<63)/(st>>1));
			bool bk=true;
			for(int k=0;k<n;k++)
			{
				b[k]=a[k]*pp;
				if(b[k]<=sg){bk=false;break;}
				if(sg+b[k]<b[k]){bk=false;break;}
				sg=sg+b[k];
			}
			if(bk)
			{
				s=s*pp;
				re[n]='\0';
				for(int k=n-1;k>=0;k--)
				{
					if(s>=b[k])
					{
						s-=b[k];
						re[k]='1';
					}
					else re[k]='0';
				}
				puts(re);
				return 0;
			}
			if(st!=1)
			{
				for(unsigned long long j=(1ull<<63)/(st>>1);j!=0;j+=(1ull<<63)/(st>>1))
				{
					unsigned long long p=pp+j;
					sg=0;bk=true;
					for(int k=0;k<n;k++)
					{
						b[k]=a[k]*p;
						if(b[k]<=sg){bk=false;break;}
						if(sg+b[k]<b[k]){bk=false;break;}
						sg=sg+b[k];
					}
					if(bk)
					{
						s=s*p;
						re[n]='\0';
						for(int k=n-1;k>=0;k--)
						{
							if(s>=b[k])
							{
								s-=b[k];
								re[k]='1';
							}
							else re[k]='0';
						}
						puts(re);
						return 0;
					}
				}
			}
		}
	}
	return 0;
}
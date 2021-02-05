#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(int &x)
{
	x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
}
long long f[6][6];
int a[1010000],b[1010000];
inline long long mymax(long long x,long long y){return x>y?x:y;}
int main()
{
	freopen("dissolution.in","r",stdin);
	freopen("dissolution.out","w",stdout);
	int n;read(n);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);read(b[i]);
	}
	memset(f,-64,sizeof(f));f[4][4]=0;
	long long p0,p1,p2,p3,p4,p5,q0,q1,q2,q3,q4,q5;
	for(int i=1;i<=n;i++)
	{
		p0=p1=p2=p3=p4=p5=q0=q1=q2=q3=q4=q5=0xc0c0c0c0c0c0c0c0ll;
		p0=mymax(p0,f[0][0]+a[i]+b[i]);p0=mymax(p0,f[0][1]+a[i]-b[i]);p0=mymax(p0,f[0][2]-a[i]+b[i]);p0=mymax(p0,f[0][3]-a[i]-b[i]);p0=mymax(p0,f[0][4]);
		p1=mymax(p1,f[1][0]+a[i]+b[i]);p1=mymax(p1,f[1][1]+a[i]-b[i]);p1=mymax(p1,f[1][2]-a[i]+b[i]);p1=mymax(p1,f[1][3]-a[i]-b[i]);p1=mymax(p1,f[1][4]);
		p2=mymax(p2,f[2][0]+a[i]+b[i]);p2=mymax(p2,f[2][1]+a[i]-b[i]);p2=mymax(p2,f[2][2]-a[i]+b[i]);p2=mymax(p2,f[2][3]-a[i]-b[i]);p2=mymax(p2,f[2][4]);
		p3=mymax(p3,f[3][0]+a[i]+b[i]);p3=mymax(p3,f[3][1]+a[i]-b[i]);p3=mymax(p3,f[3][2]-a[i]+b[i]);p3=mymax(p3,f[3][3]-a[i]-b[i]);p3=mymax(p3,f[3][4]);
		p4=mymax(p4,f[4][0]+a[i]+b[i]);p4=mymax(p4,f[4][1]+a[i]-b[i]);p4=mymax(p4,f[4][2]-a[i]+b[i]);p4=mymax(p4,f[4][3]-a[i]-b[i]);p4=mymax(p4,f[4][4]);
		p5=mymax(p5,f[5][0]+a[i]+b[i]);p5=mymax(p5,f[5][1]+a[i]-b[i]);p5=mymax(p5,f[5][2]-a[i]+b[i]);p5=mymax(p5,f[5][3]-a[i]-b[i]);p5=mymax(p5,f[5][4]);
		q0=mymax(q0,f[0][0]+a[i]+b[i]);q0=mymax(q0,f[1][0]+a[i]-b[i]);q0=mymax(q0,f[2][0]-a[i]+b[i]);q0=mymax(q0,f[3][0]-a[i]-b[i]);q0=mymax(q0,f[4][0]);
		q1=mymax(q1,f[0][1]+a[i]+b[i]);q1=mymax(q1,f[1][1]+a[i]-b[i]);q1=mymax(q1,f[2][1]-a[i]+b[i]);q1=mymax(q1,f[3][1]-a[i]-b[i]);q1=mymax(q1,f[4][1]);
		q2=mymax(q2,f[0][2]+a[i]+b[i]);q2=mymax(q2,f[1][2]+a[i]-b[i]);q2=mymax(q2,f[2][2]-a[i]+b[i]);q2=mymax(q2,f[3][2]-a[i]-b[i]);q2=mymax(q2,f[4][2]);
		q3=mymax(q3,f[0][3]+a[i]+b[i]);q3=mymax(q3,f[1][3]+a[i]-b[i]);q3=mymax(q3,f[2][3]-a[i]+b[i]);q3=mymax(q3,f[3][3]-a[i]-b[i]);q3=mymax(q3,f[4][3]);
		q4=mymax(q4,f[0][4]+a[i]+b[i]);q4=mymax(q4,f[1][4]+a[i]-b[i]);q4=mymax(q4,f[2][4]-a[i]+b[i]);q4=mymax(q4,f[3][4]-a[i]-b[i]);q4=mymax(q4,f[4][4]);
		q5=mymax(q5,f[0][5]+a[i]+b[i]);q5=mymax(q5,f[1][5]+a[i]-b[i]);q5=mymax(q5,f[2][5]-a[i]+b[i]);q5=mymax(q5,f[3][5]-a[i]-b[i]);q5=mymax(q5,f[4][5]);
		f[0][0]=mymax(p0-a[i]-b[i],q0-a[i]-b[i]);
		f[0][1]=mymax(p0-a[i]+b[i],q1-a[i]-b[i]);
		f[0][2]=mymax(p0+a[i]-b[i],q2-a[i]-b[i]);
		f[0][3]=mymax(p0+a[i]+b[i],q3-a[i]-b[i]);
		f[0][4]=q4-a[i]-b[i];
		f[0][5]=mymax(p0,q5-a[i]-b[i]);
		f[1][0]=mymax(p1-a[i]-b[i],q0-a[i]+b[i]);
		f[1][1]=mymax(p1-a[i]+b[i],q1-a[i]+b[i]);
		f[1][2]=mymax(p1+a[i]-b[i],q2-a[i]+b[i]);
		f[1][3]=mymax(p1+a[i]+b[i],q3-a[i]+b[i]);
		f[1][4]=q4-a[i]+b[i];
		f[1][5]=mymax(p1,q5-a[i]+b[i]);
		f[2][0]=mymax(p2-a[i]-b[i],q0+a[i]-b[i]);
		f[2][1]=mymax(p2-a[i]+b[i],q1+a[i]-b[i]);
		f[2][2]=mymax(p2+a[i]-b[i],q2+a[i]-b[i]);
		f[2][3]=mymax(p2+a[i]+b[i],q3+a[i]-b[i]);
		f[2][4]=q4+a[i]-b[i];
		f[2][5]=mymax(p2,q5+a[i]-b[i]);
		f[3][0]=mymax(p3-a[i]-b[i],q0+a[i]+b[i]);
		f[3][1]=mymax(p3-a[i]+b[i],q1+a[i]+b[i]);
		f[3][2]=mymax(p3+a[i]-b[i],q2+a[i]+b[i]);
		f[3][3]=mymax(p3+a[i]+b[i],q3+a[i]+b[i]);
		f[3][4]=q4+a[i]+b[i];
		f[3][5]=mymax(p3,q5+a[i]+b[i]);
		f[4][0]=p4-a[i]-b[i];
		f[4][1]=p4-a[i]+b[i];
		f[4][2]=p4+a[i]-b[i];
		f[4][3]=p4+a[i]+b[i];
		f[4][4]=0xc0c0c0c0c0c0c0c0ll;
		f[4][5]=p4;
		f[5][0]=mymax(p5-a[i]-b[i],q0);
		f[5][1]=mymax(p5-a[i]+b[i],q1);
		f[5][2]=mymax(p5+a[i]-b[i],q2);
		f[5][3]=mymax(p5+a[i]+b[i],q3);
		f[5][4]=q4;
		f[5][5]=mymax(p5,q5);
	}
	printf("%lld\n",f[5][5]);
	return 0;
}
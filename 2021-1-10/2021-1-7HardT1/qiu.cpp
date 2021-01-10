#include<cstdio>
#include<cstring>
using namespace std;
char buf[1<<23],*p1=buf,*p2=buf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<23,stdin),p1==p2)?EOF:*p1++)
inline void read(long long &x)
{
	x=0;int f=1;
	char c=getchar();
	while(c<'0'||c>'9'){c=='-'?f=-1:1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	x=x*f;
}
char ouf[110];
inline void write(unsigned long long x)
{
	if(x==0){puts("0");return ;}
	int len=0;
	while(x>0)ouf[++len]=x%10+'0',x=x/10;
	while(len>0)putchar(ouf[len--]);
	putchar('\n');
}
struct node{long long a,b,c;};
inline node operator+(node x,node y)
{
	node z;
	z.a=x.a+y.a;z.b=x.b+y.b;z.c=x.c+y.c;
	if(2147483648ll<=z.c)z.b++,z.c-=2147483648ll;
	if(2147483648ll<=z.b)z.a++,z.b-=2147483648ll;
	if(48<=z.a)z.a-=48;
	return z;
}
inline node operator-(node x,node y)
{
	node z;
	z.a=x.a-y.a;z.b=x.b-y.b;z.c=x.c-y.c;
	if(z.c<0)z.b--,z.c+=2147483648ll;
	if(z.b<0)z.a--,z.b+=2147483648ll;
	if(z.a<0)z.a+=48;
	return z;
}
inline node operator*(int x,node y)
{
	node z;
	z.a=x*y.a;z.b=x*y.b;z.c=x*y.c;
	z.b+=z.c>>31;z.c&=2147483647;
	z.a+=z.b>>31;z.b&=2147483647;
	z.a%=48;
	return z;
}
inline node operator*(node x,node y)
{
	long long c=x.c*y.c;
	long long b=x.b*y.c+x.c*y.b+(c>>31);
	return (node){(x.a*y.a*16+(x.a*y.b+x.b*y.a)%48*32+(x.a*y.c+x.c*y.a)%48+x.b*y.b%48+(b>>31))%48,b&2147483647,c&2147483647};
}
node a,b,c,d,e,f1,f2,f3,f4,f5;
int main()
{
	//freopen("qiu.in","r",stdin);
	//freopen("qiu.out","w",stdout);
	long long t;read(t);
	while(t--)
	{
		long long x1,x2,y1,y2;read(x1);read(x2);read(y1);read(y2);x1--;y1--;
		node X1=(node){0,x1>>31,x1&2147483647};
		node X2=(node){0,x2>>31,x2&2147483647};
		node Y1=(node){0,y1>>31,y1&2147483647};
		node Y2=(node){0,y2>>31,y2&2147483647};
		node X1h=(node){0,(x1+1)/2>>31,(x1+1)/2&2147483647};
		node X2h=(node){0,(x2+1)/2>>31,(x2+1)/2&2147483647};
		node Y1h=(node){0,(y1+1)/2>>31,(y1+1)/2&2147483647};
		node Y2h=(node){0,(y2+1)/2>>31,(y2+1)/2&2147483647};
		node s1=(node){0,0,0},s2=(node){0,0,0},s3=(node){0,0,0},s4=(node){0,0,0};
		//x1-1y1-1
		if(x1>=0&&y1>=0)
		{
			if(x1<y1)
			{
				if(x1%3==0)
				{
					node X13=(node){0,x1/3>>31,x1/3&2147483647};
					f1=(node){0,0,1}+14*X13+7*X1*X1+16*X13*X1*X1+2*X1*X1*X1*X1;
				}
				else if(x1%3==1)
				{
					node X13=(node){0,(x1+2)/3>>31,(x1+2)/3&2147483647};
					f1=(X1+(node){0,0,1})*(X13*(6*X1*X1-2*X1+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node X13=(node){0,(x1+1)/3>>31,(x1+1)/3&2147483647};
					f1=X13*(6*X1*X1*X1+10*X1*X1+11*X1+(node){0,0,3});
				}
				if(x1%2==1)
				{
					node X=2*X1+(node){0,0,3};
					f2=f1+(2*(X*X-(node){0,0,1}-X1h)+(node){0,0,1})*X1h;
					X=X+(node){0,0,2};
					f3=f2+(2*(X*X-(node){0,0,2}-X1h)+(node){0,0,1})*X1h;
					X=X+(node){0,0,2};
					f4=f3+(2*(X*X-(node){0,0,3}-X1h)+(node){0,0,1})*X1h;
					X=X+(node){0,0,2};
					f5=f4+(2*(X*X-(node){0,0,4}-X1h)+(node){0,0,1})*X1h;
				}
				else
				{
					node X=2*X1+(node){0,0,3};
					f2=f1+(X*X-(node){0,0,1}-X1h)*(X1+(node){0,0,1});
					X=X+(node){0,0,2};
					f3=f2+(X*X-(node){0,0,2}-X1h)*(X1+(node){0,0,1});
					X=X+(node){0,0,2};
					f4=f3+(X*X-(node){0,0,3}-X1h)*(X1+(node){0,0,1});
					X=X+(node){0,0,2};
					f5=f4+(X*X-(node){0,0,4}-X1h)*(X1+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node Y=Y1-X1+(node){0,0,1};
				s1=a+b*Y+c*Y*Y+d*Y*Y*Y+e*Y*Y*Y*Y;
			}
			else
			{
				if(y1%3==0)
				{
					node Y13=(node){0,y1/3>>31,y1/3&2147483647};
					f1=(node){0,0,1}+14*Y13+7*Y1*Y1+16*Y13*Y1*Y1+2*Y1*Y1*Y1*Y1;
				}
				else if(y1%3==1)
				{
					node Y13=(node){0,(y1+2)/3>>31,(y1+2)/3&2147483647};
					f1=(Y1+(node){0,0,1})*(Y13*(6*Y1*Y1-2*Y1+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node Y13=(node){0,(y1+1)/3>>31,(y1+1)/3&2147483647};
					f1=Y13*(6*Y1*Y1*Y1+10*Y1*Y1+11*Y1+(node){0,0,3});
				}
				if(y1%2==1)
				{
					node Y=2*Y1+(node){0,0,1};
					f2=f1+(2*(Y*Y+(node){0,0,1}+Y1h)-(node){0,0,1})*Y1h;
					Y=Y+(node){0,0,2};
					f3=f2+(2*(Y*Y+(node){0,0,2}+Y1h)-(node){0,0,1})*Y1h;
					Y=Y+(node){0,0,2};
					f4=f3+(2*(Y*Y+(node){0,0,3}+Y1h)-(node){0,0,1})*Y1h;
					Y=Y+(node){0,0,2};
					f5=f4+(2*(Y*Y+(node){0,0,4}+Y1h)-(node){0,0,1})*Y1h;
				}
				else
				{
					node Y=2*Y1+(node){0,0,1};
					f2=f1+(Y*Y+(node){0,0,1}+Y1h)*(Y1+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f3=f2+(Y*Y+(node){0,0,2}+Y1h)*(Y1+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f4=f3+(Y*Y+(node){0,0,3}+Y1h)*(Y1+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f5=f4+(Y*Y+(node){0,0,4}+Y1h)*(Y1+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node X=X1-Y1+(node){0,0,1};
				s1=a+b*X+c*X*X+d*X*X*X+e*X*X*X*X;
			}
		}
		//x1-1y2
		if(x1>=0&&y2>=0)
		{
			if(x1<y2)
			{
				if(x1%3==0)
				{
					node X13=(node){0,x1/3>>31,x1/3&2147483647};
					f1=(node){0,0,1}+14*X13+7*X1*X1+16*X13*X1*X1+2*X1*X1*X1*X1;
				}
				else if(x1%3==1)
				{
					node X13=(node){0,(x1+2)/3>>31,(x1+2)/3&2147483647};
					f1=(X1+(node){0,0,1})*(X13*(6*X1*X1-2*X1+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node X13=(node){0,(x1+1)/3>>31,(x1+1)/3&2147483647};
					f1=X13*(6*X1*X1*X1+10*X1*X1+11*X1+(node){0,0,3});
				}
				if(x1%2==1)
				{
					node X=2*X1+(node){0,0,3};
					f2=f1+(2*(X*X-(node){0,0,1}-X1h)+(node){0,0,1})*X1h;
					X=X+(node){0,0,2};
					f3=f2+(2*(X*X-(node){0,0,2}-X1h)+(node){0,0,1})*X1h;
					X=X+(node){0,0,2};
					f4=f3+(2*(X*X-(node){0,0,3}-X1h)+(node){0,0,1})*X1h;
					X=X+(node){0,0,2};
					f5=f4+(2*(X*X-(node){0,0,4}-X1h)+(node){0,0,1})*X1h;
				}
				else
				{
					node X=2*X1+(node){0,0,3};
					f2=f1+(X*X-(node){0,0,1}-X1h)*(X1+(node){0,0,1});
					X=X+(node){0,0,2};
					f3=f2+(X*X-(node){0,0,2}-X1h)*(X1+(node){0,0,1});
					X=X+(node){0,0,2};
					f4=f3+(X*X-(node){0,0,3}-X1h)*(X1+(node){0,0,1});
					X=X+(node){0,0,2};
					f5=f4+(X*X-(node){0,0,4}-X1h)*(X1+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node Y=Y2-X1+(node){0,0,1};
				s2=a+b*Y+c*Y*Y+d*Y*Y*Y+e*Y*Y*Y*Y;
			}
			else
			{
				if(y2%3==0)
				{
					node Y23=(node){0,y2/3>>31,y2/3&2147483647};
					f1=(node){0,0,1}+14*Y23+7*Y2*Y2+16*Y23*Y2*Y2+2*Y2*Y2*Y2*Y2;
				}
				else if(y2%3==1)
				{
					node Y23=(node){0,(y2+2)/3>>31,(y2+2)/3&2147483647};
					f1=(Y2+(node){0,0,1})*(Y23*(6*Y2*Y2-2*Y2+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node Y23=(node){0,(y2+1)/3>>31,(y2+1)/3&2147483647};
					f1=Y23*(6*Y2*Y2*Y2+10*Y2*Y2+11*Y2+(node){0,0,3});
				}
				if(y2%2==1)
				{
					node Y=2*Y2+(node){0,0,1};
					f2=f1+(2*(Y*Y+(node){0,0,1}+Y2h)-(node){0,0,1})*Y2h;
					Y=Y+(node){0,0,2};
					f3=f2+(2*(Y*Y+(node){0,0,2}+Y2h)-(node){0,0,1})*Y2h;
					Y=Y+(node){0,0,2};
					f4=f3+(2*(Y*Y+(node){0,0,3}+Y2h)-(node){0,0,1})*Y2h;
					Y=Y+(node){0,0,2};
					f5=f4+(2*(Y*Y+(node){0,0,4}+Y2h)-(node){0,0,1})*Y2h;
				}
				else
				{
					node Y=2*Y2+(node){0,0,1};
					f2=f1+(Y*Y+(node){0,0,1}+Y2h)*(Y2+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f3=f2+(Y*Y+(node){0,0,2}+Y2h)*(Y2+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f4=f3+(Y*Y+(node){0,0,3}+Y2h)*(Y2+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f5=f4+(Y*Y+(node){0,0,4}+Y2h)*(Y2+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node X=X1-Y2+(node){0,0,1};
				s2=a+b*X+c*X*X+d*X*X*X+e*X*X*X*X;
			}
		}
		//x2y1-1
		if(x2>=0&&y1>=0)
		{
			if(x2<y1)
			{
				if(x2%3==0)
				{
					node X23=(node){0,x2/3>>31,x2/3&2147483647};
					f1=(node){0,0,1}+14*X23+7*X2*X2+16*X23*X2*X2+2*X2*X2*X2*X2;
				}
				else if(x2%3==1)
				{
					node X23=(node){0,(x2+2)/3>>31,(x2+2)/3&2147483647};
					f1=(X2+(node){0,0,1})*(X23*(6*X2*X2-2*X2+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node X23=(node){0,(x2+1)/3>>31,(x2+1)/3&2147483647};
					f1=X23*(6*X2*X2*X2+10*X2*X2+11*X2+(node){0,0,3});
				}
				if(x2%2==1)
				{
					node X=2*X2+(node){0,0,3};
					f2=f1+(2*(X*X-(node){0,0,1}-X2h)+(node){0,0,1})*X2h;
					X=X+(node){0,0,2};
					f3=f2+(2*(X*X-(node){0,0,2}-X2h)+(node){0,0,1})*X2h;
					X=X+(node){0,0,2};
					f4=f3+(2*(X*X-(node){0,0,3}-X2h)+(node){0,0,1})*X2h;
					X=X+(node){0,0,2};
					f5=f4+(2*(X*X-(node){0,0,4}-X2h)+(node){0,0,1})*X2h;
				}
				else
				{
					node X=2*X2+(node){0,0,3};
					f2=f1+(X*X-(node){0,0,1}-X2h)*(X2+(node){0,0,1});
					X=X+(node){0,0,2};
					f3=f2+(X*X-(node){0,0,2}-X2h)*(X2+(node){0,0,1});
					X=X+(node){0,0,2};
					f4=f3+(X*X-(node){0,0,3}-X2h)*(X2+(node){0,0,1});
					X=X+(node){0,0,2};
					f5=f4+(X*X-(node){0,0,4}-X2h)*(X2+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node Y=Y1-X2+(node){0,0,1};
				s3=a+b*Y+c*Y*Y+d*Y*Y*Y+e*Y*Y*Y*Y;
			}
			else
			{
				if(y1%3==0)
				{
					node Y13=(node){0,y1/3>>31,y1/3&2147483647};
					f1=(node){0,0,1}+14*Y13+7*Y1*Y1+16*Y13*Y1*Y1+2*Y1*Y1*Y1*Y1;
				}
				else if(y1%3==1)
				{
					node Y13=(node){0,(y1+2)/3>>31,(y1+2)/3&2147483647};
					f1=(Y1+(node){0,0,1})*(Y13*(6*Y1*Y1-2*Y1+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node Y13=(node){0,(y1+1)/3>>31,(y1+1)/3&2147483647};
					f1=Y13*(6*Y1*Y1*Y1+10*Y1*Y1+11*Y1+(node){0,0,3});
				}
				if(y1%2==1)
				{
					node Y=2*Y1+(node){0,0,1};
					f2=f1+(2*(Y*Y+(node){0,0,1}+Y1h)-(node){0,0,1})*Y1h;
					Y=Y+(node){0,0,2};
					f3=f2+(2*(Y*Y+(node){0,0,2}+Y1h)-(node){0,0,1})*Y1h;
					Y=Y+(node){0,0,2};
					f4=f3+(2*(Y*Y+(node){0,0,3}+Y1h)-(node){0,0,1})*Y1h;
					Y=Y+(node){0,0,2};
					f5=f4+(2*(Y*Y+(node){0,0,4}+Y1h)-(node){0,0,1})*Y1h;
				}
				else
				{
					node Y=2*Y1+(node){0,0,1};
					f2=f1+(Y*Y+(node){0,0,1}+Y1h)*(Y1+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f3=f2+(Y*Y+(node){0,0,2}+Y1h)*(Y1+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f4=f3+(Y*Y+(node){0,0,3}+Y1h)*(Y1+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f5=f4+(Y*Y+(node){0,0,4}+Y1h)*(Y1+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node X=X2-Y1+(node){0,0,1};
				s3=a+b*X+c*X*X+d*X*X*X+e*X*X*X*X;
			}
		}
		//x2y2
		if(x2>=0&&y2>=0)
		{
			if(x2<y2)
			{
				if(x2%3==0)
				{
					node X23=(node){0,x2/3>>31,x2/3&2147483647};
					f1=(node){0,0,1}+14*X23+7*X2*X2+16*X23*X2*X2+2*X2*X2*X2*X2;
				}
				else if(x2%3==1)
				{
					node X23=(node){0,(x2+2)/3>>31,(x2+2)/3&2147483647};
					f1=(X2+(node){0,0,1})*(X23*(6*X2*X2-2*X2+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node X23=(node){0,(x2+1)/3>>31,(x2+1)/3&2147483647};
					f1=X23*(6*X2*X2*X2+10*X2*X2+11*X2+(node){0,0,3});
				}
				if(x2%2==1)
				{
					node X=2*X2+(node){0,0,3};
					f2=f1+(2*(X*X-(node){0,0,1}-X2h)+(node){0,0,1})*X2h;
					X=X+(node){0,0,2};
					f3=f2+(2*(X*X-(node){0,0,2}-X2h)+(node){0,0,1})*X2h;
					X=X+(node){0,0,2};
					f4=f3+(2*(X*X-(node){0,0,3}-X2h)+(node){0,0,1})*X2h;
					X=X+(node){0,0,2};
					f5=f4+(2*(X*X-(node){0,0,4}-X2h)+(node){0,0,1})*X2h;
				}
				else
				{
					node X=2*X2+(node){0,0,3};
					f2=f1+(X*X-(node){0,0,1}-X2h)*(X2+(node){0,0,1});
					X=X+(node){0,0,2};
					f3=f2+(X*X-(node){0,0,2}-X2h)*(X2+(node){0,0,1});
					X=X+(node){0,0,2};
					f4=f3+(X*X-(node){0,0,3}-X2h)*(X2+(node){0,0,1});
					X=X+(node){0,0,2};
					f5=f4+(X*X-(node){0,0,4}-X2h)*(X2+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node Y=Y2-X2+(node){0,0,1};
				s4=a+b*Y+c*Y*Y+d*Y*Y*Y+e*Y*Y*Y*Y;
			}
			else
			{
				if(y2%3==0)
				{
					node Y23=(node){0,y2/3>>31,y2/3&2147483647};
					f1=(node){0,0,1}+14*Y23+7*Y2*Y2+16*Y23*Y2*Y2+2*Y2*Y2*Y2*Y2;
				}
				else if(y2%3==1)
				{
					node Y23=(node){0,(y2+2)/3>>31,(y2+2)/3&2147483647};
					f1=(Y2+(node){0,0,1})*(Y23*(6*Y2*Y2-2*Y2+(node){0,0,15})-(node){0,0,9});
				}
				else
				{
					node Y23=(node){0,(y2+1)/3>>31,(y2+1)/3&2147483647};
					f1=Y23*(6*Y2*Y2*Y2+10*Y2*Y2+11*Y2+(node){0,0,3});
				}
				if(y2%2==1)
				{
					node Y=2*Y2+(node){0,0,1};
					f2=f1+(2*(Y*Y+(node){0,0,1}+Y2h)-(node){0,0,1})*Y2h;
					Y=Y+(node){0,0,2};
					f3=f2+(2*(Y*Y+(node){0,0,2}+Y2h)-(node){0,0,1})*Y2h;
					Y=Y+(node){0,0,2};
					f4=f3+(2*(Y*Y+(node){0,0,3}+Y2h)-(node){0,0,1})*Y2h;
					Y=Y+(node){0,0,2};
					f5=f4+(2*(Y*Y+(node){0,0,4}+Y2h)-(node){0,0,1})*Y2h;
				}
				else
				{
					node Y=2*Y2+(node){0,0,1};
					f2=f1+(Y*Y+(node){0,0,1}+Y2h)*(Y2+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f3=f2+(Y*Y+(node){0,0,2}+Y2h)*(Y2+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f4=f3+(Y*Y+(node){0,0,3}+Y2h)*(Y2+(node){0,0,1});
					Y=Y+(node){0,0,2};
					f5=f4+(Y*Y+(node){0,0,4}+Y2h)*(Y2+(node){0,0,1});
				}
				a=120*f1-240*f2+240*f3-120*f4+24*f5;
				b=244*f4-50*f5-468*f3+428*f2-154*f1;
				c=35*f5-164*f4+294*f3-236*f2+71*f1;
				d=44*f4-72*f3+52*f2-14*f1-10*f5;
				e=f5-4*f4+6*f3-4*f2+f1;
				node X=X2-Y2+(node){0,0,1};
				s4=a+b*X+c*X*X+d*X*X*X+e*X*X*X*X;
			}
		}
		s1=s1-s2-s3+s4;
		unsigned long long ss=s1.a%24<<31;s1.a=s1.a/24;
		s1.b=s1.b+ss;ss=s1.b%24<<31;s1.b=s1.b/24;
		s1.c=(s1.c+ss)/24;
		ss=(s1.a&1)<<62|s1.b<<31|s1.c;
		write(ss);
	}
	return 0;
}
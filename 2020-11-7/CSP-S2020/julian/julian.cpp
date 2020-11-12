#include<cstdio>
#include<cstring>
using namespace std;
int dd[2460000],yy[2460000],mm[2460000];
int mg[110];
int main()
{
	freopen("julian.in","r",stdin);
	freopen("julian.out","w",stdout);
	mg[1]=mg[3]=mg[5]=mg[7]=mg[8]=mg[10]=mg[12]=31;
	mg[4]=mg[6]=mg[9]=mg[11]=30;
	int y=-4713,m=1,d=1;
	long long day=0;
	while(day<=2451911)
	{
		dd[day]=d;yy[day]=y;mm[day]=m;
		day++;
		d++;
		if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
		{
			if(d==32)m++,d=1;
		}
		else if(m==2)
		{
			if(y<0)
			{
				if((-y)%4==1)
				{
					if(d==30)m++,d=1;
				}
				else if(d==29)m++,d=1;
			}
			else
			{
				if(y<=1582)
				{
					if(y%4==0)
					{
						if(d==30)m++,d=1;
					}
					else if(d==29)m++,d=1;
				}
				else
				{
					if((y%4==0&&y%100!=0)||y%400==0)
					{
						if(d==30)m++,d=1;
					}
					else if(d==29)m++,d=1;
				}
			}
		}
		else if(d==31)m++,d=1;
		if(m==13)y++,m=1;
		if(y==0)y++;
		if(y==1582&&m==10&&d==5)d=15;
	}
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%lld\n",&day);
		if(day<=2451911)
		{
			if(yy[day]<0)printf("%d %d %d BC\n",dd[day],mm[day],-yy[day]);
			else printf("%d %d %d\n",dd[day],mm[day],yy[day]);
		}
		else
		{
			day-=2451911;
			long long dg=day/146097;day=day%146097;
			long long year=2001+dg*400;
			if(day>=145731)
			{
				year+=399;day-=145731;
			}
			else
			{
				if(day>=109572)year+=300,day-=109572;
				else if(day>=73048)year+=200,day-=73048;
				else if(day>=36524)year+=100,day-=36524;
				if(day>=36159)year+=99,day-=36159;
				else
				{
					long long fg=day/1461;day=day%1461;
					year=year+fg*4;
					if(day>=1095)year+=3,day-=1095;
					else if(day>=730)year+=2,day-=730;
					else if(day>=365)year+=1,day-=365;
				}
			}
			if((year%400==0)||(year%4==0&&year%100!=0))mg[2]=29;
			else mg[2]=28;
			int month=1;
			while(day>=mg[month])
			{
				day=day-mg[month];
				month++;
			}
			printf("%lld %d %lld\n",day+1,month,year);
		}
	}
	return 0;
}

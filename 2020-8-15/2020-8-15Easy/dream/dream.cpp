#include<cstdio>
#include<cstring>
using namespace std;
char a[1100][1100];
int main()
{
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	int uvwxyz=0;
	for(int o=1;o<=n;o++)
		for(int p=1;p<=n;p++)
			for(int q=o;q<=n;q++)
			{
				bool r=true;
				for(int s=p;s<=n;s++)
				{
					for(int t=o;t<=q;t++)if(a[t][s]=='B'){r=false;break;}
					if(r==false)break;
					if(q==o&&s==p)continue;
					for(int oo=1;oo<=n;oo++)
						for(int pp=1;pp<=n;pp++)
							for(int qq=oo;qq<=n;qq++)
							{
								bool rr=true;
								for(int ss=pp;ss<=n;ss++)
								{
									for(int tt=oo;tt<=qq;tt++)if(a[tt][ss]=='B'){rr=false;break;}
									if(rr==false)break;
									if(qq==oo&&ss==pp)continue;
									uvwxyz++;
									if(o<=qq&&oo<=q&&p<=ss&&pp<=s)uvwxyz--;
								}
							}
				}
			}
	printf("%d\n",uvwxyz/2%10007);
	return 0;
}
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int dx[4]={1,0,-1,0};
const int dy[4]={0,1,0,-1};
struct pt{int x,y;};
vector<pt> a[31];
bool b[2100][2100];
struct node
{
	int x,y,d;
}list[4010000];
char s[2100][2100];
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	int stx,sty,edx,edy;
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
	memset(b,true,sizeof(b));
	for(int i=1;i<=n;i++)b[i][0]=b[i][m+1]=false;
	for(int i=1;i<=m;i++)b[0][i]=b[n+1][i]=false;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(s[i][j]=='S')stx=i,sty=j;
			else if(s[i][j]=='G')edx=i,edy=j;
			else if(s[i][j]>='a'&&s[i][j]<='z')
			{
				a[s[i][j]-'a'].push_back((pt){i,j});
			}
			else if(s[i][j]=='#')b[i][j]=false;
		}
	}
	int head=1,tail=2;
	list[1]=(node){stx,sty,0};b[stx][sty]=false;
	while(head<tail)
	{
		node x=list[head];
		if(x.x==edx&&x.y==edy)
		{
			printf("%d\n",x.d);
			return 0;
		}
		for(int i=0;i<4;i++)
		{
			int xx=x.x+dx[i],yy=x.y+dy[i];
			if(b[xx][yy])
			{
				b[xx][yy]=false;
				list[tail++]=(node){xx,yy,x.d+1};
			}
		}
		if(s[x.x][x.y]>='a'&&s[x.x][x.y]<='z')
		{
			for(int i=0;i<a[s[x.x][x.y]-'a'].size();i++)
			{
				int xr=a[s[x.x][x.y]-'a'][i].x,yr=a[s[x.x][x.y]-'a'][i].y;
				if(b[xr][yr])
				{
					s[xr][yr]='.';
					b[xr][yr]=false;
					list[tail++]=(node){xr,yr,x.d+1};
				}
			}
		}
		head++;
	}
	puts("-1");
	return 0;
}
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,cnt[11];
struct node
{
	int x,y;
}a[11],L1[2100],L2[2100];int len1,len2;
int dx,dy;
int r[11];
bool G;
int Ans[510][510];
char S[510][510];
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%d%d%d%d%d%d%d%d",&n,&m,&cnt[1],&cnt[2],&cnt[3],&a[1].x,&a[1].y,&a[2].x,&a[2].y,&a[3].x,&a[3].y);
		if(a[1].x==a[2].x&&a[1].x==a[3].x)
		{
			G=true;
			swap(n,m);
			swap(a[1].x,a[1].y);
			swap(a[2].x,a[2].y);
			swap(a[3].x,a[3].y);
		}
		else G=false;
		if(a[1].x!=a[2].x&&a[1].x!=a[3].x)
		{
			dx=a[1].x;
			dy=a[1].y;
			a[4].x=a[1].x-dx+1;
			a[4].y=a[1].y-dy+1;
			a[5].x=a[2].x-dx+1;
			a[5].y=a[2].y-dy+1;
			a[6].x=a[3].x-dx+1;
			a[6].y=a[3].y-dy+1;
			if(a[4].x<1)a[4].x+=n;
			if(a[5].x<1)a[5].x+=n;
			if(a[6].x<1)a[6].x+=n;
			if(a[4].y<1)a[4].y+=m;
			if(a[5].y<1)a[5].y+=m;
			if(a[6].y<1)a[6].y+=m;
			a[1]=a[4];
			a[2]=a[5];
			a[3]=a[6];
			r[1]=1;
			if(a[2].y<a[3].y)
			{
				r[2]=2;
				r[3]=3;
			}
			else if(a[3].y<a[2].y)
			{
				r[2]=3;
				r[3]=2;
			}
			else if(a[2].x<a[3].x)
			{
				r[2]=2;
				r[3]=3;
			}
			else
			{
				r[2]=3;
				r[3]=2;
			}
		}
		else if(a[2].x!=a[1].x&&a[2].x!=a[3].x)
		{
			dx=a[2].x;
			dy=a[2].y;
			a[4].x=a[1].x-dx+1;
			a[4].y=a[1].y-dy+1;
			a[5].x=a[2].x-dx+1;
			a[5].y=a[2].y-dy+1;
			a[6].x=a[3].x-dx+1;
			a[6].y=a[3].y-dy+1;
			if(a[4].x<1)a[4].x+=n;
			if(a[5].x<1)a[5].x+=n;
			if(a[6].x<1)a[6].x+=n;
			if(a[4].y<1)a[4].y+=m;
			if(a[5].y<1)a[5].y+=m;
			if(a[6].y<1)a[6].y+=m;
			a[1]=a[4];
			a[2]=a[5];
			a[3]=a[6];
			r[1]=2;
			if(a[1].y<a[3].y)
			{
				r[2]=1;
				r[3]=3;
			}
			else if(a[3].y<a[1].y)
			{
				r[2]=3;
				r[3]=1;
			}
			else if(a[1].x<a[3].x)
			{
				r[2]=1;
				r[3]=3;
			}
			else
			{
				r[2]=3;
				r[3]=1;
			}
		}
		else
		{
			dx=a[3].x;
			dy=a[3].y;
			a[4].x=a[1].x-dx+1;
			a[4].y=a[1].y-dy+1;
			a[5].x=a[2].x-dx+1;
			a[5].y=a[2].y-dy+1;
			a[6].x=a[3].x-dx+1;
			a[6].y=a[3].y-dy+1;
			if(a[4].x<1)a[4].x+=n;
			if(a[5].x<1)a[5].x+=n;
			if(a[6].x<1)a[6].x+=n;
			if(a[4].y<1)a[4].y+=m;
			if(a[5].y<1)a[5].y+=m;
			if(a[6].y<1)a[6].y+=m;
			a[1]=a[4];
			a[2]=a[5];
			a[3]=a[6];
			r[1]=3;
			if(a[1].y<a[2].y)
			{
				r[2]=1;
				r[3]=2;
			}
			else if(a[2].y<a[1].y)
			{
				r[2]=2;
				r[3]=1;
			}
			else if(a[1].x<a[2].x)
			{
				r[2]=1;
				r[3]=2;
			}
			else
			{
				r[2]=2;
				r[3]=1;
			}
		}
		a[4]=a[1];
		a[5]=a[2];
		a[6]=a[3];
		a[1]=a[3+r[1]];
		a[2]=a[3+r[2]];
		a[3]=a[3+r[3]];
		cnt[4]=cnt[1];
		cnt[5]=cnt[2];
		cnt[6]=cnt[3];
		cnt[1]=cnt[3+r[1]];
		cnt[2]=cnt[3+r[2]];
		cnt[3]=cnt[3+r[3]];
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)Ans[i][j]=0;
		}
		if(cnt[1]<m)
		{
			for(int i=1;i<=cnt[1];i++)Ans[1][i]=1;
			for(int i=a[2].y;i>=1;i--)
			{
				if(cnt[2]==0)break;
				Ans[a[2].x][i]=2;cnt[2]--;
			}
			for(int i=1;i<=m;i++)
			{
				if(cnt[2]==0)break;
				for(int j=a[3].x+1;j<=n;j++)
				{
					if(cnt[2]==0)break;
					if(Ans[j][i]==0){Ans[j][i]=2;cnt[2]--;}
				}
				for(int j=1;j<a[3].x;j++)
				{
					if(cnt[2]==0)break;
					if(Ans[j][i]==0)Ans[j][i]=2,cnt[2]--;
				}
				if(cnt[2]==0)break;
				if(i<a[3].y&&Ans[a[3].x][i]==0)Ans[a[3].x][i]=2,cnt[2]--;
			}
			for(int i=m;i>a[2].y;i--)
			{
				if(cnt[2]==0)break;
				if(Ans[a[3].x][i]==0)Ans[a[3].x][i]=2,cnt[2]--;
			}
		}
		else
		{
			len1=len2=0;
			if(a[2].y==a[3].y)
			{
				for(int i=a[2].x;i<a[3].x;i++)
				{
					Ans[i][a[2].y]=2;
					L1[++len1]=(node){i,a[2].y};
				}
				if(a[2].y>1)
				{
					for(int i=a[3].x-1;i<=n;i++)
					{
						Ans[i][a[2].y-1]=2;
						L1[++len1]=(node){i,a[2].y-1};
					}
				}
				else
				{
					for(int i=a[3].x-1;i<=n;i++)
					{
						Ans[i][a[2].y+1]=2;
						L1[++len1]=(node){i,a[2].y+1};
					}
				}
				for(int i=a[3].x;i<=n;i++)
				{
					Ans[i][a[3].y]=3;
					L2[++len2]=(node){i,a[3].y};
				}
			}
			else
			{
				for(int i=a[2].x;i<=n;i++)
				{
					Ans[i][a[2].y]=2;
					L1[++len1]=(node){i,a[2].y};
				}
				for(int i=a[3].x;i<=n;i++)
				{
					Ans[i][a[3].y]=3;
					L2[++len2]=(node){i,a[3].y};
				}
			}
			for(int i=1;i<=n;i++)
			{
				if(cnt[1]==0)break;
				for(int j=1;j<a[3].y-1&&Ans[i][j]==0;j++)
				{
					if(cnt[1]==0)break;
					Ans[i][j]=1;cnt[1]--;
				}
				for(int j=m;j>a[2].y+1&&Ans[i][j]==0;j--)
				{
					if(cnt[1]==0)break;
					Ans[i][j]=1;cnt[1]--;
				}
				if(cnt[2]==1)
				{
					for(int j=1;j<=m;j++)
					{
						if(cnt[1]==0)break;
						if(Ans[i][j]==0)Ans[i][j]=1,cnt[1]--;
					}
				}
				else
				{
					for(int j=m;j>=1;j--)
					{
						if(cnt[1]==0)break;
						if(Ans[i][j]==0)Ans[i][j]=1,cnt[1]--;
					}
				}
			}
			for(int i=1;i<=len1;i++)Ans[L1[i].x][L1[i].y]=0;
			for(int i=1;i<=len2;i++)Ans[L2[i].x][L2[i].y]=0;
			len1=len2=0;
			if(a[2].y==a[3].y&&a[2].x==1)
			{
				int xx=a[2].x,yy=a[2].y;
				while(xx<=n)
				{
					L1[++len1]=(node){xx,yy};
					if(yy<m&&Ans[xx][yy+1]==0)yy++;
					else xx++;
				}
				xx=a[3].x;yy=a[3].y;
				while(xx<=n)
				{
					L2[++len2]=(node){xx,yy};
					Ans[xx][yy]=3;
					if(yy>1&&Ans[xx][yy-1]==0)yy--;
					else xx++;
				}
				for(int i=1;i<=len1;i++)
				{
					if(cnt[2]==0)break;
					Ans[L1[i].x][L1[i].y]=2;cnt[2]--;
				}
				for(int i=m;i>=1;i--)
				{
					if(cnt[2]==0)break;
					for(int j=1;j<=n;j++)
					{
						if(cnt[2]==0)break;
						if(Ans[j][i]==0)Ans[j][i]=2,cnt[2]--;
					}
				}
				for(int i=len2;i>=1;i--)
				{
					if(cnt[2]==0)break;
					Ans[L2[i].x][L2[i].y]=2;cnt[2]--;
				}
			}
			else
			{
				int xx=a[2].x,yy=a[2].y;
				while(xx<=n)
				{
					L1[++len1]=(node){xx,yy};
					if(yy>1&&Ans[xx][yy-1]==0)yy--;
					else xx++;
				}
				xx=a[3].x;yy=a[3].y;
				while(xx<=n)
				{
					L2[++len2]=(node){xx,yy};
					Ans[xx][yy]=3;
					if(yy<m&&Ans[xx][yy+1]==0)yy++;
					else xx++;
				}
				for(int i=1;i<=len1;i++)
				{
					if(cnt[2]==0)break;
					Ans[L1[i].x][L1[i].y]=2;cnt[2]--;
				}
				for(int i=1;i<=m;i++)
				{
					if(cnt[2]==0)break;
					for(int j=n;j>=1;j--)
					{
						if(cnt[2]==0)break;
						if(Ans[j][i]==0)Ans[j][i]=2,cnt[2]--;
					}
				}
				for(int i=len2;i>=1;i--)
				{
					if(cnt[2]==0)break;
					Ans[L2[i].x][L2[i].y]=2;cnt[2]--;
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				if(Ans[i][j]==0)Ans[i][j]=3;
				int x=i+dx-1,y=j+dy-1;
				if(x>n)x-=n;
				if(y>m)y-=m;
				if(G)swap(x,y);
				S[x][y]=r[Ans[i][j]]+'A'-1;
			}
		}
		if(G)swap(n,m);
		for(int i=1;i<=n;i++){S[i][m+1]='\0';puts(S[i]+1);}
	}
	return 0;
}
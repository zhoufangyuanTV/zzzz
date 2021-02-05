#include<io.h>
#include<windows.h>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<random>
#include<algorithm>
using namespace std;
int n,m,a[1100],b[310],w[1100][310];
mt19937 myrand;
int pailie[1100];
struct node{int x,p;}p[310];int plen;
struct sheep
{
	int f,Ans[1100];
	inline void calc()
	{
		f=0;
		for(int i=1;i<=n;i++)f+=w[i][Ans[i]];
	}
	inline bool live()
	{
		for(int i=1;i<=n;i++)b[Ans[i]]-=a[i];
		bool re=true;
		for(int i=1;i<=m;i++)if(b[i]<0){re=false;break;}
		for(int i=1;i<=n;i++)b[Ans[i]]+=a[i];
		return re;
	}
	inline void grow()
	{
		for(int i=1;i<=n;i++)b[Ans[i]]-=a[i];
		shuffle(pailie+1,pailie+n+1,myrand);
		for(int t=1;t<=n;t++)
		{
			int i=pailie[t];
			if(Ans[i]==0)
			{
				p[0].x=0;plen=0;
				for(int j=1;j<=m;j++)
				{
					if(a[i]<=b[j])
					{
						plen++;
						p[plen]=(node){p[plen-1].x+w[i][j],j};
					}
				}
				if(plen>0)
				{
					int v=myrand()%p[plen].x;
					int l=1,r=plen;
					while(l<r)
					{
						int mid=(l+r)/2;
						if(v<p[mid].x)r=mid;
						else l=mid+1;
					}
					b[p[r].p]-=a[i];
					Ans[i]=p[r].p;
				}
			}
		}
		for(int i=1;i<=n;i++)b[Ans[i]]+=a[i];
	}
}S[91000],SS[91000];int slen,sslen;
inline sheep cross(sheep x,sheep y)
{
	sheep z;
	shuffle(pailie+1,pailie+n+1,myrand);
	for(int t=1;t<=n;t++)
	{
		int i=pailie[t];
		if(a[i]<=b[x.Ans[i]]&&a[i]<=b[y.Ans[i]])
		{
			z.Ans[i]=myrand()&1?x.Ans[i]:y.Ans[i];
			b[z.Ans[i]]-=a[i];
		}
		else if(a[i]<=b[x.Ans[i]])b[z.Ans[i]=x.Ans[i]]-=a[i];
		else if(a[i]<=b[y.Ans[i]])b[z.Ans[i]=y.Ans[i]]-=a[i];
		else z.Ans[i]=0;
	}
	for(int i=1;i<=n;i++)b[z.Ans[i]]+=a[i];
	return z;
}
inline bool cmp(sheep x,sheep y){return x.f>y.f;}
char fn[260];
int main()
{
	freopen("drawer.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%d",&w[i][j]);
	for(int i=1;i<=n;i++)pailie[i]=i;
	int TAT=1;
	while(TAT--)
	{
		int cnt=0;
		_finddata_t fd;
		intptr_t hd=_findfirst("C:\\Users\\Administrator\\Desktop\\zzzz\\present\\THUWC2017T3\\drawer10\\sheep\\new\\*",&fd);
		if(hd!=-1)
		{
			do cnt+=strcmp(fd.name,".")!=0&&strcmp(fd.name,"..")!=0;
			while(_findnext(hd,&fd)!=-1);
		}
		_findclose(hd);
		for(int i=cnt+1;i<=400;i++)system("drawer.exe");
		slen=0;
		hd=_findfirst("C:\\Users\\Administrator\\Desktop\\zzzz\\present\\THUWC2017T3\\drawer10\\sheep\\new\\*",&fd);
		do
		{
			if(strcmp(fd.name,".")==0||strcmp(fd.name,"..")==0)continue;
			slen++;
			strcpy(fn,"C:\\Users\\Administrator\\Desktop\\zzzz\\present\\THUWC2017T3\\drawer10\\sheep\\new\\");
			strcat(fn,fd.name);
			FILE *fp=fopen(fn,"r");
			for(int i=1;i<=n;i++)fscanf(fp,"%d",&S[slen].Ans[i]);
			fclose(fp);
			strcpy(fn,"C:\\Users\\Administrator\\Desktop\\zzzz\\present\\THUWC2017T3\\drawer10\\sheep\\old\\");
			strcat(fn,fd.name);
			fp=fopen(fn,"w");
			for(int i=1;i<=n;i++)fprintf(fp,"%d\n",S[slen].Ans[i]);
			fclose(fp);
		}while(_findnext(hd,&fd)!=-1);
		_findclose(hd);
		system("del C:\\Users\\Administrator\\Desktop\\zzzz\\present\\THUWC2017T3\\drawer10\\sheep\\new /q");
		sslen=0;
		for(int i=1;i<=slen;i++)
		{
			for(int j=i+1;j<=slen;j++)
			{
				SS[++sslen]=cross(S[i],S[j]);
				if(SS[sslen].live())
				{
					SS[sslen].grow();
					SS[sslen].calc();
				}
				else sslen--;
			}
		}
		sort(SS+1,SS+sslen+1,cmp);
		for(int i=1;i<=300&&i<=sslen;i++)
		{
			sprintf(fn,"C:\\Users\\Administrator\\Desktop\\zzzz\\present\\THUWC2017T3\\drawer10\\sheep\\new\\%d",SS[i].f);
			FILE *fp=fopen(fn,"w");
			for(int j=1;j<=n;j++)fprintf(fp,"%d\n",SS[i].Ans[j]);
			fclose(fp);
		}
	}
	return 0;
}
#include<cstdio>
#include<cstring>
using namespace std;
struct node
{
	int l,r,lc,rc;
	unsigned A,B,C,AB,AC,BC,ABC;
	unsigned X,Y,Z;
}tr[210000];int len;
inline void update(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	tr[x].A=tr[lc].A+tr[rc].A;
	tr[x].B=tr[lc].B+tr[rc].B;
	tr[x].C=tr[lc].C+tr[rc].C;
	tr[x].AB=tr[lc].AB+tr[rc].AB;
	tr[x].AC=tr[lc].AC+tr[rc].AC;
	tr[x].BC=tr[lc].BC+tr[rc].BC;
	tr[x].ABC=tr[lc].ABC+tr[rc].ABC;
}
inline void changeA(int x,unsigned X)
{
	tr[x].X=X;
	tr[x].A=X*(unsigned)(tr[x].r-tr[x].l+1);
	tr[x].AB=X*tr[x].B;
	tr[x].AC=X*tr[x].C;
	tr[x].ABC=X*tr[x].BC;
}
inline void changeB(int x,unsigned Y)
{
	tr[x].Y=Y;
	tr[x].B=Y*(unsigned)(tr[x].r-tr[x].l+1);
	tr[x].AB=Y*tr[x].A;
	tr[x].BC=Y*tr[x].C;
	tr[x].ABC=Y*tr[x].AC;
}
inline void changeC(int x,unsigned Z)
{
	tr[x].Z=Z;
	tr[x].C=Z*(unsigned)(tr[x].r-tr[x].l+1);
	tr[x].AC=Z*tr[x].A;
	tr[x].BC=Z*tr[x].B;
	tr[x].ABC=Z*tr[x].AB;
}
inline void pushdown(int x)
{
	int lc=tr[x].lc,rc=tr[x].rc;
	if(tr[x].X!=0)
	{
		changeA(lc,tr[x].X);
		changeA(rc,tr[x].X);
		tr[x].X=0;
	}
	if(tr[x].Y!=0)
	{
		changeB(lc,tr[x].Y);
		changeB(rc,tr[x].Y);
		tr[x].Y=0;
	}
	if(tr[x].Z!=0)
	{
		changeC(lc,tr[x].Z);
		changeC(rc,tr[x].Z);
		tr[x].Z=0;
	}
}
void bt(int l,int r)
{
	len++;int now=len;
	tr[now].l=l;tr[now].r=r;tr[now].lc=tr[now].rc=-1;
	tr[now].A=tr[now].B=tr[now].C=tr[now].AB=tr[now].AC=tr[now].BC=tr[now].ABC=tr[now].X=tr[now].Y=tr[now].Z=0;
	if(l<r)
	{
		int mid=(l+r)/2;
		tr[now].lc=len+1;bt(l,mid);
		tr[now].rc=len+1;bt(mid+1,r);
	}
}
void changeA(int now,int l,int r,unsigned X)
{
	if(tr[now].l==l&&tr[now].r==r){changeA(now,X);return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)changeA(lc,l,r,X);
	else if(l>=mid+1)changeA(rc,l,r,X);
	else changeA(lc,l,mid,X),changeA(rc,mid+1,r,X);
	update(now);
}
void changeB(int now,int l,int r,unsigned Y)
{
	if(tr[now].l==l&&tr[now].r==r){changeB(now,Y);return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)changeB(lc,l,r,Y);
	else if(l>=mid+1)changeB(rc,l,r,Y);
	else changeB(lc,l,mid,Y),changeB(rc,mid+1,r,Y);
	update(now);
}
void changeC(int now,int l,int r,unsigned Z)
{
	if(tr[now].l==l&&tr[now].r==r){changeC(now,Z);return ;}
	int lc=tr[now].lc,rc=tr[now].rc;
	int mid=(tr[now].l+tr[now].r)/2;
	pushdown(now);
	if(r<=mid)changeC(lc,l,r,Z);
	else if(l>=mid+1)changeC(rc,l,r,Z);
	else changeC(lc,l,mid,Z),changeC(rc,mid+1,r,Z);
	update(now);
}
unsigned a[110000],b[110000],c[110000];
int sta[110000],tap,stb[110000],tbp,stc[110000],tcp;
int main()
{
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%u",&a[i]);
	for(int i=1;i<=n;i++)scanf("%u",&b[i]);
	for(int i=1;i<=n;i++)scanf("%u",&c[i]);
	unsigned ss=0;
	sta[0]=stb[0]=stc[0]=0;
//MMM
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]<=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]<=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]<=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss+=tr[1].ABC;
	}
//MMm
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]<=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]<=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]>=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss-=tr[1].ABC;
	}
//MmM
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]<=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]>=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]<=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss-=tr[1].ABC;
	}
//Mmm
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]<=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]>=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]>=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss+=tr[1].ABC;
	}
//mMM
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]>=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]<=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]<=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss-=tr[1].ABC;
	}
//mMm
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]>=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]<=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]>=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss+=tr[1].ABC;
	}
//mmM
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]>=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]>=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]<=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss+=tr[1].ABC;
	}
//mmm
	len=0;bt(1,n);
	tap=tbp=tcp=0;
	for(int i=1;i<=n;i++)
	{
		while(tap>0&&a[sta[tap]]>=a[i])tap--;
		while(tbp>0&&b[stb[tbp]]>=b[i])tbp--;
		while(tcp>0&&c[stc[tcp]]>=c[i])tcp--;
		changeA(1,sta[tap]+1,i,a[i]);
		changeB(1,stb[tbp]+1,i,b[i]);
		changeC(1,stc[tcp]+1,i,c[i]);
		sta[++tap]=i;
		stb[++tbp]=i;
		stc[++tcp]=i;
		ss-=tr[1].ABC;
	}
	printf("%u\n",ss);
	return 0;
}

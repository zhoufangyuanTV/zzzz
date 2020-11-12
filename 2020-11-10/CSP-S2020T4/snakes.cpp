#include<cstdio>
#include<cstring>
using namespace std;
int a[1010000];
struct node
{
    int x,p;
}list[1010000];
inline bool operator<(node x,node y){return x.x==y.x?x.p<y.p:x.x<y.x;}
int main()
{
	freopen("snakes.in","r",stdin);
	freopen("snakes.out","w",stdout);
    int n,t;scanf("%d",&t);
    for(int tt=1;tt<=t;tt++)
    {
        if(tt==1)
        {
            scanf("%d",&n);
            for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        }
        else
        {
            int cc;scanf("%d",&cc);
            for(int i=1;i<=cc;i++)
            {
                int x,y;
                scanf("%d%d",&x,&y);
                a[x]=y;
            }
        }
        int head=1,tail=0,h=1,t=n;
        bool bk=false;int g=0;
        for(int i=1;i<n;i++)
        {
            node ax,in;
            if(head<=tail&&(h>t||(node){a[t],t}<list[head]))ax=list[head++];
            else
            {
                ax=(node){a[t],t};
                t--;
            }
            if(head<=tail&&(h>t||list[tail]<(node){a[h],h}))in=list[tail--];
            else
            {
                in=(node){a[h],h};
                h++;
            }
            ax.x=ax.x-in.x;
            if(i!=n-1&&(h<=t&&ax<(node){a[h],h}||h>t))
            {
                bk=true;g++;
            }
            else if(bk==true)
            {
                g=n-i+g+g%2;
                break;
            }
            list[++tail]=ax;
        }
        if(g==0)printf("%d\n",1);
        else printf("%d\n",g);
    }
    return 0;
}
#include<iostream>
#include<algorithm>
using namespace std;
int rank[101];
int v[101];
void make_set(int x)//³õÊ¼»¯
{
    v[x]=x;
    rank[x]=0;
}
int find_set(int x)
{
    if(v[x]!=x) v[x]=find_set(v[x]);
    return v[x];
}
void Union(int x,int y)
{
    if(rank[x]>rank[y])
        v[y]=x;
    else if(rank[x]<rank[y])
        v[x]=y;
    else if(rank[x]==rank[y])
    {
        v[x]=y;
        rank[y]++;
    }
}
struct Edge
{
    int x,y,w;
} e[1001];
bool cmp(Edge e1,Edge e2)
{
    if(e1.w<e2.w) return true;
    else return false;
}
int main()
{
    int n,m,s1,s2;
    int i,j,ans;
    cin>>n>>m;
    for(i=0; i<m; i++)
        cin>>e[i].x>>e[i].y>>e[i].w;
    sort(e,e+m,cmp);
    for(i=1; i<=n; i++) v[i]=i;
    ans=0;
    for(i=0; i<m; i++)
    {
        s1=find_set(e[i].x);
        s2=find_set(e[i].y);
        if(s1!=s2)
        {
            ans+=e[i].w;
            Union(s1,s2);
        }
    }
    cout<<ans<<endl;
    return 0;
}

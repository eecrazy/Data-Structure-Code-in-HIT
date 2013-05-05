#include<iostream>
using namespace std;
#include <cstdio>
#include <queue>
#include <string.h>
struct point
{
    int z,x,y,count;
};
int dir[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};
char c[30][30][30],str[30];
int l,r,c1;
point start,finish;
int cc[30][30][30];
int bfs()
{
    memset(cc,0,sizeof(cc));
    point pre,cur;
    start.count = 0;
    queue<point> q;
    q.push(start);
    cc[start.z][start.x][start.y] = 1;
    while(!q.empty())
    {
        pre = q.front();
        q.pop();
        if(pre.x == finish.x&&pre.y == finish.y&&pre.z == finish.z)
            return pre.count;
        for(int i = 0; i < 6; i++)
        {
            cur.z = pre.z + dir[i][0];
            cur.x = pre.x + dir[i][1];
            cur.y = pre.y + dir[i][2];
            if(cur.z<0||cur.z>=l||cur.x<0||cur.x>=r||cur.y<0||cur.y>=c1)continue;
            if(cc[cur.z][cur.x][cur.y]==1)continue;
            if(c[cur.z][cur.x][cur.y]=='#')continue;
            cc[cur.z][cur.x][cur.y] = 1;
            cur.count = pre.count + 1;
            q.push(cur);
        }
    }
    return -1;
}

int main()
{
    while(scanf("%d%d%d",&l,&r,&c1)!=EOF)
    {
        if(l+r+c1==0)break;
        getchar();
        for(int i=0; i<l; i++)
        {
            for(int j=0; j<r; j++)
            {
                for(int k=0; k<c1; k++)
                {
                    scanf("%c",&c[i][j][k]);
                    if(c[i][j][k]=='S')
                    {
                        start.z=i;
                        start.x=j;
                        start.y=k;
                    }
                    if(c[i][j][k]=='E')
                    {
                        finish.z=i;
                        finish.x=j;
                        finish.y=k;
                    }
                }
                getchar();
            }
            getchar();
        }
        int ans;
        if(start.z==finish.z&&start.x==finish.x&&start.y==finish.y)
            ans=0;
        else
            ans=bfs();
        if(ans>=0)printf("Escaped in %d minute(s).\n",ans);
        else printf("Trapped!\n");
    }
}
/* 
3 4 5
S....
.###.
.##..
###.#

#####
#####
##.##
##...

#####
#####
#.###
####E

1 3 3
S##
#E#
###

0 0 0
*/
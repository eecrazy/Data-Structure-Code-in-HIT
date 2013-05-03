#include<iostream>
#include<stdio.h>
#define MAX 100
using namespace std;

//样例邻接矩阵
int map[5][5]=
{
    {0,1,1,0,0},
    {0,0,0,1,0},
    {0,0,0,0,1},
    {0,0,0,0,0},
    {0,0,0,0,0}
};
int n=5;
int CountCD()
{
    int flag,count=0;
    for(int i=0;i<n;i++)
    {
        flag=0;
        for(int j=0;j<n;j++)
        {
            if(map[i][j]==1)
            flag=1;
        }
        if(flag==0)
        count++;
    }
    return count;
}
int CountRD()
{
    int flag,count=0;
    for(int i=0;i<n;i++)
    {
        flag=0;
        for(int j=0;j<n;j++)
        {
            if(map[j][i]==1)
            flag=1;
        }
        if(flag==0)
        count++;
    }
    return count;
}
int main()
{
   cout<<"出度为零的顶点个数为："<<CountCD()<<endl;
   cout<<"入度为零的顶点个数为："<<CountRD()<<endl;

}

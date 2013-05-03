/*若矩阵Am×n中的某个元素aij是第i行的最小值，
同时又是第j列中的最大值，则称此元素为该矩阵中的一个马鞍点。
假设以二维数组存储矩阵Am×n，试编写求出矩阵中一个马鞍点的算法，
并分析你的算法的最坏情况下的时间复杂度
*/
#include<stdio.h>
int main()
{
    int n, m, i, j, k, l, minn, maxx, flag ;
    int a[256][256];
    while(1)
    {
        printf("请输入矩阵的行列数：\n");
        scanf("%d %d",&n,&m);
        printf("请输入与行列数相符的矩阵：\n");
        for(i=0; i<n; i++)
            for(j=0; j<m; j++)
                scanf("%d",&a[i][j]);
        flag=0;
        printf("马鞍点输出(输出该点所在的行数与列数)：\n");
        for(i=0; i<n; i++)
        {
            for( j = 0; j < m; j++)
            {
                minn = a[i][j];
                for( k = 0 ; k < m; k++)
                {
                    if( minn > a[i][k])
                        break;
                }
                if( k==m)
                {
                    maxx=a[i][j];
                    for(l=0; l<n; l++)
                    {
                        if(maxx<a[l][j])
                            break;
                    }
                    if(l==n)
                    {
                        printf("%d %d %d\n",i , j ,a[i][j]);
                        flag = 1;
                    }
                }
            }
        }
        if(flag==0)
            printf("此矩阵没有马鞍点\n");
    }
    return 0;
}
/*
请输入矩阵的行列数：
5 5
请输入与行列数相符的矩阵
9 5 3 4 8
8 4 5 1 7
5 4 7 2 3
5 8 6 2 1
4 5 7 6 9
马鞍点输出（输出该点所有的行数与列数）：
此矩阵没有马鞍点
输出矩阵的行列数：
4 5
请输入与行列数相符的矩阵：
6 2 9 2 3
4 3 5 4 2
9 6 8 7 9
2 0 4 5 6
马鞍点输出（输出该点所在的行数与列数）：
2 1 6
*/



/*求马鞍点的C++算法

      若矩形Am*n中的某个元素Aij是第i行的最小值，同时又是第j列的最大值，则称此元素是该矩阵的一个马鞍点。假设以二维数组存储矩阵，试编写程序求出矩阵的所有马鞍点。
       求马鞍点的算法如下，希望大家支持！

#include <iostream.h>

#define N 100

void main()

{

   int i,j,k,m,n,c,flag,min;

   int a[N][N];

   flag=0;

   cout<<"请输入矩阵的行数:  ";  //输入矩阵的行数

    cin>>m;

   cout<<"请输入矩阵的列数:  ";  //输入矩阵的列数

    cin>>n;

   cout<<"请输入矩阵:"<<endl;

 //输入矩阵，元素间以空格隔开，回车换行

  for(i=0;i<m;i++)

     for(j=0;j<n;j++)

      {

         cin>>a[i][j];

       }

  cout<<"您输入的矩阵是:"<<endl;

   for(i=0;i<m;i++)  //显示当前输入的矩阵

     {   for(j=0;j<n;j++)

           {    cout<<a[i][j];

             }

        cout<<endl;

      }

  for(i=0;i<m;i++)

    {

       min=a[i][0];

       c=0;

       for(j=0;j<n;j++)       //找出i行中的最小值

         if(a[i][j]<min)

           {

              min=a[i][j];

              c=j;

            }

       for(j=0;j<n;j++)

         {   if(a[i][j]==min)  //找出i行中所有最小值

              {

               for(k=0;k<m;k++)  //对所有min进行列比较

                 if(a[k][j]>min)  break;

                if(k==m)  //min为马鞍点

                 {  c=j;

                    cout<<"该矩阵的马鞍点是:"<<a[i][c]<<endl;

                    flag=1;

                  }

               }

          }

     }

  if(flag==0)

     cout<<"该矩阵没有马鞍点!"<<endl;

}*/

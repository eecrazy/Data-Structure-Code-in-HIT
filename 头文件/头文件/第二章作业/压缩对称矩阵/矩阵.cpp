#include <iostream>
#include <cstdio>
using namespace std;
void compute(const int *A,const int *B,const int &n)
{
    cout<<"A与B矩阵的乘积为："<<endl;
    int M1,M2,M3,M4,sum;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            sum=0;
            for(int k=1;k<=n;k++)
            {
                M1=max(i,k);
                M2=min(i,k);
                M3=max(j,k);
                M4=min(j,k);
                sum+=A[M1*(M1-1)/2+M2-1]*B[M3*(M3-1)/2+M4-1];
            }
            cout<<sum<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    int i,j,key;
    int n,len;
    int *A,*B;
    cout<<"输入对称矩阵的维数：";
    cin>>n;
    len=(1+n)*n/2;
    A=new int[len];
    B=new int[len];
    cout<<"输入A矩阵数据（格式：每行一组数据，分别为行，列，值。如：2 3 4 表示第2行第3列的值是3）";
    cout<<"输入0 0 0输入结束"<<endl;
    cin>>i>>j>>key;
    while(i||j||key)
    {
        if(i>=j)
            A[i*(i-1)/2+j-1]=key;  //根据数据所在的行列，存储到相应的一维数组
        else
            A[j*(j-1)/2+i-1]=key;
        cin>>i>>j>>key;
    }
    cout<<"输入B矩阵数据（格式：每行一组数据，分别为行，列，值。如：2 3 4 表示第2行第3列的值是3）";
    cout<<"输入0 0 0输入结束"<<endl;
    cin>>i>>j>>key;
    while(i||j||key)
    {
        if(i>=j)
            B[i*(i-1)/2+j-1]=key;  //根据数据所在的行列，存储到相应的一维数组
        else
            B[j*(j-1)/2+i-1]=key;
        cin>>i>>j>>key;
    }
    compute(A,B,n);
    return 0;
}
/*
1 2 3
2 1 1
3 1 1

1 1 1
1 2 2
1 3 3
2 2 1
2 3 1
3 3 1
0 0 0
*/

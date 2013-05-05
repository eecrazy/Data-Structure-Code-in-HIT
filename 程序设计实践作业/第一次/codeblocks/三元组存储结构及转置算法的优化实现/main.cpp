#include<iostream>
#include<iomanip>
using namespace std;
#define MAXSIZE 12500
typedef struct
{
    int i,j;
    int e;

} Triple;
typedef struct
{
    Triple data[MAXSIZE+1];//非零元三元组表，data[0]未用
    int mu,nu,tu;//矩阵的行数，列数和非零元个数

} TSMatrix;
void initTS(TSMatrix &X)
{
    cout<<"请输入矩阵的行数、列数和非零元个数："<<endl;
    cin>>X.mu>>X.nu>>X.tu;
    cout<<"请输入矩阵元素："<<endl;
    for(int p=1; p<=X.tu; p++)
    {
        cout<<"请输入第 "<<p<<"个非零元素的行数、列数、与数值:";
        cin>>X.data[p].i;
        cin>>X.data[p].j;
        cin>>X.data[p].e;
        cout<<endl;
    }
}
void print(TSMatrix X)
{
    cout<<"现在的矩阵为："<<endl;
    for(int k=1; k<=X.tu; k++)
    {
        cout<<X.data[k].i<<" "<<X.data[k].j<<" "<<X.data[k].e<<endl;
    }
}
void TransposeSM(TSMatrix X,TSMatrix &T)//一般转置算法
{
    T.mu=X.nu;
    T.nu=X.mu;
    T.tu=X.tu;
    if(T.tu)
    {
        int q=1;
        for(int col=1; col<=X.nu; ++col) //注意不忘了等于
            for(int p=1; p<=X.tu; ++p)
                if(X.data[p].j==col)
                {
                    T.data[q].i=X.data[p].j;
                    T.data[q].j=X.data[p].i;
                    T.data[q].e=X.data[p].e;
                    ++q;
                }
    }
}


int main()
{
    TSMatrix X,T;
    initTS(X);
    print(X);
    TransposeSMatrix(X,T);
    cout<<"矩阵X的转置矩阵为："<<endl;
    print(T);
    return 0;
}

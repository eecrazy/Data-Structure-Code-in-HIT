#include<iostream>
#include<iomanip>
using namespace std;
#define MAXSIZE 12500
typedef struct
{
    int i,j;//该非零元的行下标和列下标
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
    cout<<"正在对矩阵进行转置！"<<endl;
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
//采用此算法时引用两个辅助数组num[],cpot[],
//num[col]表示矩阵M中第col列中非零元的个数，
//cpot[col]指示M中第col列的第一个非零元在b.data中的恰当位置。
//（即指M中每一列的第一个非零元在B中表示为第几个非零元）
void FastTransposeSMatrix(TSMatrix M,TSMatrix &T)   //快速转置算法
{
    int p,q,t,col,*num,*cpot;
    num=(int*)malloc((M.nu+1)*sizeof(int));
    cpot=(int*)malloc((M.nu+1)*sizeof(int));
    T.mu=M.nu;T.nu=M.mu;T.tu=M.tu;
    if(T.tu)
    {
        for(col=1;col<=M.nu;++col)
            num[col]=0;
        for(t=1;t<=M.tu;++t)
            ++num[M.data[t].j];
        cpot[1]=1;
        for(col=2;col<=M.nu;++col)
            cpot[col]=cpot[col-1]+num[col-1];
                for(p=1;p<=M.tu;++p)
                {
                    col=M.data[p].j;
                    q=cpot[col];
                    T.data[q].i=M.data[p].j;
                    T.data[q].j=M.data[p].i;
                    T.data[q].e=M.data[p].e;
                    ++cpot[col];
                }
    }
    free(num);free(cpot);
}

int main()
{
    TSMatrix X,T;
    initTS(X);
    print(X);
    TransposeSM(X,T);
    cout<<"矩阵X的转置矩阵为："<<endl;
    print(T);
    return 0;
}

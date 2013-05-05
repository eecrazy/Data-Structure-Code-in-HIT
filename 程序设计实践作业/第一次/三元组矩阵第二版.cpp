#include<iostream>
using namespace std;

#define MAX_MATRIXSIZE 20
#define ElemType int

class Triple//三元组类
{
public:
	int i,j;//行列号
	ElemType e;//元素值
};

class TSMatrix//矩阵类
{
public:
	TSMatrix();
	Triple matrix[MAX_MATRIXSIZE];//三元组集合 
	int mu,nu,tu;//行数，列数，非零元个数
};

TSMatrix::TSMatrix()
{
	mu=nu=tu=0;
}

class Matrix//矩阵类封装了有关矩阵的各种操作
{
public:
	void GetMatrix();//得到矩阵的三元组
	void TransposeSMatrix();//矩阵转置
	void PrintMatrix();//打印矩阵
private:
	void PrintMatrix(Triple[]);//重载函数用于打印转置矩阵
	void GetCpot(int[]);//求转置矩阵时用于求得辅助数组Cpot的值
	TSMatrix m;//实例化一个矩阵类的对象
};

void Matrix::GetMatrix()//得到矩阵的三元组
{
	cout<<"Please Input The Size Of The Matrix(m*n)"<<endl;
	cin>>m.mu>>m.nu;
	cout<<"Please Input Matrix With Increasing Order Of RowNumber"<<endl
		<<"rownum columnnum element"<<endl<<endl;
	int i,j;
	ElemType e;
	while(cin>>i>>j>>e)
	{
		m.matrix[m.tu].i=i;
		m.matrix[m.tu].j=j;
		m.matrix[m.tu].e=e;
		m.tu++;
	}
	cin.clear();
}

void Matrix::GetCpot(int Cpot[])//求转置矩阵时用于求得辅助数组Cpot的值
{
	int num[MAX_MATRIXSIZE];
	memset(num,0,sizeof(num));
	for(int i=0;i<m.tu;i++)
		num[m.matrix[i].j]++;
	Cpot[1]=1;
	for(int i=2;i<m.nu;i++)
		Cpot[i]=Cpot[i-1]+num[i-1];
}

void Matrix::TransposeSMatrix()//矩阵转置
{
	int Cpot[MAX_MATRIXSIZE];
	GetCpot(Cpot);
	Triple temp[MAX_MATRIXSIZE];
	for(int i=0;i<m.tu;i++)
	{
		temp[Cpot[m.matrix[i].j]-1].i=m.matrix[i].j;
		temp[Cpot[m.matrix[i].j]-1].j=m.matrix[i].i;
		temp[Cpot[m.matrix[i].j]-1].e=m.matrix[i].e;
		Cpot[m.matrix[i].j]++;
	}
	cout<<endl;
	PrintMatrix(temp);
}

void Matrix::PrintMatrix()//打印矩阵
{
	for(int i=0;i<m.tu;i++)
		cout<<m.matrix[i].i<<" "<<m.matrix[i].j<<" "<<m.matrix[i].e<<endl;
}

void Matrix::PrintMatrix(Triple t[])//重载函数用于打印转置矩阵
{
	for(int i=0;i<m.tu;i++)
		cout<<t[i].i<<" "<<t[i].j<<" "<<t[i].e<<endl;
}
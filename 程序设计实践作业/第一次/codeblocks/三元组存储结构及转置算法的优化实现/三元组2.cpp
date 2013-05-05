#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#define OK 1
#define ERROR 0
#define OVERFLOW 0
#define MAXSIZE 100
#define MAXRC 100
typedef int ElemType;
typedef struct
{
	int i,j;
	ElemType e;
}Triple;
typedef struct
{
	Triple data[MAXSIZE+1]; //非零元三元组
	int rpos[MAXRC+1];      //各行第一个非零元的位置表
	int mu,nu,tu;             //矩阵的行数、列数和非零元个数
}RLSMatrix;

CreateSMatrix(RLSMatrix &M)     //创建稀疏矩阵M
{
	int i,m,n;
	ElemType e;
	int k,j;
	printf("输入矩阵的行数、列数、非零元的个数：");
	scanf("%d%d%d",&M.mu,&M.nu,&M.tu);
	M.data[0].i=0;
	for(i=1;i<=M.tu;i++)
	{
		j=0;
		do
		{
			j++;
			if(j>3)     //控制跳出死循环
			{
				printf("本次输入失败！");
				return ERROR;
			}
			printf("按行序输入第%d个非零元素所在的行(1~%d)列(1~%d)值：",i,M.mu,M.nu);
			scanf("%d%d%d",&m,&n,&e);
			k=0;
			if(m<1||m>M.mu||n<1||n>M.nu)       //行或列超出范围
				k=1;
			if(m<M.data[i-1].i||m==M.data[i-1].i&&n<M.data[i-1].j)
				k=1;
		}while(k);
		M.data[i].i=m;
		M.data[i].j=n;
		M.data[i].e=e;
	}      //end for
	printf("\n");
	return(OK);
}
void DestroySMatrix(RLSMatrix &M)    //销毁稀疏矩阵M
{
	M.mu=0;
	M.nu=0;
	M.tu=0;
}
void PrinRLSMatrix(RLSMatrix M)        //遍历稀疏矩阵 M
{
	int i;
	printf("稀疏矩阵对应的三元组表为：\n\n");
	printf("行 列 元素值、\n\n");
	for(i=1;i<=M.tu;i++)
		printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
	printf("\n\n");
}
void print(RLSMatrix A)      //打印矩阵函数，以通常形式输出矩阵   
{
	int k=1,a,b;
    printf("稀疏矩阵的通常形式为：\n");
	int M[MAXSIZE][MAXSIZE];
	for(a=0;a<A.mu;a++)        //初始化矩阵M
	{
		for(b=0;b<A.nu;b++)
			M[a][b]=0;
	}
	while(k<=A.tu)
	{
		M[A.data[k].i-1][A.data[k].j-1]=A.data[k].e;
		k++;
	}
	for(a=0;a<A.mu;a++)
	{
		printf("  |  ");
		for(b=0;b<A.nu;b++)
			printf("%d ",M[a][b]);
		printf("  |  \n");
	}
}
void  showtip()     //菜单
{
	printf("          ********************请选择要执行的操作********************\n\n");
	printf("          &    1  采用一般算法实现                                  &\n");
	printf("          &    2  采用快速转置的算法实现                            &\n");
	printf("          &    3 同时采用两种算法，先显示一般算法，再显示快速算法   &\n");
	printf("          **********************************************************\n\n");
}
////头文件结束
TransposeSMatrix(RLSMatrix M,RLSMatrix &T)  //求稀疏矩阵M的转置矩阵T(一般算法)
{
	int p,q,col;
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu)
	{
		q=1;
		for(col=1;col<=M.nu;++col)   //按列序求转置
			for(p=1;p<=M.tu;++p)
				if(M.data[p].j==col)
				{
					T.data[q].i=M.data[p].j;
					T.data[q].j=M.data[p].i;
					T.data[q].e=M.data[p].e;
					++q;
				}
	}
	return OK;
}
FastTransposeSMatrix(RLSMatrix M,RLSMatrix &T)    //快速转置算法
{
	int p,q,t,col,*num,*cpot;
	num=(int*)malloc((M.nu+1)*sizeof(int));
	cpot=(int*)malloc((M.nu+1)*sizeof(int));
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu)
	{
		for(col=1;col<=M.nu;++col)
			num[col]=0;
		for(t=1;t<=M.tu;++t)
			++num[M.data[t].j];
		cpot[1]=1;
		for(col=2;col<=M.nu;++col)
			cpot[col]=cpot[col-1]+num[col-1];
		printf("\n辅助数组的值为：\n");
		printf("列号：");
			for(t=1;t<=M.nu;++t)
				printf("%4d",t);
				printf("\n");
				printf("num[]");
				for(t=1;t<=M.nu;++t)
					printf("%4d",num[t]);
				printf("\n");
				printf("cpot[]");
				for(t=1;t<=M.nu;++t)
					printf("%4d",cpot[t]);
				printf("\n\n");
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
	free(num);
	free(cpot);
	return OK;
}
int main()
{
	int result;
	int j;
	RLSMatrix A,B;
	//************************************************
	COORD Co={0,0};DWORD Write;
	SetConsoleTitle("稀疏矩阵的转置\n");
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
	FillConsoleOutputAttribute(hOut,FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY,100000000,Co,&Write);
	///windows的API函数，用来设置控制台标题
	do
	{

		showtip();     //调用菜单函数
		int i;
		scanf("%d",&i);
			switch(i)
			{
			case 1:
				printf("创建矩阵A：");
				if((result=CreateSMatrix(A))==0)
					exit(ERROR);
				PrinRLSMatrix(A);
				printf("求A的转置矩阵B(一般算法)：\n");
				TransposeSMatrix(A,B);
				PrinRLSMatrix(B);
				print(B);
				DestroySMatrix(B);
        		printf("\n\n");break;
			case 2:
				printf("创建矩阵A：");
				if((result=CreateSMatrix(A))==0)
					exit(ERROR);
        		PrinRLSMatrix(A);
				printf("求A的转置矩阵B(快速转置):\n");
				FastTransposeSMatrix(A,B);
				PrinRLSMatrix(B);
				print(B);
				DestroySMatrix(A);
        		DestroySMatrix(B);
				printf("\n\n");break;
			case 3:
                printf("创建矩阵A：");
				if((result=CreateSMatrix(A))==0)
					exit(ERROR);
                PrinRLSMatrix(A);
                printf("求A的转置矩阵B------(一般算法)：\n");
                TransposeSMatrix(A,B);
				PrinRLSMatrix(B);
				print(B);
                DestroySMatrix(B);
        		printf("\n\n");
                printf("求A的转置矩阵B------(快速转置):\n");
				FastTransposeSMatrix(A,B);
				PrinRLSMatrix(B);
				print(B);
				DestroySMatrix(A);
        		DestroySMatrix(B);
				printf("\n\n");break;
			}
		printf("               **********请选择是否继续输入其他稀疏矩阵？**********\n");
		printf("                         1  是，输入其他矩阵\n");
		printf("                         0 否，不输入\n");
		printf("               ****************************************************");
		fflush(stdin);//清除输入缓存区
		scanf("%d",&j);
	}while(j==1);
	

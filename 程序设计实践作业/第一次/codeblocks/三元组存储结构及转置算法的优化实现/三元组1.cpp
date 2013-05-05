#include <stdio.h>
#include <stdlib.h>

#define Status int
#define OK 1
#define ERROR 0

#define OVERFLOW -2

#define TRUE 1
#define FALSE 0

#define MAXSIZE 1250

#define ROW 3 /*行列可以自定*/
#define COLUM 3

typedef int ElemType;

ElemType Matrix[ROW][COLUM];
ElemType Matrix2[COLUM][ROW];

typedef struct
{
    int i,j;
    ElemType e;
}Triple;/*三元组存储结构*/

typedef struct
{
    Triple data[MAXSIZE+1]; /*非零元三元组表,data[0]未用*/
    int mu,nu,tu;
}TSMatrix;

Status CreateMatrix(TSMatrix *tsm)
{
    int i,j;

    tsm->mu = ROW;
    tsm->nu = COLUM;
    tsm->tu = 0;

    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COLUM;j++)
    {
            if(Matrix[i][j]!=0)
       {
                tsm->data[tsm->tu+1].i=i;
                tsm->data[tsm->tu+1].j=j;
                tsm->data[tsm->tu+1].e=Matrix[i][j];
                tsm->tu++;
       }
    }
    }
}

void inputTSMatrix()
{
    int i,j,k,l;
    ElemType e;
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COLUM;j++)
    {
            printf("(%d,%d):",i+1,j+1);
            scanf("%d",&Matrix[i][j]);
            printf("\n");
    }
    }
}


void outputTSMatrix(TSMatrix tsm)
{
    int i,j;

    for(i=0;i<COLUM;i++)
    {
        for(j=0;j<ROW;j++)
    {
            Matrix2[i][j]=0;
    }
    }


    for(i=1;i<=tsm.tu;i++)
    {
        Matrix2[tsm.data[i].i][tsm.data[i].j]=tsm.data[i].e;
    }

    printf("\n");
    for(i=0;i<COLUM;i++)
    {
        for(j=0;j<ROW;j++)
    {
            printf("%5d",Matrix2[i][j]);
    }
        printf("\n");
    }

}

Status FastTransposeTSMatrix(TSMatrix M,TSMatrix *tsm) /*快速转置算法*/
{
    int col,t,p,q;
    int num[MAXSIZE],cpot[MAXSIZE];

    tsm->mu = M.nu;
    tsm->nu = M.mu;
    tsm->tu = M.tu;

    if(tsm->tu)
    {
        for(col=0;col<M.nu;col++)
    {
            num[col]=0;
    }
        for(t=1;t<=M.tu;t++)
    {
            num[M.data[t].j]++;
    }

        cpot[0]=1;

        for(col=1;col<M.nu;col++)
    {
            cpot[col]=cpot[col-1]+num[col-1];
    }

        for(p=1;p<=M.tu;p++)
    {
            col = M.data[p].j;
            q = cpot[col];
            tsm->data[q].i = M.data[p].j;
            tsm->data[q].j = M.data[p].i;
            tsm->data[q].e = M.data[p].e;
            cpot[col]++;
    }
    }
    return OK;
}

main()
{
    TSMatrix A,B;
    inputTSMatrix();
    CreateMatrix(&A);
    FastTransposeTSMatrix(A,&B);
    outputTSMatrix(B);
    getch();
}
#ifndef POLYNOMINAL_CLASS
#define POLYNOMINAL_CLASS
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//多项式结点
typedef struct polynode
{
    float coef;
    int   power;
}PolyNode;

//多项式链表表示存储结构: f(x)=an*x^n+an-1*x^n-1+...+a3*x^3+a2*x^2+a1*x^1+a0*x^0
typedef struct polynomial
{
    PolyNode info;
    polynomial *next;
}PolyNomial;


/************************************************************************/
/*                     在多项式上增加一个结点                             */
/************************************************************************/
PolyNomial *AddNewItem(PolyNomial *polynomialExpress,polynode item)
{
    PolyNomial *p=polynomialExpress;
    if(p==NULL)
    {
        p=(PolyNomial*)malloc(sizeof(polynomial));
        p->info=item;
        p->next=NULL;
        return p;
    }
    else
    {
        int flag=0; //标记item是否在多项式中存在
        for (PolyNomial *temp=p; temp!=NULL;temp=temp->next)
        {
            if(temp->info.power==item.power)   //如果指数相同，增item与polynomialExpress相加
            {
                flag=1;
                temp->info.coef+=item.coef;
                return polynomialExpress;
            }
        }
        if(flag==0)
        {
            PolyNomial *t=(PolyNomial *)malloc(sizeof(polynomial));
            t->info=item;
            t->next=p;
            return t;
        }
    }
}

/************************************************************************/
/*                      两个多项式相加或相减                             */
/************************************************************************/
PolyNomial *AddorSubPoly(polynomial first,polynomial second)
{

     for ( polynomial *temp=&second;temp!=NULL;temp=temp->next)
     {
         first=*AddNewItem(&first,temp->info);
     }
     return &first;
}

/************************************************************************/
/*                      两多项式相乘                                     */
/************************************************************************/
PolyNomial  *MultiplyPoly(polynomial first,polynomial seconds)
{
     polynomial *result=NULL;
     for(polynomial *tf=&first;tf!=NULL;tf=tf->next)
     {
         for (polynomial *ts=&seconds;ts!=NULL;ts=ts->next)
         {
             PolyNode *node=(PolyNode *)malloc(sizeof(PolyNode));
             node->power=tf->info.power+ts->info.power;
             node->coef=tf->info.coef*ts->info.coef;
             result=AddNewItem(result,*node);
         }
     }
    return result;
}

/************************************************************************/
/*                       求多项式的微分                                  */
/************************************************************************/
PolyNomial  *DiffPoly(PolyNomial poly)
{
    PolyNomial *result=NULL;
    for (PolyNomial *temp=&poly;temp!=NULL;temp=temp->next)
    {
        PolyNode *node=(PolyNode *)malloc(sizeof(polynode));
        node->coef=temp->info.power*temp->info.coef;
        node->power=temp->info.power-1;
        result=AddNewItem(result,*node);
    }
    return result;
}

/************************************************************************/
/*                       求多项式的积分                                  */
/************************************************************************/
PolyNomial  *IntPoly(polynomial poly)
{
    polynomial *result=NULL;
    for (polynomial *temp=&poly;temp!=NULL;temp=temp->next)
    {
        PolyNode *node=(PolyNode *)malloc(sizeof(PolyNode));
        node->coef=temp->info.coef/(temp->info.power+1);
        node->power=temp->info.power+1;
        result=AddNewItem(result,*node);
    }
    return result;
}

/************************************************************************/
/*                       计算给定值Value的多项式值f(Value)               */
/************************************************************************/
double EvaluatePoly(polynomial poly,double  value)
{
    double result=0;
    for (polynomial *temp=&poly;temp!=NULL;temp=temp->next)
    {
        result+=temp->info.coef*pow(value,temp->info.power);
    }
    return result;
}

/************************************************************************/
/*                       计算给定值的定积分的值                          */
/************************************************************************/
double DefIntPoly(polynomial poly,double lowwerBound,double UpperBound)
{
    double result;
    polynomial *intPoly=IntPoly(poly);
    result=EvaluatePoly(*intPoly,UpperBound)-EvaluatePoly(*intPoly,lowwerBound);
    return result;
}


/************************************************************************/
/*                       复合函数的值                                    */
/************************************************************************/
double CompositeFun(polynomial f,polynomial g,double Vaule)
{
    double result;
    result=EvaluatePoly(f,EvaluatePoly(g,Vaule));
    return result;
}

/************************************************************************/
/*                       创建多项式                                      */
/************************************************************************/
PolyNomial *CreatePoly()
{
     PolyNomial *polynomialExpress=NULL;
     printf("Input 0 will end the input!\n");
     while(1)
     {
         printf("InputPolynode:\n");
         //PolyNode *node=(PolyNode*)malloc(sizeof(PolyNode));
         PolyNode node;
         std::cin>>node.coef;
         std::cin>>node.power;
         if(node.coef==0) break;
         else
         {
            polynomialExpress=AddNewItem(polynomialExpress,node);
         }
     }
     return polynomialExpress;
}

/************************************************************************/
/*                       显示多项式                                      */
/************************************************************************/
void Display(PolyNomial polynomialExpress)
{
    printf("PloymialExpress IS:");
    for (polynomial *temp=&polynomialExpress; temp!=NULL; temp=temp->next)
    {
        if(temp->info.coef>=0)
        {
            std::cout<<"+"<<temp->info.coef<<"*x^"<<temp->info.power;
        }else
        {
            std::cout<<"-"<<temp->info.coef<<"*x^"<<temp->info.power;
        }
    }
    std::cout<<endl;
}
#endif

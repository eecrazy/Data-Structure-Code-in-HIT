#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
//多项式结点
struct node
{
    float coef;
    int   power;
};

typedef struct polynomial
{
    node info;
    polynomial *next;
}PolyNomial;

PolyNomial *AddNewItem(PolyNomial *polynomialExpress,node item)
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
        int flag=0;//标记item是否在多项式中存在
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

PolyNomial *AddorSubPoly(polynomial first,polynomial second)
{

     for(polynomial *temp=&second;temp!=NULL;temp=temp->next)
     {
         first=*AddNewItem(&first,temp->info);
     }
     return &first;
}
/* 两多项式相乘*/

PolyNomial  *MultiplyPoly(polynomial first,polynomial seconds)
{
     polynomial *result=NULL;
     for(polynomial *tf=&first;tf!=NULL;tf=tf->next)
     {
         for (polynomial *ts=&seconds;ts!=NULL;ts=ts->next)
         {
             node *node=(node *)malloc(sizeof(node));
             node->power=tf->info.power+ts->info.power;
             node->coef=tf->info.coef*ts->info.coef;
             result=AddNewItem(result,*node);
         }
     }
    return result;
}
double EvaluatePoly(polynomial poly,double  value)
{
    double result=0;
    for (polynomial *temp=&poly;temp!=NULL;temp=temp->next)
    {
        result+=temp->info.coef*pow(value,temp->info.power);
    }
    return result;
}
PolyNomial *CreatePoly()
{
     PolyNomial *polynomialExpress=NULL;
     printf("Input 0 will end the input!\n");
     while(1)
     {
         printf("Inputnode:\n");
         node node;
         cin>>node.coef;
         cin>>node.power;
         if(node.power<0) break;
         else
         {
            polynomialExpress=AddNewItem(polynomialExpress,node);
         }
     }
     return polynomialExpress;
}

void Display(PolyNomial polynomialExpress)
{
    printf("PloymialExpress IS:");
    polynomial *temp=&polynomialExpress;
    if(temp->info.coef>=0)
        {
            cout<<temp->info.coef<<"*x^"<<temp->info.power;
        }
        else
        {
            cout<<"-"<<temp->info.coef<<"*x^"<<temp->info.power;
        }
    temp=temp->next;
    for (temp; temp!=NULL; temp=temp->next)
    {
        if(temp->info.coef>=0)
        {
            cout<<"+"<<temp->info.coef<<"*x^"<<temp->info.power;
        }
        else
        {
            cout<<"-"<<temp->info.coef<<"*x^"<<temp->info.power;
        }
    }
    cout<<endl;
}
int main()
{
    PolyNomial *polynomialExpressA=CreatePoly();
    Display(*polynomialExpressA);
    //两个多项式相乘
    PolyNomial *polynomialExpressC=CreatePoly();
    Display(*polynomialExpressC);
    Display (*MultiplyPoly(*polynomialExpressA,*polynomialExpressC));
    return 0;
}

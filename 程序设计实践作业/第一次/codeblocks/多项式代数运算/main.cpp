#include"Polynominal.h"
#include<iostream>
using namespace std;

int main()
{
    PolyNomial *polynomialExpressA=CreatePoly();

    Display(*polynomialExpressA);

    //计算f(3)
    cout<<"fff"<<endl;
    std::cout<<EvaluatePoly(*polynomialExpressA,3);
    //计算复合函数
    /*PolyNomial *polynomialExpressB=CreatePoly();
    Display(*polynomialExpressB);
    std::cout<<CompositeFun(*polynomialExpressA,*polynomialExpressB,3);*/
    //微分f(x)'
    //Display(*DiffPoly(*polynomialExpressA));
    //多项式积分求解
    //Display(*IntPoly(*polynomialExpressA));\
    //定积分求解
    //std::cout<<DefIntPoly(*polynomialExpressA,1,3);
    //计算f(x)+g(x)
    PolyNomial *polynomialExpressB=CreatePoly();
    Display(*polynomialExpressB);
    PolyNomial *result=AddorSubPoly(*polynomialExpressA,*polynomialExpressB);
    Display(*result);
    //两个多项式相乘
    Display(*MultiplyPoly(*polynomialExpressA,*polynomialExpressB));
    system("pause");
    return 0;
}

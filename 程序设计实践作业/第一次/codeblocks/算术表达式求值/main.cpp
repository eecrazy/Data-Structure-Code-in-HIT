//用数组存放中缀和后缀表达式，借助自己实现的堆栈，实现从中缀到后缀的转换。 
//可以处理小数，但不能处理负数 
#include<iostream> 
#include<cstdio> 
#include"mystack.h"//自己实现的堆栈，写成头文件，包括堆栈的各种操作。 
//采用ADT模板类实现。 
using namespace std; 
//四则运算求值 
double Compute(double t1,double t2,char c) 
{ 
    switch(c) 
    { 
    case'+': 
        return t1+t2; 
    case'-': 
        return t1-t2; 
    case'*': 
        return t1*t2; 
    case'/': 
        return t1/t2; 
    default: 
        return 0; 
    } 
} 
//判断在栈内运算符的优先级 
int priority_in(char c) 
{ 
    switch(c) 
    { 
    case'+': 
        return 1; 
    case'-': 
        return 1; 
    case'*': 
        return 2; 
    case'/': 
        return 2; 
    case'(': 
        return 0; 
    case'#': 
        return -1; 
    default: 
        exit(1); 
    } 
} 
//判断在栈外运算符的优先级 
int priority_out(char c) 
{ 
    switch(c) 
    { 
    case'+': 
        return 1; 
    case'-': 
        return 1; 
    case'*': 
        return 2; 
    case'/': 
        return 2; 
    case'(': 
        return 3; 
    default: 
        exit(1); 
    } 
} 
//中缀表达式转后缀表达式过程 
void postfix(char *e1,char *e2) 
{ 
    stackType<char> OPER;//char类型的操作符栈 
    char C,X; 
    int i=0;//控制e1 
    int j=0;//控制e2 
    C=e1[i++]; 
    while(C!=0) 
    { 
        if((C>='0'&&  C<='9')||C=='.')  //如果是数字字符,直接加入到输出序列
e2中 
        { 
            e2[j++]=C; 
            if((e1[i]<'0'||e1[i]>'9')&&e1[i]!='.')//下一个不是数字字符 
                e2[j++]=' ';    //以空格分隔 
        } 
        else //是操作符 
        { 
            if(C==')') 
            { 
                //连续出栈，直到遇到'(' 
                while(!OPER.isEmptyStack()&&OPER.top()!='(') 
                { 
                    X=OPER.top(); 
                    OPER.pop(); 
                    cout<<"The  operator  in  the  stack  is:";OPER.display();                               
e2[j++]=X; 
                    e2[j++]=' '; 
                } 
                if(!OPER.isEmptyStack()) 
                { 
                X=OPER.top(); 
                OPER.pop(); 
                cout<<"The operator in the stack is:";OPER.display(); 
                } 
            } 
            else 
            { 
                //比较栈顶运算符和字符C的优先级 
                
while(!OPER.isEmptyStack()&&priority_in(OPER.top())>=priority_out(C)) 
                { 
                    //如果栈中的操作符的优先级大于或等于新的操作符 
                    //则将栈中操作符出栈，加入到输出序列e2中 
                    X=OPER.top(); 
                    OPER.pop(); 
                    cout<<"The operator in the stack is:";OPER.display(); 
                    e2[j++]=X; 
                    e2[j++]=' '; 
                } 
                OPER.push(C);//否则进栈 
                cout<<"The operator in the stack is:";OPER.display(); 
            } 
        } 
        C=e1[i++];//表达式的下一个字符 
    } 
    while(!OPER.isEmptyStack()) 
    { 
        //弹出栈中剩余的运算符号 
        X=OPER.top(); 
        OPER.pop(); 
        cout<<"The operator in the stack is:";OPER.display(); 
        e2[j++]=X; 
        e2[j++]=' '; 
    } 
    e2[j++]='#';//用‘#’控制是否处理到文件尾 
} 
//对后缀表达式求出运算结果 
double Evaluate(char *e2) 
{ 
    stackType<double> Double_stack; 
    char C; 
    int j=0; 
    int n,m=0,length=0; 
    C=e2[j++]; 
    while(C!='#')//’#'为结束标志 
    { 
        if(C>'0'&&C<='9')//碰到数字 
        { 
            n=C-'0';//数字字符到整数的转化 
            while(e2[j]!=' '&&e2[j]!='.') //处理多位数 
                n=n*10+(e2[j++]-'0'); 
            if(e2[j]=='.') 
            { 
                j++; 
                m=e2[j++]-'0'; 
                length++; 
                while(e2[j]!=' ') //处理多位数 
                { 
                    m=m*10+(e2[j++]-'0'); 
                    length++; 
                } 
            } 
            double a=(double)n; 
            if(length!=0) 
            a+=double(m)/(10.0*length); 
            Double_stack.push(a);//数字压栈 
            length=0;m=0; 
            if(!Double_stack.isEmptyStack()) 
            {cout<<"The stack is:";Double_stack.display();} 
        } 
        else//碰到运算符 
        { 
            double T2=Double_stack.top(); 
            Double_stack.pop(); 
            cout<<"The stack is:";Double_stack.display(); 
            double T1=Double_stack.top(); 
            Double_stack.pop(); 
            cout<<"The stack is:";Double_stack.display(); 
            double T=Compute(T1,T2,C);//对T1，T2进行求值运算 
            Double_stack.push(T);//求值结果继续入栈，供下一次使用 
            cout<<"The stack is:";Double_stack.display(); 
        } 
        C=e2[j++]; 
        if(C==' ')//跳过空格 
            C=e2[j++]; 
    } 
    double temp=Double_stack.top(); 
    Double_stack.pop(); 
    cout<<"The stack is:";Double_stack.display(); 
    return temp; 
} 
int main() 
{ 
    char ex1[100];//存放中缀表达式 
    char ex2[100];//存放后缀表达式 
    cout<<"Please input the infix string:"<<endl; 
    while(cin>>ex1)//循环输入 
    { 
        postfix(ex1,ex2);//进行中缀到后缀的转化 
        int i=0; 
 
        cout<<"The postfix is:"; 
        while(ex2[i]!='#') 
            cout<<ex2[i++]; 
        cout<<endl; 
 
        double result=Evaluate(ex2); 
        printf("The  result is:%lf\n",result); 
        cout<<"Please input the infix string:"<<endl; 
    } 
    return 0; 
} 
}
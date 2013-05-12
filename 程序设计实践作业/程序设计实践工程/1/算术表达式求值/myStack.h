
#ifndef H_StackType
#define H_StackType
#include <iostream>
#include <cassert>
using namespace std;
#define INCRE 50
template<class  Type>
class stackType
{
public:
    const stackType<Type>&operator = (const stackType<Type>&);
    void initializeStack();
    bool isEmptyStack();
    bool isFullStack();
    void destroyStack();
    void push(const Type& newItem);
    Type top();
    void pop();
    int size();
    void display();
    stackType(int stackSize=100);//默认构造函数
    stackType(const stackType<Type>& otherStack);//复制构造函数
    ~stackType();//析构函数
private:
    int maxStackSize;//最大元素个数
    int stackTop;//栈顶元素
    Type *list;//数组名
    void copyStack(const stackType<Type>& otherStack);//复制函数
  void larger();
};
//初始化
template<class  Type>
void stackType<Type>::initializeStack()
{
    stackTop=0;
}
template<class  Type>
void stackType<Type>::larger()
{
    maxStackSize+=INCRE;
}
//销毁栈
template<class  Type>
void stackType<Type>::destroyStack()
{
    stackTop=0;
}
//判断是否为空
template<class  Type>
bool stackType<Type>::isEmptyStack()
{
    return(stackTop==0);
}
//判断是否满栈
template<class  Type>
bool stackType<Type>::isFullStack()
{
    return(stackTop==maxStackSize);
}
//返回栈最大元素个数
template<class  Type>
int stackType<Type>::size()
{
    return maxStackSize;
}
//压栈
template<class  Type>
void stackType<Type>::push(const Type&newItem)
{
    if(!isFullStack())
    {
        list[stackTop++]=newItem;
    }
    else
    {
    Type *temp;
    larger();
    temp=new Type[maxStackSize];
    for(int i=0;i<stackTop;i++)
      temp[i]=list[i];
    temp[stackTop++]=newItem;
    delete []list;
    list=temp;
        //cout<<"cannot add to a full stack!"<<endl;
    }
}
//返回栈顶元素
template<class  Type>
Type stackType<Type>::top()
{
    if(stackTop==0)
    {
        cout<<"Stack is empty!"<<endl;
        return 0;
    }
    return list[stackTop-1];
}
//出栈
template<class  Type>
void stackType<Type>::pop()
{
    if(!isEmptyStack())
    {
        stackTop--;
    }
    else
        cout<<"Cannot remove from an empty stack!"<<endl;
}

//显示栈的内容
template<class  Type>
void stackType<Type>::display()
{
    if(stackTop==0)
    {
        cout<<"Stack is empty!"<<endl;
        return ;
    }
    int temp=stackTop;
    while(temp!=0)
    {
        cout<<list[--temp];
        if(temp!=0)
        cout<<" ";
    }
    cout<<endl;
}
//复制
template<class  Type>
void stackType<Type>:: copyStack(const stackType<Type>& otherStack)
{
    delete []list;
    maxStackSize=otherStack.maxStackSize;
    stackTop=otherStack.stackTop;
    list=new Type[maxStackSize];
    //assert(list!=NULL);
    for(int i=0; i<stackTop; i++)
    {
        list[i]=otherStack.list[i];
    }
}
//构造函数
template<class  Type>
stackType<Type>::stackType(int stackSize)
{
    if(stackSize<=0)
    {
        cout<<"The size of the array to hold the stack must be positive!"<<endl;
        cout<<"Creating an array of size 100"<<endl;
        maxStackSize=100;
    }
    else
    {
        maxStackSize=stackSize;
    }
    stackTop=0;
    list =new Type[maxStackSize];
    assert(list!=NULL);
}
//析构函数
template<class  Type>
stackType<Type>::~stackType()
{
    delete []list;
}
//复制构造函数
template<class  Type>
stackType<Type>::stackType(const stackType<Type>& otherStack)
{
    list=NULL;
    copyStack(otherStack);
}
//重载运算符‘=’
template<class  Type>
const  stackType<Type>&stackType<Type>::operator  =  (const
stackType<Type>&otherStack)
{
    if(this!=&otherStack)
    {
        copyStack(otherStack);
    }
    return *this;
}

#endif

#include<iostream>
#include <stack>
using namespace std;
void generate(int &a,int &k)
{
    stack<int> int_stack;
    while(a/k)
    {
        int_stack.push(a%k);
        a/=k;
    }
    int_stack.push(a%k);
    cout<<"转换后的数为:";
    while(!int_stack.empty())
    {
        cout<<int_stack.top();
        int_stack.pop();
    }
    cout<<endl;
}
int main()
{
    int a,k;
    cout<<"输入要转换的十进制数：";
    while(cin>>a)
    {
        cout<<"输入要转换的进制：";
        cin>>k;
        generate(a,k);
        cout<<"输入要转换的十进制数：";
    }
    return 0;
}

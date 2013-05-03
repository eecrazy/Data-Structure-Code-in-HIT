#include<iostream>
using namespace std;
#include<stack>
#include<string.h>
#include<algorithm>
#define LEN 100
int judge1(char ch)
{
    if(ch=='{')return 1;
    if(ch=='[')return 2;
    if(ch=='(')return 3;
    return 0;
}
int judge2(char ch)
{
    if(ch=='}')return 1;
    if(ch==']')return 2;
    if(ch==')')return 3;
    return 0;
}
int main()
{
    stack<char> char_stack;
    char str[100];
    while(cin>>str)
    {
        int flag=0;
        for(int i=0; i<strlen(str); i++)
        {
            if(judge1(str[i]))
            {
                char_stack.push(str[i]);
            }
            else
            {
                if(judge2(str[i]))
                {
                    if(!char_stack.empty()&&judge1(char_stack.top())==judge2(str[i]))
                    char_stack.pop();
                    else
                    {
                        cout<<"No!"<<endl;
                        flag=1;
                    }
                }
            }
            if(flag==1)
            break;
        }
        if(flag==1)continue;
        if(char_stack.empty())
        cout<<"Yes!"<<endl;
        else
        cout<<"No!"<<endl;
    }
}

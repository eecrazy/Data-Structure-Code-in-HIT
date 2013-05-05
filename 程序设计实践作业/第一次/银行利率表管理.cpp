//file:"array_list.h"  
#ifndef _ARRAYLIST_H_INCLUDE_  
#define _ARRAYLIST_H_INCLUDE_  
#include<cstdio>  
#define maxlen 1000  
template<typename Type>  
class  List  
{  
public:  
    List():list_last(0) {}//构造函数，线性表的开始长度为0  
    void Insert(int p,Type x)  
    {  
        if(list_last>=maxlen-1)  printf("list is full!\n");  
        else if((p>list_last+1)||(p<1))  
        {  
           printf("position is not exist!\n");  
        }  
        else  
        {  
            for(int i=list_last; i>=p; i--)  
            {  
                element[i+1]=element[i];  
            }  
            element[p]=x;  
            list_last++;  
        }  
    }  
    void Delete(int p)  
    {  
      if((p>list_last)||(p<1))   printf("position is not exist!\n");  
      else  
        {  
            list_last--;  
            for(int i=p;i<=list_last;i++)  element[i]=element[i+1];  
        }  
    }  
    int Locate(Type x)  
    {  
       for(int i=1;i<=list_last;i++)  
           if(element[i]==x)   return i;  
       return (list_last+1);  
    }  
    Type Retrieve(int p)  
    {  
      if(p>list_last)  printf("position is not exist!\n");  
      else   return element[p];  
    }  
    Type Previous(int p)  
    {  
       if((p<=1)||(p>list_last))  printf("Previous element is not exist!\n");  
       else return element[p-1];  
    }  
    Type Next(int p)  
    {  
      if((p<1)||(p>=list_last))  printf("Next element is not exist!\n");  
      else return element[p+1];  
    }  
    int End()  
    {  
       return (list_last+1);  
    }  
private:  
    int list_last;  
    Type element[maxlen];  
};  
#endif  


#include<iostream>  
#include<cstring>  
#include "array_list.h"  
using namespace std;  
struct rate  
{  
    char name[30];//银行名字  
    double current_rate;//活期利率  
};  
int main()  
{  
    freopen("in.txt","r",stdin);  
    List<rate>R;  
    struct rate x;  
    char na[30];  
    int N;  
    printf("1--插入\n2--删除\n3--查询\n4--打印\n0--退出\n");  
    while(cin >> N)  
    {  
        switch(N)  
        {  
        case 1:  
            int m;  
            cin >> m;//插入个数  
            for(int i=1; i<=m; i++)  
            {  
                cin >> x.name >> x.current_rate;  
                R.Insert(i,x);  
            }//插入的时候一直在后面插入  
            break;  
        case 2:  
            cin >> x.name;  
            for(int i=1; i<=R.End()-1; i++)  
                if(strcmp(R.Retrieve(i).name,x.name)==0)  R.Delete(i);  
            break;  
        case 3:  
            cin >> x.name;  
            for(int i=1; i<R.End(); i++)  
            {   www.2cto.com
                if(strcmp(R.Retrieve(i).name,x.name)==0)  
                    cout << R.Retrieve(i).current_rate << endl;  
            }  
            break;  
        case 4:  
            for(int i=1; i<R.End(); i++)  
                cout << R.Retrieve(i).name << "---" <<  R.Retrieve(i).current_rate << endl;  
                break;  
        case 0:  
            return 0;  
        }  
       printf("1--插入\n2--删除\n3--查询\n4--打印\n0--退出\n");  
    }  
    return 0;  
}  
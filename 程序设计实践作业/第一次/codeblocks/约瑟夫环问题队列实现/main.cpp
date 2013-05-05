#include<iostream>
using namespace std;
#include"Queue.h"
//1.	从队列头开始报数，报到1至m-1的人先从队首出队，再从队尾进队
//2.	报数报到m的人出队，不进队。并从下一个人开始接着从1开始报数。
//3.	继续上述过程，直到队列为空为止。

int main()
{
    int s,m,i,x;
	linkedQueueType<int> Q;

	cout<<"输入队列中的总人数：";
	cin>>s;
	cout<<"输入报数出列值：";
	cin>>m;

	for (i=1;i<=s;i++)
		Q.addQueue(i);
	cout<<"现在开始报数出列：";
	int Front;
	while(!Q.isEmptyQueue())
	{
		for(i=1;i<m;i++)
		{
		    Front=Q.front();
            Q.deleteQueue();
			Q.addQueue(Front);
		}
		Front=Q.front();
        Q.deleteQueue();
		cout<<Front<<" ";
	}
	cout<<"\n出列完毕！";
}

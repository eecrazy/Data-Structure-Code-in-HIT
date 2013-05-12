#include <iostream>
#include <cstdio>
using namespace std;
#define maxn 100005
struct node
{
	int data;
	node* next;
};
node* hash[maxn];
void init()
{
	for(int i=0;i<maxn;i++)
		hash[i]=NULL;
}
int h(int k)
{
	return k%maxn;
}
node* search(int k)
{
	node* str=hash[h(k)];
	while(str!=NULL)
	{
		if(str->data==k)
			return str;
		else
			str=str->next;
	}
	return str;
}
void insert(int r)
{
	int b;
	node* element;
	if(search(r)==NULL)
	{
		b=h(r);
		element=hash[b];
		hash[b]=new node;
		hash[b]->data=r;
		hash[b]->next=element;
	}
}
int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    init();
    int a;
    int arr[100000],i=0;;
    while (scanf("%d", &a) != EOF)
    {
        arr[i++]=a;
    }
    for(int j=0;j<i;j++)insert(arr[j]);
    start = clock();
    int num=0;
    for(int j=0;j<i;j++)
    {
        if(search(arr[j])!=NULL)
        num++;
    }
     printf("搜索到%d个数据\n",num);
    finish = clock();
    duration =(double)(finish - start) / CLOCKS_PER_SEC;
    printf("外散列搜索用时 %f seconds\n", duration );

}

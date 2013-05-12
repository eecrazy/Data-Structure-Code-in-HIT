#include<cstdio>
#include <iostream>
using namespace std;
int v[100005];
int n;
inline void swap(int k,int j)
{
    int temp=v[k];
    v[k]=v[j];
    v[j]=temp;
}
void qsort(int left,int right)
{
    int j,last,m;
    if(left>=right)
        return;

    swap(left,(left+right)/2);
    last=left;
    for(j=left+1; j<=right; j++)
    {
        if(v[j]<v[left])
        {

            last+=1;
            if(last==j)continue;
            swap(last,j);
        }
    }
    swap(left,last);
    qsort(left,last-1);
    qsort(last+1,right);
}

int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)
            scanf("%d", &v[i]);
        start=clock();
        qsort(0,n);
        finish = clock();
        duration =(double)(finish - start) / CLOCKS_PER_SEC;
        printf("快速排序用时: %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//            printf("%d ", v[i]);
        puts("");
    }
}














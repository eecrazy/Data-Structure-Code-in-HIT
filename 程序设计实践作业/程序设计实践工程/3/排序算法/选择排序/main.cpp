#include <cstdio>
#include <iostream>
using namespace std;
int a[100010];
int n;

void SelectSort()
{
    int lowkey; //当前最小关键字
    int i, j,lowindex; //当前最小关键字的下标
    for (i = 1; i < n; i++) //在A[i…n]中选择最小的关键字，与A[i]交换
    {
        lowindex = i ;
        lowkey = a[i];
        for ( j = i + 1; j <= n; j++)
            if (a[j] < lowkey) //用当前最小关键字与每个关键字比较
            {
                lowkey = a[j] ;
                lowindex = j ;
            }
        swap(a[i], a[lowindex]) ;
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    while (scanf("%d", &n) != EOF)
    {
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        start = clock();
        SelectSort();
        finish = clock();
        duration =(double)(finish - start) / CLOCKS_PER_SEC;
        printf("选择排序用时 %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//            printf("%d ", a[i]);
        puts("");
    }
}

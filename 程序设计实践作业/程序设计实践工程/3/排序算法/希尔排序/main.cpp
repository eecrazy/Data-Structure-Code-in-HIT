#include <cstdio>
#include <string.h>
#include <iostream>
using namespace std;
#define inf 1000000000
int A[100005];
int n;
void ShellSort()
{
    int i, j, d;
    for (d = n / 2; d >= 1; d = d / 2)
    {
        for (i = d + 1; i <= n; i++) //将A[i]插入到所属的子序列中
        {
            A[0] = A[i]; //暂存待插入记录
            j = i - d; //j指向所属子序列的最后一个记录
            while (j > 0 && A[0] < A[j])
            {
                A[j + d] = A[j]; //记录后移d个位置
                j = j - d; //比较同一子序列的前一个记录
            }
            A[j + d] = A[0];
        }
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    while (scanf("%d", &n) != EOF)
    {
        memset(A, 0, sizeof(A));
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        start = clock();
        ShellSort();
        finish = clock();
        duration =(double)(finish - start) / CLOCKS_PER_SEC;
        printf("希尔排序用时 %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//            printf("%d ", A[i]);
        puts("");
    }
}

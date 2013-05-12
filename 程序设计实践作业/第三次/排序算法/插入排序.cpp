#include <cstdio>
#include <iostream>
using namespace std;
#define inf 100000000
int A[100005];
int n;
void InsertSort ()
{
    int i, j ;
    A[0]=-inf;//哨兵
    for (i = 1; i <= n; i++)
    {
        j = i;
        while (A[j] < A[j - 1])
        {
            swap(A[j], A[j - 1]) ;
            j = j - 1;
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
        InsertSort();
        finish = clock();
        duration =(double)(finish - start) / CLOCKS_PER_SEC;
        printf("插入排序用时 %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//            printf("%d ", A[i]);
        puts("");
    }
}

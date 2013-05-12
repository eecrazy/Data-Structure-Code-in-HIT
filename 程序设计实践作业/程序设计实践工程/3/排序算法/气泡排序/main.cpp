#include <cstdio>
#include <iostream>
using namespace std;
int a[100005];
int n;
void BubbleSort()
{
    for(int i=1; i<=n-1; i++)
    {
        for(int j=n; j>=i+1; j--)
        {
            if(a[j]<a[j-1])
                swap(a[j],a[j-1]);
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
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++)
            scanf("%d", &a[i]);
        start = clock();
        BubbleSort();
        finish = clock();
        duration =(double)(finish - start) / CLOCKS_PER_SEC;
        printf("ÆøÅÝÅÅÐòÓÃÊ± %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//            printf("%d ", a[i]);
        puts("");
    }
}

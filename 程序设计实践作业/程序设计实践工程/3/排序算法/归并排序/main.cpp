#include <iostream>
using namespace std;
#define MAX 1000000000
int a[500001];
int tmp[500001];
long long ans;
void Mergesort(int b, int e)
{
    if (e - b <= 0) return;
    int mid = (b + e) / 2, p1 = b, p2 = mid + 1, i = b;
    Mergesort(b, mid);
    Mergesort(mid + 1, e);
    while (p1 <= mid || p2 <= e)
    {
        if (p2 > e || (p1 <= mid && a[p1] <= a[p2]))
            tmp[i++] = a[p1++];
        else
        {
            tmp[i++] = a[p2++];
            ans += (mid - p1 + 1);
        }
    }
    for (i = b; i <= e; i++)a[i] = tmp[i];
}
int main()
{
    freopen("in.txt", "r", stdin);
    clock_t start, finish;
    double duration;
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        scanf("%d",&a[i]);
    ans = 0;
    start=clock();
    Mergesort(1, n);
    finish = clock();
    duration =(double)(finish - start) / CLOCKS_PER_SEC;
    printf("Mergesort: %f seconds\n", duration );
//        for (int i = 1; i <= n; i++)
//        printf("%d ",a[i]);
    puts("");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int a[100005];
int n;

int RadixCountSort(int* npIndex, int nMax, int* a, int n)
{
    int* pnCount  = (int*)malloc(sizeof(int)* nMax);        //保存计数的个数
    for (int i = 0; i < nMax; ++i)
    {
        pnCount[i] = 0;
    }
    for (int i = 0; i < n; ++i)    //初始化计数个数
    {
        ++pnCount[npIndex[i]];
    }

    for (int i = 1; i < 10; ++i)  //确定不大于该位置的个数。
    {
        pnCount[i] += pnCount[i - 1];
    }

    int * pnSort  = (int*)malloc(sizeof(int) * n);    //存放零时的排序结果。

    //注意：这里i是从n-1到0的顺序排序的，是为了使排序稳定。
    for (int i = n - 1; i >= 0; --i)
    {
        --pnCount[npIndex[i]];
        pnSort[pnCount[npIndex[i]]] = a[i];
    }

    for (int i = 0; i < n; ++i)        //把排序结构输入到返回的数据中。
    {
        a[i] = pnSort[i];
    }
    free(pnSort);                        //记得释放资源。
    free(pnCount);
    return 1;
}

//基数排序
int RadixSort(int* a, int n)
{
    //申请存放基数的空间
    int* aRadix    = (int*)malloc(sizeof(int) * n);

    int nRadixBase = 1;    //初始化倍数基数为1
    bool nIsOk = false; //设置完成排序为false
    while (!nIsOk)
    {
        nIsOk = true;
        nRadixBase *= 10;
        for (int i = 0; i < n; ++i)
        {
            aRadix[i] = a[i] % nRadixBase;
            aRadix[i] /= nRadixBase / 10;
            if (aRadix[i] > 0)
            {
                nIsOk = false;
            }
        }
        if (nIsOk) //如果所有的基数都为0，认为排序完成，就是已经判断到最高位了。
        {
            break;
        }
        RadixCountSort(aRadix, 10, a, n);
    }

    free(aRadix);

    return 1;
}

int main()
{
    //测试基数排序。
    freopen("in.txt","r",stdin);
    clock_t start, finish;
    double duration;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    scanf("%d",&a[i]);
    start=clock();
    RadixSort(a, n);
    finish = clock();
    duration =(double)(finish - start) /CLOCKS_PER_SEC;
    printf("基数排序用时: %f seconds\n", duration );
//    for (int i = 0; i < n; ++i)
//    {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
    return 0;
}

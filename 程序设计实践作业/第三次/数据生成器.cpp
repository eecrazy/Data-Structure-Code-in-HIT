#include <cstdio>
#include <stdlib.h>
#include <time.h>
#define maxn 100000
int main()
{
    freopen("in.txt","w",stdout);
    srand(time(0));
    int a=1,b;
    while(a<=maxn)
    {
        b=rand()%maxn+1;
        printf("%d\n",b);
        a++;
    }
}

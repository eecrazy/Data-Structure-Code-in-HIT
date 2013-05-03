#include<iostream>
using namespace std;
#define MAX 1000000000
int a[500001];
int left[500001];
int right[500001];
long long ans;//逆序数
void merge(int p,int q,int r)
{
    int   n1=q-p+1;
    int   n2=r-q;
    int   i,j,k;
    long left[n1+1];
    long right[n2+1];

    for(i=1; i<=n1; i++)
        left[i]=a[p+i-1];
    for(j=1; j<=n2; j++)
        right[j]=a[q+j];

    left[n1+1]=1e9;    //设置一个哨兵
    right[n2+1]=1e9; //同上
    i=1;
    j=1;
    for(k=p; k<=r; k++)
    {
        if(left[i]<right[j])
            a[k]=left[i++];
        else
        {
            a[k]=right[j++];
            ans+=n1-i+1;      //计数；
        }
    }
}
void mergesort(int p,int r)
{
    if(p<r)
    {
        int q=(p+r)/2;
        mergesort(p,q);
        mergesort(q+1,r);
        merge(p,q,r);    //合并步骤 p<=left<=q q<right<=r；
    }
}
int main()
{
    int n;
    while(cin>>n,n)
    {
        for(int i=1; i<=n; i++)
            cin>>a[i];
        ans=0;
        mergesort(1,n);
        cout<<ans<<endl;
    }
    return 0;
}

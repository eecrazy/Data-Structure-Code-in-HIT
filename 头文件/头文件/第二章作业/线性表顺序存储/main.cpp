#include <stdlib.h>
#include <iostream>
using namespace std;
#define LIST_INIT_SIZE 100//线性表存储空间的初始分配量
typedef int ElemType;
typedef int Status;


typedef struct//用户自定义结构体SqList
{
    ElemType *elem; //指针指向存储空间基址
    int length;
    int listsize;
} SqList;

//线性表初始化
Status Initlist_Sq(SqList &L) {
    L.elem = (ElemType *) malloc(LIST_INIT_SIZE * sizeof (ElemType));
    return 1;
}

//input 操作
Status Input(SqList &L, int n) {
    cout << "input n status into the struct:" << endl;
    for (int i = 0; i < n; i++)
        cin >> L.elem[i];
    L.length =  n;
    return 1;
}

//output 操作
Status Output(SqList &L) {
    for (int i = 0; i < L.length; i++)
        cout << L.elem[i] << " ";
    cout << endl;
    return 1;
}

//Insert操作
int *p, *q, *e;
Status Insert(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1)
        return 0; //i的值不合法
    q = &(L.elem[i - 1]); //q为插入地址
    for (p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p + 1) = *p; //插入元素后移
    *q = e;
    ++L.length;
    return 1;
}

//Delete操作
Status Delete(SqList &L, int i, ElemType &e) {
    if ((i < 1) || (i >= L.length))
        return 0;
    p = &(L.elem[i - 1]);
    e = *p;
    q = L.elem + L.length - 1;
    for (++p; p <= q; ++p) *(p - 1) = *p;
    --L.length;
    return 1;
}

//Search操作
int Search(SqList L, ElemType f) {
    int i = 1;
    p = L.elem;
    while ((i <= L.length) && !((*p++) == f)) i++;
    if (i <= L.length) return i;
    else return 0;
}

int main() {
    int num, post, k, e, j, f;
    SqList chart;
    Initlist_Sq(chart);
    cout << "the number of status in the chart (num<=100): " << endl;
    cin >> num;
    Input(chart, num);
    cout << "the linear form is:" << endl;
    Output(chart);
    cout << "please input the insert position (before the ith status) and status:" << endl;
    cin >> post >> k;
    Insert(chart, post, k);
    cout << "the linear form after insert is:" << endl;
    Output(chart);
    cout << "please input the delete position:" << endl;
    cin >> j;
    Delete(chart, j, e);
    cout << "the linear form after delete is:" << endl;
    Output(chart);
    cout << "the status being deleted is " << e << endl;
    cout << "please input status f that will be searched: " << endl;
    cin >> f;
    cout << "the position of f in the linear form is: " << Search(chart, f) << endl;
   int a;
   cin >> a;
   return 0;
}


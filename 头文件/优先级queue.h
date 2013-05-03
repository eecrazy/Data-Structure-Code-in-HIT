/*这里实现的是最小优先级队列，T类型必须可以进行<操作.*/
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <iostream>
#include <iomanip>
#include <assert.h>
using namespace std;
enum Priority_Queue_Type { Maximum_Priority_Queue, Minimum_Priority_Queue};
template< typename T >
class Priority_Queue
{
public:
    Priority_Queue(int maxSize = 20, Priority_Queue_Type type = Minimum_Priority_Queue);
    void enqueue( T *ele );
    void dequeue( T *ele );
    T top();
    void test();
private:
    inline int parent( int i );
    int heap_size;
    int max_size;
    T *heap;
    Priority_Queue_Type type;
};
enum Heap_Type { MAX_HEAP, MIN_HEAP };
template<typename T>
void build_heap( T *array, const int length, Heap_Type type )
{
    int i;
    for( i = length/2; i >= 0; --i )
    {
        heapify( array, length, i, type );
    }//注意第一个非叶子节点的序号
}
//注意数组中第i（从0开始）个元素的左孩子和右孩子的序号
template<typename T>
void heapify( T *array, const int length, int i, Heap_Type type )
{
    if( i < length )
    {
        int extre_ele_index;
        extre_ele_index = i;
        if( i*2+1 < length )//左孩子
        {
            if( type == MAX_HEAP )
            {
                if( array[extre_ele_index] < array[ i*2+1 ] )
                    extre_ele_index = i*2+1;
            }
            else
            {
                if( array[extre_ele_index ] > array[ i*2+1 ] )
                    extre_ele_index = i*2+1;
            }
        }
        if( i*2+2 < length )//右孩子
        {
            if( type == MAX_HEAP )
            {
                if( array[extre_ele_index] < array[ i*2+2 ] )
                    extre_ele_index = i*2+2;
            }
            else
            {
                if( array[extre_ele_index ] > array[ i*2+2 ] )
                    extre_ele_index = i*2+2;
            }
        }
        if( extre_ele_index != i )
        {
            T extre_ele;
            extre_ele = array[i];
            array[i] = array[extre_ele_index];
            array[extre_ele_index] = extre_ele;
            heapify( array, length, extre_ele_index, type );
        }
    }
}
template <typename T>
Priority_Queue<T>::Priority_Queue( int maxSize,Priority_Queue_Type type)
    :heap_size(0), max_size(maxSize)
{
    heap = new T[maxSize];
    this->type = type;
}
template <typename T>
void Priority_Queue<T>::enqueue( T *ele )
{
    if( heap_size+1 > max_size )//堆已满，需重新分配
    {
        T *old_heap = heap;
        heap = new T[ max_size*2 ];
        for( int i = 0; i < heap_size; ++i )
            heap[i] = old_heap[i];
        delete old_heap;
        old_heap = NULL;
    }
    heap[heap_size] = *ele;
    int cur_index = heap_size;
    int par_index = parent( heap_size );
    ++heap_size;
    if( type == Minimum_Priority_Queue )
        while( par_index >= 0 && heap[cur_index] < heap[par_index]  )
        {
            T tmp = heap[cur_index];
            heap[cur_index] = heap[par_index];
            heap[par_index] = tmp;
            cur_index = par_index;
            par_index = parent( cur_index );
        }
    else//最大优先级队列.
    {
        while( par_index >= 0 && heap[cur_index] > heap[par_index]  )
        {
            T tmp = heap[cur_index];
            heap[cur_index] = heap[par_index];
            heap[par_index] = tmp;
            cur_index = par_index;
            par_index = parent( cur_index );
        }
    }
}
template <typename T>
void Priority_Queue<T>::dequeue( T *ele )
{
    heap[0] = heap[heap_size-1];
    --heap_size;
    if( type == Minimum_Priority_Queue )
        heapify( heap, heap_size, 0, MIN_HEAP );
    else
        heapify( heap, heap_size, 0, MAX_HEAP );
}
template <typename T>
T Priority_Queue<T>::top()
{
    return heap[0];
}
template <typename T>
void Priority_Queue<T>::test()
{
    for( int i = 0; i < heap_size; ++i )
        if( this->type == Maximum_Priority_Queue )
        {
            if( 2*i+1 < heap_size )
                assert( heap[i] > heap[2*i+1] );
            if(2*i+2 < heap_size )
                assert( heap[i] > heap[2*i+2] );
        }
        else
        {
            if( 2*i+1 < heap_size )
                assert( heap[i] < heap[2*i+1] );
            if(2*i+2 < heap_size )
                assert( heap[i] < heap[2*i+2] );
        }
}
template <typename T>
int Priority_Queue<T>::parent( int i )
{
    return i%2== 0 ? (i-2)/2 : (i-1)/2;
}
/*下标为奇数的元素为左孩子,偶数为右孩子
下标为i的元素的左孩子为(2*i+1),右孩子为(2*i+2);i从0开始。
根据这个式子反推就可以了
*/
#endif

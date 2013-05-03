#include<cstdio>

#include<queue>

#include<cstring>

#include<bitset>

using namespace std;

const int kind = 26;

const int maxn = 70000;

int root,tot;

char ch[1010];

int n,m;

struct Node

{

    int child[kind];

    int fail;

    int id;

    void init()

    {

        memset(child,0,sizeof(child));

        fail = -1 , id = 0;

    }

} T[maxn];

int que[maxn],head,tail;

void init()

{

    root = tot = 0;

    T[root].init();

}

void insert(char *s,int id)

{

    int p = root,index;

    while(*s)

    {

        index = *s - 'a';

        if(!T[p].child[index])

        {

            T[++tot].init();

            T[p].child[index] = tot;

        }

        p = T[p].child[index];

        s++;

    }

    T[p].id = id;

}

void build_ac_auto()

{

    head = tail = 0;

    que[tail ++] = root;

    while(head < tail)

    {

        int u = que[head++];

        for(int i = 0 ; i < kind ; i ++)

        {

            if(T[u].child[i])

            {

                int son = T[u].child[i];

                int p = T[u].fail;

                if(u == root) T[son].fail = root;

                else T[son].fail = T[p].child[i];

                que[tail++] = son;

            }

            else //trie图，设定虚拟节点

                int p = T[u].fail;

            if(u == root)

                T[u].child[i] = root;

            else

                T[u].child[i] = T[p].child[i];

        }

    }

}

int main()

{

    init();

    scanf("%d",&n);

    for(int i = 0 ; i < n ; i ++)

    {

        scanf("%s",ch);

        insert(ch,i);

    }

    build_ac_auto();

}




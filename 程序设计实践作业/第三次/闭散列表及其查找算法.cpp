#define N 1001
int hash[N];

int h(int k)
{
	return (k%N+51)%N;
}


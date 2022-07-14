#include <stdio.h>

#define M 7
int main()
{
	int c[M] = {1, 2, 3, 4, 5, 6, 7};
	int a[M]={};

	for (int i = 0; i < M; ++i)
	{
		a[i]=c[M-i-1];
		printf("%d ", a[i]);
	}
}

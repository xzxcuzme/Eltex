#include <stdio.h>
#include <math.h>

#define N 9
int main()
{

	int c[N][N] = {};
	int y, x, a=1, d=1, q=1;

	printf("Длинна массива: %zu\n", sizeof(c)/sizeof(int));


	for (int y = 0; y < N-1; ++y)
	{
		c[0][y]=q;
		q++;
	}

	for (int x = 0; x < N; ++x)
	{
		c[x][N-1]=q;
		q++;
	}

	for (int y = N-2; y >=0; --y)
	{
		c[N-1][y]=q;
		q++;
	}

	for (int x = N-2; x >0; --x)
	{
		c[x][0]=q;
		q++;
	}

	if (N!=1)
	{

		while (q<pow(N, 2))
		{
			while (c[a][d+1]==0)
			{
				c[a][d]=q;
				q++;
				d++;
			}

			while (c[a+1][d]==0)
			{
				c[a][d]=q;
				q++;
				a++;
			}

			while (c[a][d-1]==0)
			{
				c[a][d]=q;
				q++;
				d--;
			}

			while (c[a-1][d]==0)
			{
				c[a][d]=q;
				q++;
				a--;
			}
		}
	}

	for (int x = 0; x < N; ++x)
	{
		for (int y = 0; y < N; ++y)
		{
			if (c[x][y]==0)
			{	
				c[x][y]=q;
			}
		}
	}


	for (int i = 0; i < N; ++i)
	{
		for (int y = 0; y < N; ++y)
		{	
			if (c[i][y] < 10)
			{
				printf("%d  ", c[i][y]);
			} else {
				printf("%d ", c[i][y]);
			}
			
		}
		printf("\n");
	}

}

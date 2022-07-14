#include <stdio.h>

#define M 5
int main()
{

	int c[M][M] = {};

	printf("Длинна массива: %zu\n", sizeof(c)/sizeof(int));

	for (int i = 0; i < M; ++i)
	{
		for (int y = 0; y < M; ++y)
		{	
			// if ((i<2 && y<2) && (M-2!=i || M-2!=y))
			if (i+y<=M-2)
			{
				c[i][y]=0;
			} 
			else	{
				c[i][y]=1;
			}
			
			printf("%d ", c[i][y]);
		}
		printf("\n");

	}

}

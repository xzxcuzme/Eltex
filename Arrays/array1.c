#include <stdio.h>

#define M 3
int main()
{

	int c[M][M] = {};
	int x=1;
	int z;

	printf("Длинна массива: %zu\n", sizeof(c)/sizeof(int));

	for (int i = 0; i < M; ++i)
	{
		for (int y = 1; y < M; ++y)
		{	
			z=y;
			c[i][y]=x++;
			printf("%d ", c[i][y]);
		}
		c[i][z]=x++;
		
		printf("%d\n", c[i][z]);

	}

}

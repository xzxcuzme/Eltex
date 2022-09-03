#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	printf("'%s'  argc = %d\n", __FUNCTION__, argc);

	if (argc != 3)
	{
		printf("'%s'Error!! argc = %d\n", __FUNCTION__, argc);
		return -1;
	}

	for (int i = 1; i < argc; ++i)
	{
		printf("----%s----(%d)\n", argv[i], i);
	}

	return 0;
}
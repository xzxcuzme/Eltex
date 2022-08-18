#include <stdio.h>
#include <pthread.h>

void *func(void *arg) {
	int *ptr = (int*)arg;
	printf("%d\n", *ptr);
	//return;
}

int main(void)
{
	pthread_t tid[5];
	int i;
	int *s;
	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&tid[i], NULL, func, (void *) &i);
	}
	for (int i = 0; i < 5; ++i)
	{
		pthread_join(tid[i], (void **)&s);
	}
	return 0;
}
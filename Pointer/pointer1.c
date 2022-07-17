#include <stdio.h>

int main(void)
{
	char a = 'A';
	char *ptr;

	ptr=&a;

	printf("ptr = %p\n", ptr);
	printf("*ptr = %c\n", *ptr);
}
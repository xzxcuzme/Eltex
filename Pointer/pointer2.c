#include <stdio.h>

int main(void)
{
	int a = 270533154;
	char *ptr;


	ptr = (char*)&a;

	printf("First byte of a = %d\n", *ptr);
	ptr++;	
	printf("Second byte of a = %d\n", *ptr);
	ptr++;

	*ptr=88;
		

	printf("Third byte of a = %d\n", *ptr);
	ptr++;
	printf("Fourth byte of a = %d\n", *ptr);
} 
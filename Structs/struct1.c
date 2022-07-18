#include <stdio.h>

int main()
{
	struct test
	{
		char a;
		int b;
	};

	struct test my_test;

	my_test.a='A';
	my_test.b=123;

	printf("%ld\n", sizeof(struct test));
	
	printf("%c\n", my_test.a);
	printf("%d\n", my_test.b);
}
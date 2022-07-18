#include <stdio.h>

int main()
{
	struct test
	{
		unsigned char b1:1;
		unsigned char b2:1;
		unsigned char b3:1;
		unsigned char b4:1;
		unsigned char b5:1;
		unsigned char b6:1;
		unsigned char b7:1;
		unsigned char b8:1;
	};

	struct test test;
	char a = 0b11011001;
	struct test *ptr;

	ptr = (struct test *) &a;

	printf("%p\n", ptr);
	// printf("%c\n", *ptr);
	ptr -> b5 = 1;
	printf("%c\n", test.b5);

	// printf("%ld\n", sizeof(test));
	
}  
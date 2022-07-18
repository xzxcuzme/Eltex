#include <stdio.h>

int main()
{
	struct test
	{
		char a;
		int b;
	};

	struct test st;
	struct test *ptr;

	ptr = &st;
	ptr->a='A'; //(*ptr).a='A';
	ptr->b=12345; //(*ptr).b=12345;

	printf("%c\n", st.a);
	printf("%d\n", st.b );

	struct test a ={0};
	struct test b ={.a = 8, .b = 100};


	printf("%d%d\n", a.a, a.b);
	printf("%d%d\n", b.a, b.b);

	struct test *ptr_to_struct = &b;

	a = *ptr_to_struct;

	printf("%d%d\n", a.a, a.b);
	printf("%d%d\n", b.a, b.b);

}
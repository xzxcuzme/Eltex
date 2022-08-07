#include <stdio.h>
#include "calc.h"

int main()
{
	while (1) 
	{
		enum math {
			MATH_SUM=1,
			MATH_DIFF,
			MATH_INC,
			MATH_DIV,
			MATH_EXIT
		};
		short x;
		int a, b;
		fflush(stdin);
		printf("1. Сложить\n2. Вычесть\n3. Умножить\n4. Разделить\n5. Выход\n");
		scanf("%hd%*c", &x);
		
		switch(x)
		{
			case MATH_SUM:
				printf("Первое слагаемое\n");
				scanf("%d%*c", &a);

				printf("Второе слагаемое\n");
				scanf("%d%*c", &b);
				printf("Сумма: %d\n", sum(a, b));
				break;
			case MATH_DIFF:
				printf("Первое слагаемое\n");
				scanf("%d%*c", &a);

				printf("Второе слагаемое\n");
				scanf("%d%*c", &b);
				printf("Разность: %d\n", diff(a, b));
				break;
			case MATH_INC:
				printf("Первое слагаемое\n");
				scanf("%d%*c", &a);

				printf("Второе слагаемое\n");
				scanf("%d%*c", &b);
				printf("Произведение: %d\n", inc(a, b));
				break;
			case MATH_DIV:
				printf("Первое слагаемое\n");
				scanf("%d%*c", &a);

				printf("Второе слагаемое\n");
				scanf("%d%*c", &b);
				printf("Частное: %d\n", div(a, b));
				break;
			case MATH_EXIT:
				return 0;
			default: 
				break;
		}	
	}
	return 0;
}
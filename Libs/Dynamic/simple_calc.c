#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "sum.h"
#include "diff.h"
#include "inc.h"
#include "divn.h"

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
		void *handle;
		short x;
		int a, b;
		char *error;
		double (*powerfunc)(double x);
		fflush(stdin);
		printf("1. Сложить\n2. Вычесть\n3. Умножить\n4. Разделить\n5. Выход\n");
		scanf("%hd%*c", &x);

		handle = dlopen("./libmycalc.so", RTLD_LAZY);
		if (!handle) 
		{
			fprintf(stderr, "%s\n", dlerror());
			exit(EXIT_FAILURE);
		}
		dlerror();
		error = dlerror();
		if (error != NULL) {
		   fprintf(stderr, "%s\n", error);
		   exit(EXIT_FAILURE);
		}

		switch(x)
		{
			case MATH_SUM:
			{
				
				powerfunc = dlsym(handle, "sum");
				printf("Первое слагаемое\n");
				scanf("%d%*c", &a);

				printf("Второе слагаемое\n");
				scanf("%d%*c", &b);
				printf("Сумма: %d\n", sum(a, b));

				break;
			}
			case MATH_DIFF:
				powerfunc = dlsym(handle, "diff");
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
				printf("Частное: %d\n", divn(a, b));
				break;
			case MATH_EXIT:
				return 0;
			default: 
				break;
		}

		dlclose(handle);
		exit(EXIT_SUCCESS);	
	}
	return 0;
}
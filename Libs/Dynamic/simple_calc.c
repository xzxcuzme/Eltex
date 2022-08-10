#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main()
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
	char *error;
	int a, b, (*sum_func)(int a, int b), (*diff_func)(int a, int b), 
	(*inc_func)(int a, int b), (*divn_func)(int a, int b);

	while (1) 
	{
		printf("1. Сложить\n2. Вычесть\n3. Умножить\n4. Разделить\n5. Выход\n");
		scanf("%hd%*c", &x);
		switch(x)
		{
			case MATH_SUM:
			{
				handle = dlopen("./libsum.so", RTLD_LAZY);
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

				sum_func = dlsym(handle, "sum");
				
				if (sum_func) {
					printf("Первое слагаемое\n");
					scanf("%d%*c", &a);

					printf("Второе слагаемое\n");
					scanf("%d%*c", &b);
					printf("Сумма: %d\n", (*sum_func)(a,b));
				} else {
				  printf("dlsym for f1 failed: %s\n", dlerror());
				}
				break;
			}
			case MATH_DIFF:
			{
				handle = dlopen("./libdiff.so", RTLD_LAZY);
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

				diff_func = dlsym(handle, "diff");

				if (diff_func) {
					printf("Первое слагаемое\n");
					scanf("%d%*c", &a);

					printf("Второе слагаемое\n");
					scanf("%d%*c", &b);
					printf("Разность: %d\n", (*diff_func)(a,b));
				} else {
				  printf("dlsym for f1 failed: %s\n", dlerror());
				}
				break;
			}
			case MATH_INC:
			{
				handle = dlopen("./libinc.so", RTLD_LAZY);
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

				inc_func = dlsym(handle, "inc");

				if (inc_func) {
					printf("Первое слагаемое\n");
					scanf("%d%*c", &a);
					
					printf("Второе слагаемое\n");
					scanf("%d%*c", &b);
					printf("Произведение: %d\n", (*inc_func)(a,b));
				} else {
				  printf("dlsym for f1 failed: %s\n", dlerror());
				}
				break;
			}
			case MATH_DIV:
			{
				handle = dlopen("./libdivn.so", RTLD_LAZY);
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

				divn_func = dlsym(handle, "divn");

				if (divn_func ) {
					printf("Первое слагаемое\n");
					scanf("%d%*c", &a);

					printf("Второе слагаемое\n");
					scanf("%d%*c", &b);
					printf("Частное: %d\n", (*divn_func)(a,b));
				} else {
				  printf("dlsym for f1 failed: %s\n", dlerror());
				}
				break;
			}
			case MATH_EXIT:
				return 0;
			default: 
				break;
		}

	}
	dlclose(handle);
	exit(EXIT_SUCCESS);	
	return 0;
}
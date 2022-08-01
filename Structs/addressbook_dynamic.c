#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define N 30

int main(void)
{

	struct data
	{
		char name[N];
		char surname[N];
		long phone; 
	};

	int n=3;
	struct data *mydata;

	mydata = malloc(sizeof(struct data)*n);

	if (mydata < 0 || mydata == NULL) {
		perror("Out of memory!\n");
		exit(EXIT_FAILURE);
	}

	strncpy(mydata[0].name, "igor", N);
	strncpy(mydata[0].surname, "prikh", N);
	mydata[0].phone = 12488;

	strncpy(mydata[1].name, "efim", N);
	strncpy(mydata[1].surname, "glaz", N);
	mydata[1].phone = 24772;

	strncpy(mydata[2].name, "igor", N);
	strncpy(mydata[2].surname, "korygin", N);
	mydata[2].phone = 20301;

	while (1)
		{
			short x;
			printf("1. Добавление абонента\n2. Поиск абонента\n3. Список абонентов\n4. Удалить абонента\n5. Выйти из программы\n");
			
			scanf("%hd", &x);
			switch (x)
			{
				case 1: //добавление
				{
					n++;
					mydata = realloc (mydata, (sizeof(struct data)*n));
					if (mydata < 0 || mydata == NULL) {
						perror("Out of memory!\n");
						exit(EXIT_FAILURE);
					}
			    	char addname[N];
			    	long addphone;
			        printf("name=");
					scanf("%s", mydata[n-1].name);
			        printf("surname=");
					scanf("%s", mydata[n-1].surname);
					printf("phone=");
					scanf("%ld", &mydata[n-1].phone);
					printf("Добавлена запись\nName: %s Surname %s Phone: %ld\n", 
					mydata[n-1].name, mydata[n-1].surname, mydata[n-1].phone);
				    break;
				}
				case 2: //поиск
					{
						char search[N];
						long searchphone;
						printf("Введите имя или фамилию\n");
						scanf("%s", search);
						printf("Введите телефон\n");
						scanf("%ld", &searchphone);

						for (int i = 0; i < n; ++i)
						{	
							if (strcmp(search, mydata[i].name) == 0 ||
								strcmp(search, mydata[i].surname) == 0 || 
								searchphone == mydata[i].phone)
							{
								printf("Name: %s Surname: %s Phone: %ld\n", 
								mydata[i].name, mydata[i].surname, mydata[i].phone);
							}
						}
						break;
					}

				case 3: //список
					for(int i=0;i<n; i++)
					{
						//if (mydata[i].phone != 0)
					    {
							printf("name=%s ", mydata[i].name);
							printf("surname=%s ", mydata[i].surname);
							printf("phone=%ld\n", mydata[i].phone);
						}
					}
					printf("\n");	 
					break;

				case 4: //удаление
					{
						char delname[N], delsurname[N];
						long delphone;

						printf("Введите имя \n");
						scanf("%s", delname);
						
						printf("Введите фамилию \n");
						scanf("%s", delsurname);
						
						printf("Введите телефон \n");
						scanf("%ld", &delphone);

						for (int i = 0; i < n; ++i)
						{
							if (strcmp(delname, mydata[i].name) == 0 &&
								strcmp(delsurname, mydata[i].surname) == 0 || 
								delphone == mydata[i].phone)
							{
								if (i<n-1)
								{
									printf("Name: %s Surname: %s Phone: %ld\n", 
									mydata[i].name, mydata[i].surname, mydata[i].phone);
									memcpy(mydata[i].name, mydata[i+1].name, N);
									strncpy(mydata[i+1].name, mydata[n-1].name, sizeof(delname));
									memcpy(mydata[i].surname, mydata[i+1].surname, N);
									strncpy(mydata[i+1].surname, mydata[n-1].surname, sizeof(delsurname));
									memcpy(&mydata[i].phone, &mydata[i+1].phone, sizeof(mydata[i].phone));
									mydata[i+1].phone=mydata[n-1].phone;
									printf("Удалено \n");
								} else {
									printf("Name: %s Surname: %s Phone: %ld\n", 
									mydata[i].name, mydata[i].surname, mydata[i].phone);
									printf("Удалено \n");
								}
								n--;
							}
						}
					}
					
					break;

				case 5: //выход
				{
					free(mydata);
					return 0;
				}

				default:
				{
					free(mydata);
					return 0;
				}
			}
		}

    free(mydata);
    return 0;
}
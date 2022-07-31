#include <stdio.h>
#include <string.h>

#define N 30
#define M 10

char searchinput[N], search[N], delname[N], delsurnamename[N], addname[N], addsurname[N];
int x, delphone, searchphone, addphone;

int main()
{
	struct data
	{
		char name[N];
		char surname[N];
		int phone; 
	};

	struct data mydata[M]={0};
	struct data *ptr=NULL;

	ptr = &mydata[M];

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
		printf("1. Добавление абонента\n2. Поиск абонента\n3. Список абонентов\n4. Удалить абонента\n");
		scanf("%d", &x);
		switch (x) 
		{
			case 1: // добавление
				for (int i = 0; i < M; ++i)
				{
					if (mydata[i].phone == 0) {

						printf("Введите имя \n");
						scanf("%s", addname);
						strncpy(mydata[i].name, addname, N);
						printf("Введите фамилию \n");
						scanf("%s", addsurname);
						strncpy(mydata[i].surname, addsurname, N);
						printf("Введите телефон \n");
						scanf("%d", &addphone);
						mydata[i].phone = addphone;
						printf("Добавлена запись\nName: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
						break;
					} 
				}
				break;
			case 2: // поиск
				printf("Введите имя или фамилию\n");
				scanf("%s", search);
				printf("Введите телефон\n");
				scanf("%d", &searchphone);
				
				for (int i = 0; i < M; ++i)
				{	
					if (strcmp(search, mydata[i].name) == 0 ||
						strcmp(search, mydata[i].surname) == 0 || 
						searchphone == mydata[i].phone)
					{
						printf("Name: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
						
					}
				}
				break;
			case 3: // список
				for (int i = 0; i < M; ++i)
				{
					if (mydata[i].phone != 0)
					{
						printf("Name: %s Surname: %s Phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
					}
				}
				break;
			case 4: // удаление
				printf("Введите имя \n");
				scanf("%s", delname);
				
				printf("Введите фамилию \n");
				scanf("%s", delsurnamename);
				
				printf("Введите телефон \n");
				scanf("%d", &delphone);

				for (int i = 0; i < M; ++i)
				{
					if (strcmp(delname, mydata[i].name) == 0 ||
						strcmp(delsurnamename, mydata[i].surname) == 0 || 
						delphone == mydata[i].phone)
					{
						printf("Name: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
						strncpy(mydata[i].name, "0", N);
						strncpy(mydata[i].surname, "0", N);
						mydata[i].phone=0;
						printf("Удалено \n");
						
					}
				}
		}
	}
}  
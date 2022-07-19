#include <stdio.h>
#include <string.h>

int x;
char searchinput[30];
char *search = "efim";

char *delname;// = "igor";
char *delsurnamename;// = "glaz";
int delphone = 12488;

int main()
{
	struct data
	{
		char *name;
		char *surname;
		int phone; 
	};

	struct data mydata[10]={};
	// struct data *ptr;

	// ptr = & mydata[10];

	// strcpy(mydata -> name, "igorr");
	// strcpy(mydata -> name, "irr");

	//&ptr -> name[0] = "igor"; // *ptr.name = "igor"

	printf("Size of data structure: %lu\n\n", sizeof(mydata));

	mydata[0].name = "igor";
	mydata[0].surname = "prikh";
	mydata[0].phone = 12488;

	mydata[1].name = "efim";
	mydata[1].surname = "glaz";
	mydata[1].phone = 2477;

	while (1)
	{
		printf("1. Добавление абонента\n2. Поиск абонента\n3. Список абонентов\n4. Удалить абонента\n");
		scanf("%d", &x);
		switch (x) {
			case 1: // добавление
				for (int i = 0; i < 10; ++i)
				{
					if (mydata[i].name == 0) {

						mydata[i].name = "ilya";
						mydata[i].surname = "tri";
						mydata[i].phone = 444111;
						printf("Добавлена запись\nName: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
						break;
					} 

					else

					{
						printf("Name: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
					} 
				}
			break;
			case 2: // поиск
				//printf("Введите имя\n");
				//scanf("%c", search);
				
				for (int i = 0; i < 10; ++i)
					{	
						printf("%s %d\n", search, i);
						printf("%s %d\n", mydata[i].name, i);
						if (search==mydata[i].name)
						{
							printf("Name: %s %s phone: %d\n", 
							mydata[i].name, mydata[i].surname, mydata[i].phone);
							break;
						}

						else {
							printf("не нашел %d \n", i);
						}
					}
				break;
			case 3: //список
				for (int i = 0; i < 10; ++i)
					{
						if (mydata[i].name != 0)
						{
							printf("Name: %s Surname: %s Phone: %d\n", 
							mydata[i].name, mydata[i].surname, mydata[i].phone);
						}
					}
				break;
			case 4: // удаление
				for (int i = 0; i < 10; ++i)

					if (mydata[i].name == delname || 
						mydata[i].surname == delsurnamename || 
						mydata[i].phone == delphone)
					{
						printf("Name: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
						mydata[i].name=0;
						mydata[i].surname=0;
						mydata[i].phone=0;
						printf("Удалено \n");
						break;
					} 
				break;
		}
	}

	

	// printf("%d\n", ptr -> name);

	// ptr -> b5 = 0; //(*ptr).b5

	// printf("%d\n", ptr -> b5);

}  
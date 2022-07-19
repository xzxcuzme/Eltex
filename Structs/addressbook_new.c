#include <stdio.h>
#include <string.h>

int x;
char search[30], searchinput[30];

char *delname;// = "igor";
char *delsurnamename;// = "glaz";
int delphone = 12488;

int main()
{
	struct data
	{
		char name[30];
		char surname[30];
		char phone[30]; 
	};

	struct data mydata[10]={};
	struct data *ptr=NULL;

	ptr = & mydata[10];
	// mydata[0].name;


	strncpy(mydata -> name, "igorr", 30);
	printf("name is %s\n%p\n", mydata[0].name, &ptr);
	ptr++;
	strncpy(ptr -> name, "efim", 30);
	printf("name is %s\n%p\n", mydata[1].name, &ptr);

	//strncpy(ptr[5] -> name, "mife", 30);
	//printf("name is %s\n", mydata[0].name);


	// strncpy(mydata[0].name, "igorr", 30);
	// strncpy(mydata[0].surname, "prikh", 30);
	// strncpy(mydata[0].phone, "12488", 30);

	strncpy(mydata[1].name, "efim", 30);
	strncpy(mydata[1].surname, "glaz", 30);

	// mydata[1].phone = 2477;

	// printf("name is %s\n", mydata[0].name);

	// strncpy(mydata[0].name, "igorr", 30);
	
	// strcpy(mydata -> name, "irr");

	// printf("Size of data structure: %lu\n\n", sizeof(mydata));




	// int x1;

	// while (1)
	// {
	// 	printf("1. Добавление абонента\n2. Поиск абонента\n3. Список абонентов\n4. Удалить абонента\n");
	// 	scanf("%d", &x);
	// 	switch (x) {
	// 		case 1: // добавление
	// 			for (int i = 0; i < 10; ++i)
	// 			{
	// 				if (mydata[i].name == 0) {

	// 					mydata[i].name = "ilya";
	// 					mydata[i].surname = "tri";
	// 					mydata[i].phone = 444111;
	// 					printf("Добавлена запись\nName: %s %s phone: %d\n", 
	// 					mydata[i].name, mydata[i].surname, mydata[i].phone);
	// 					break;
	// 				} 

	// 				else

	// 				{
	// 					printf("Name: %s %s phone: %d\n", 
	// 					mydata[i].name, mydata[i].surname, mydata[i].phone);
	// 				} 
	// 			}
	// 		break;
	// 		case 2: // поиск
	// 			for (int i = 0; i < 10; ++i)
	// 				{	
	// 					printf("Введите имя\n");
	// 					scanf("%s", search);
	// 					printf("%s\n", search);
	// 					strcpy (searchinput, mydata[i].name, 30);	
	// 					if (search==searchinput)
	// 					{
	// 						printf("Name: %s %s phone: %d\n", 
	// 						mydata[i].name, mydata[i].surname, mydata[i].phone);
	// 					}
	// 				}
	// 			break;
	// 		case 3: //список
	// 			for (int i = 0; i < 10; ++i)
	// 				{
	// 					if (mydata[i].name != 0)
	// 					{
	// 						printf("Name: %s Surname: %s Phone: %d\n", 
	// 						mydata[i].name, mydata[i].surname, mydata[i].phone);
	// 					}
	// 				}
	// 			break;
	// 		case 4: // удаление
	// 			for (int i = 0; i < 10; ++i)

	// 				if (mydata[i].name == delname || 
	// 					mydata[i].surname == delsurnamename || 
	// 					mydata[i].phone == delphone)
	// 				{
	// 					printf("Name: %s %s phone: %d\n", 
	// 					mydata[i].name, mydata[i].surname, mydata[i].phone);
	// 					mydata[i].name=0;
	// 					mydata[i].surname=0;
	// 					mydata[i].phone=0;
	// 					printf("Удалено \n");
	// 					break;
	// 				} 
	// 			break;
	// 	}
	// }

	

	// printf("%d\n", ptr -> name);

	// ptr -> b5 = 0; //(*ptr).b5

	// printf("%d\n", ptr -> b5);

}  
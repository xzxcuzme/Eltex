#include <stdio.h>

int x = 4;
char* search = "efim";

int main()
{
	struct data
	{
		char* name;
		char* surname;
		int phone; 
	};

	struct data mydata[10]={};

	
	printf("Size of data structure: %lu\n\n", sizeof(mydata));

	mydata[0].name = "igor";
	mydata[0].surname = "prikh";
	mydata[0].phone = 12488;

	mydata[1].name = "efim";
	mydata[1].surname = "glaz";
	mydata[1].phone = 2477;

	switch (x) {
		case 1:
			for (int i = 0; i < 10; ++i)
			{
				if (mydata[i].phone == 0)
					{
						mydata[i].name = "ilya";
						mydata[i].surname = "tri";
						mydata[i].phone = 444111;
						printf("Добавлена запись\nName: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
						break;
					} 
			}

			break;
		case 2:
			for (int i = 0; i < 10; ++i)
				{
					if (mydata[i].name==search)
					{
						printf("Name: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
					}
				}
			break;
		case 3:
			for (int i = 0; i < 10; ++i)
				{
					if (mydata[i].phone != 0)
					{
						printf("Name: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
					}
				}
			break;
		case 4:
			for (int i = 0; i < 10; ++i)
				{
					mydata[i].name=0;
					mydata[i].surname=0;
					mydata[i].phone=0;
					printf("Name: %s %s phone: %d\n", 
					mydata[i].name, mydata[i].surname, mydata[i].phone);	
				}
			break;

	}

	// printf("%d\n", ptr -> name);

	// ptr -> b5 = 0; //(*ptr).b5

	// printf("%d\n", ptr -> b5);

}  
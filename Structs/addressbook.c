#include <stdio.h>

char x = 2;
char* search = "efim";

int main()
{
	struct data
	{
		char* name;
		char* surname;
		int phone; 
	};

	struct data mydata[2]={0};

	
	printf("Size of data structure: %lu\n", sizeof(mydata));

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
				/* code */
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
					printf("Name: %s %s phone: %d\n", 
						mydata[i].name, mydata[i].surname, mydata[i].phone);
				}
			break;
	}

	// printf("%d\n", ptr -> name);

	// ptr -> b5 = 0; //(*ptr).b5

	// printf("%d\n", ptr -> b5);

}  
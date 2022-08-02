#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "AddressBookRecord.h"

// int get_test_addressbook(address_book**)
// {

// }

int main(void)
{
	int n=3;
	Address_book_t *address_book;

	address_book = calloc(n, sizeof(Address_book_t));

	if (address_book == NULL) {
		perror("Out of memory!\n");
		exit(EXIT_FAILURE);
	}

	strncpy(address_book[0].name, "igor", NAME_LEN);
	strncpy(address_book[0].surname, "prikh", SURNAME_LEN);
	address_book[0].phone = 12488;

	strncpy(address_book[1].name, "efim", NAME_LEN);
	strncpy(address_book[1].surname, "glaz", SURNAME_LEN);
	address_book[1].phone = 24772;

	strncpy(address_book[2].name, "igor", NAME_LEN);
	strncpy(address_book[2].surname, "korygin", SURNAME_LEN);
	address_book[2].phone = 20301;

	while (1)
		{
			short x;
			enum Action {
				ACTION_ADD=1,
				ACTION_SEARCH,
				ACTION_LIST,
				ACTION_DEL,
				ACTION_EXIT
			};
			menu();
			if (scanf("%hd%*c", &x)!=1)
			{
				do {
					printf("Ошибка ввода, попробуй еще раз\n");
					scanf("%*[^\n]");
					menu();
					scanf("%hd%*c", &x);
				}
				while (x==1);
			}
			//scanf("%hd%*c", &x);
			switch (x)
			{
				case ACTION_ADD:
				//action_add(&address_book[n], 3);
					{
						n++;
						char name[NAME_LEN], surname[SURNAME_LEN];
						long phone;
						address_book = realloc (address_book, (sizeof(Address_book_t)*n));
						if (address_book == NULL) {
							perror("Out of memory!\n");
							exit(EXIT_FAILURE);
						}
						printf("Введите имя:\n");
						fgets(name, sizeof(name), stdin);
						address_book_name_set(&address_book[n-1], name);
						printf("Введите фамилию:\n");
						fgets(surname, sizeof(surname), stdin);
						address_book_surname_set(&address_book[n-1], surname);
						printf("Введите телефон:\n");
						//scanf("%ld", &phone);
						address_book_phone_set(&address_book[n-1], phone);
						printf("Добавлена запись\n");
						address_book_get(&address_book[n-1]);
					    
					}
				break;
				
				case ACTION_SEARCH:
					{
						char search[NAME_LEN];
						long searchphone;
						printf("Введите имя или фамилию\n");
						scanf("%s", search);
						printf("Введите телефон\n");
						scanf("%ld", &searchphone);

						for (int i = 0; i < n; ++i)
						{	
							if (strncmp(search, address_book[i].name, sizeof(search)) == 0 ||
								strncmp(search, address_book[i].surname, sizeof(search)) == 0 || 
								searchphone == address_book[i].phone)
							{
								address_book_get(&address_book[i]);
							}
						}
						break;
					}

				case ACTION_LIST:
					for(int i=0;i<n; i++)
					{
					    {
					    	address_book_get(&address_book[i]);
						}
					}
					printf("\n");	 
					break;

				case ACTION_DEL:
					{
						char delname[NAME_LEN], delsurname[SURNAME_LEN];
						long delphone;

						printf("Введите имя \n");
						scanf("%s", delname);
						
						printf("Введите фамилию \n");
						scanf("%s", delsurname);
						
						printf("Введите телефон \n");
						scanf("%ld", &delphone);

						for (int i = 0; i < n; ++i)
						{
							if ((strncpy(delname, address_book[i].name, sizeof(delname)) == 0 &&
								strncpy(delsurname, address_book[i].surname, sizeof(delsurname)) == 0) || 
								delphone == address_book[i].phone)
							{
								if (i<n-1)
								{
									address_book_get(&address_book[i]);
									strncpy(address_book[i].name, address_book[i+1].name, sizeof(delname));
									strncpy(address_book[i+1].name, address_book[n-1].name, sizeof(delname));
									strncpy(address_book[i].surname, address_book[i+1].surname, sizeof(delsurname));
									strncpy(address_book[i+1].surname, address_book[n-1].surname, sizeof(delsurname));
									address_book[i].phone=address_book[i+1].phone;
									address_book[i+1].phone=address_book[n-1].phone;
									
								} else {
									address_book_get(&address_book[i]);
									
								}
								printf("Удалено \n");
								n--;
							}
						}
					}
					
					break;

				case ACTION_EXIT:
					{
						free(address_book);
						return 0;
					}

				default:
					{
						free(address_book);
						return 0;
					}
			}
		}
    free(address_book);
    return 0;
}


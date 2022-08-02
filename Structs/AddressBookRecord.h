#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 30
#define SURNAME_LEN 30

typedef struct Address_book_record
{
	char name[NAME_LEN];
	char surname[SURNAME_LEN];
	long phone; 
} Address_book_t;

int check(long *phone) {
	if (scanf("%ld%*c", phone)==1) return 0;
	else return -1;
}

int address_book_name_set (Address_book_t *address_book,
	char *name) 
{
	if (strlen(name)>=NAME_LEN) return -1;
	strncpy(address_book -> name, name, sizeof(&name));
	return 0;
}

int address_book_surname_set (Address_book_t *address_book,
	char *surname) 
{
	if (strlen(surname)>=SURNAME_LEN) return -1;
	strncpy(address_book -> surname, surname, sizeof(&surname));
	return 0;
}

int address_book_phone_set (Address_book_t *address_book, long phone) 
{
	if (check(&phone)) return -1;
	address_book -> phone=phone;
	return 0;
}

int address_book_get (Address_book_t *address_book) {
	printf("Name: %s Surname: %s Phone: %ld\n", address_book -> name, address_book -> surname, address_book -> phone);
	return 0;
}

int menu () {
	printf("1. Добавление абонента\n2. Поиск абонента\n3. Список абонентов\n4. Удалить абонента\n5. Выйти из программы\n");
	return 0;
}

int action_list(Address_book_t *address_book, 
	int n) {
	for(int i=0; i<n; i++)
	{
	    {
	    	address_book_get(&address_book[i]);
		}
	}
	printf("\n");
	return 0;
}

int action_add(Address_book_t *address_book, 
	int n)
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
	return 0;
}

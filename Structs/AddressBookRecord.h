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

int check(long *phone);

int address_book_name_set (Address_book_t *address_book,
	char *name);

int address_book_surname_set (Address_book_t *address_book,
	char *surname);

int address_book_phone_set (Address_book_t *address_book, long phone);

int address_book_get (Address_book_t *address_book);

int menu ();

int action_list(Address_book_t *address_book, 
	int n);

int clear_scanf();

int get_test_addressbook(Address_book_t *address_book);

int scan_int();
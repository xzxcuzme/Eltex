#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define PRICE 10000
#define NUM_SHOPS 5
#define SHOP_LOADER 500
#define BUYER 1000
#define COUNT_BUYER 3

typedef struct shop
{
	int stock;
	int number_of_shop;
	pthread_mutex_t mutex;
} Shop_t;

Shop_t my_shop[NUM_SHOPS];
Shop_t *new_shop = my_shop;

int get_shop_num(Shop_t *new_shop) {
	return new_shop->number_of_shop;
}

int get_stock(Shop_t *new_shop) {
	return new_shop->stock;
}

int get_shop_mutex_init(Shop_t *new_shop) {
	return pthread_mutex_init(&(new_shop->mutex), NULL);
}

void shop_init() {
	for (int i = 1; i <=NUM_SHOPS; ++i)
	{
		my_shop[i].number_of_shop = i;
		my_shop[i].stock = PRICE;
		pthread_mutex_init(&(my_shop[i].mutex), NULL);
		printf("Магазин %d заполнен товарами на %d и инициализирован mutex\n", 
			my_shop[i].number_of_shop, my_shop[i].stock);
	}
}

void *loader(void *arg) {
	
	int index = *(int*)arg;
	
	for (int i = 1; i < NUM_SHOPS+1; ++i)
	{
		pthread_mutex_lock(&(my_shop[i].mutex));
		new_shop[i].stock=new_shop[i].stock+500;
		printf("В магазин %d добавлено 500, стало: %d\n", 
			 my_shop[i].number_of_shop, my_shop[i].stock);
		sleep(2);
		pthread_mutex_unlock(&(my_shop[i].mutex));
	}

	return NULL;
}

void *buyer(void *arg) {
	
	int index = *(int*)arg;

	for (int i = 1; i < NUM_SHOPS+1; ++i)
	{
		pthread_mutex_lock(&(my_shop[i].mutex));
		new_shop[i].stock=new_shop[i].stock-1000;
		printf("Покупатель %d купил на 1000, в магазине %d стало: %d\n", 
			index, my_shop[i].number_of_shop, my_shop[i].stock);
		sleep(1);
		pthread_mutex_unlock(&(my_shop[i].mutex));
	}
	return NULL;
}

int main(void)
{
		
	size_t i;
	int index[5];

	shop_init();
	pthread_t lloader;
	pthread_t thread[3];
	while(my_shop[1].stock > SHOP_LOADER) {
		for (i = 0; i < 1; ++i)
		{
			index[i]=i + 1;
			pthread_create(&lloader, NULL, loader, (void *) &index[i]);
		}

		for (i = 0; i < 3; ++i)
		{
			index[i]=i + 1;
			pthread_create(&thread[i], NULL, buyer, (void *) &index[i]);
		}

		for (i = 0; i < 3; ++i)
		{
			pthread_join(thread[i], NULL);
		}
	}
	pthread_cancel(lloader);
	pthread_mutex_destroy(&(my_shop[i].mutex));
	return 0;
}
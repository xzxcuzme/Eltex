#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_SIZE 1024
#define MY_SHM "/my_shm"
#define SEM_NAME "/mysem"

int main()
{
	int shm_fd;
	char *vaddr;
	sem_t *sema_n;
	int val;
	char text[] = "Hi!";

	printf("Процесс 2 запустился\n");
	if ((shm_fd = shm_open(MY_SHM, O_CREAT | O_RDWR, 0666)) == -1)
	{
		perror("cannot open");
		exit(EXIT_FAILURE);
	}

	if (ftruncate(shm_fd, SHM_SIZE) != 0)
	{
		perror("cannot set size");
		exit(EXIT_FAILURE);
	}

	if ((vaddr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0)) == MAP_FAILED)
	{
		perror("cannot mmap");
		exit(EXIT_FAILURE);
	}

	if ((sema_n = sem_open(SEM_NAME, O_CREAT | O_RDWR, 0600, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	printf("Процесс 2 открыл sema_n\n");

	sem_post(sema_n);

		printf("Процесс 2 сделал первый пост\n");

	sem_wait(sema_n);
		// if (mlock(vaddr, SHM_SIZE) != 0)
		// {
		// 	perror("cannot mlock");
		// 	exit(EXIT_FAILURE);
		// }
		printf("Процесс 2 считал из памяти: %s\n", vaddr);

	sem_post(sema_n);

	sem_wait(sema_n);
		
		strncpy(vaddr, text, sizeof(text));
		printf("Процесс 2 записал в память: %s\n\n", vaddr);
		// if (munlock(vaddr, SHM_SIZE) != 0)
		// {
		// 	perror("cannot munlock");
		// 	exit(EXIT_FAILURE);
		// }
	sem_post(sema_n);

	munmap(vaddr, SHM_SIZE);
	sem_close(sema_n);
	close(shm_fd);

	sem_unlink(SEM_NAME);
	shm_unlink(MY_SHM);
	exit(EXIT_SUCCESS);
}
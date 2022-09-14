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
#define MY_SHM "my_shm"
#define SEM_NAME "/mysem"

int main()
{
	int shm_fd;
	char *vaddr;
	sem_t *sema_n;
	int val;
	int i = 0;


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

	if (mlock(vaddr, SHM_SIZE) != 0)
	{
		perror("cannot mlock");
		exit(EXIT_FAILURE);
	}

	if ((sema_n = sem_open(SEM_NAME, O_CREAT | O_RDWR, 0600, 3)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}

while(1) {
	if (sem_getvalue(sema_n, &val) > i)
	{
	i++;

	
	sem_trywait(sema_n);
	
	printf("semaphore value = %d\n", val);
	printf("shm:%d %s\n", val, vaddr);

	sem_post(sema_n);

	}
}

	munmap(vaddr, SHM_SIZE);
	sem_close(sema_n);
	sem_unlink(SEM_NAME);
	close(shm_fd);
	shm_unlink(MY_SHM);

	exit(EXIT_SUCCESS);
}
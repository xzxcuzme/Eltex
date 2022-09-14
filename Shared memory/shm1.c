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
	char text[] = "Hello!";

	pid_t pid = fork();
	if(pid == 0)
	{
		if(execl("./build/shm2","",NULL) == -1)
		{
			perror("exec");
			exit(EXIT_FAILURE);
		}
	}

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

	if ((sema_n = sem_open(SEM_NAME, O_CREAT | O_RDWR, 0600, 0)) == SEM_FAILED)
	{
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	sem_getvalue(sema_n, &val);
	printf("semaphore value = %d\n", val);

	sem_trywait(sema_n); //блокирует семафор
	strncpy(vaddr, text, sizeof(text));
	printf("Процесс 1 записал в память: %s\n\n", vaddr);
	sem_post(sema_n); //разблокирует семафор

	sleep(1);

	sem_getvalue(sema_n, &val);
	printf("semaphore value = %d\n", val);

	sem_trywait(sema_n); //блокирует семафор
	printf("Процесс 1 считал из памяти: %s\n\n", vaddr);
	sem_post(sema_n); //разблокирует семафор
	

	munmap(vaddr, SHM_SIZE); //отделяем сегмент общей памяти от адресного пространства
	sem_close(sema_n);
	close(shm_fd);

	sem_unlink(SEM_NAME);
	shm_unlink(MY_SHM);

	exit(EXIT_SUCCESS);
}
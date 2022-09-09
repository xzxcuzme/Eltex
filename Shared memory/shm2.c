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

#define SHM_SIZE 1024
#define MY_SHM "my_shm"

int main()
{
	int shm_fd;
	char *vaddr;

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

	printf("shm: %s\n", vaddr);

	if (mlock(vaddr, SHM_SIZE) != 0)
	{
		perror("cannot mlock");
		exit(EXIT_FAILURE);
	}

	munmap(vaddr, SHM_SIZE);
	close(shm_fd);
	shm_unlink(MY_SHM);
	
	exit(EXIT_SUCCESS);
}
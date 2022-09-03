#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h> 

#define QUEUE_NAME "/my_queue"
#define PRIORITY 1
#define SIZE 256

int main()
{
	mqd_t ds[2];
	char new_text[SIZE];
	struct mq_attr queue_attr;
	char text[] = "Hello, queue 1";

	ds[1] = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &queue_attr);
	ds[0] = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &queue_attr);

	if (ds[1] == -1 || ds[0] == -1)
	{
		perror("Creating queue error");
		exit(EXIT_FAILURE);
	}

	if (mq_receive(ds[1], new_text, SIZE, NULL) == -1)
	{
		perror("cannot receive");
		exit(EXIT_FAILURE);
	}

	printf("Message: %s\n", new_text);

	if (mq_send(ds[0], text, strlen(text), PRIORITY) == -1)
	{
		perror("Sending message error");
		exit(EXIT_FAILURE);
	}

	if (mq_close(ds[0]) == -1 || mq_close(ds[1]) == -1) perror("Closing queue error");

	exit(EXIT_SUCCESS);

}
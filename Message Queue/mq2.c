#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h> 

#define QUEUE_UP_STREAM "/my_queue_us"
#define QUEUE_DOWN_STREAM "/my_queue_ds"
#define PRIORITY 1
#define SIZE 256

int main()
{
	mqd_t ds[2];
	char new_text[SIZE];
	struct mq_attr queue_attr;
	char text[] = "Hello, US queue, im DS (mq2)";

	queue_attr.mq_maxmsg = 10; //max msg amount
	queue_attr.mq_msgsize = SIZE; //max size queue
	queue_attr.mq_flags = 0;
	queue_attr.mq_curmsgs = 0;

	ds[1] = mq_open(QUEUE_UP_STREAM, O_CREAT | O_RDONLY, &queue_attr);
	ds[0] = mq_open(QUEUE_DOWN_STREAM, O_CREAT | O_WRONLY, &queue_attr);

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

	printf("Message from US: %s\n", new_text);

	if (mq_send(ds[0], text, strlen(text)+1, PRIORITY) == -1)
	{
		perror("Sending message error");
		exit(EXIT_FAILURE);
	}

	if (mq_close(ds[0]) == -1 || mq_close(ds[1]) == -1) perror("Closing queue error");

	exit(EXIT_SUCCESS);

}
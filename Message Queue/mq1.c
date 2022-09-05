#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>  

#define QUEUE_UP_STREAM "/my_queue_us"
#define QUEUE_DOWN_STREAM "/my_queue_ds"
#define PRIORITY 1
#define SIZE 256

int main()
	{
	pid_t pid = fork();
	if(pid == 0)
	{
		if(execl("./mq2","",NULL) == -1)
		{
		perror("exec");
		exit(EXIT_FAILURE);
		}
	}
	else
	{
		mqd_t ds[2];
		char new_text[SIZE];
		char text[] = "Hi, DS queue, im US (mq1)";
		struct mq_attr queue_attr;

		queue_attr.mq_maxmsg = 10; //max msg amount
		queue_attr.mq_msgsize = SIZE; //max size queue
		queue_attr.mq_flags = 0;
		queue_attr.mq_curmsgs = 0;

		ds[0] = mq_open(QUEUE_UP_STREAM, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU, &queue_attr);
		

		if (ds[0] == -1)
		{
		    perror("Creating queue error");
	    	exit(EXIT_FAILURE);
		}

		if (mq_send(ds[0], text, strlen(text)+1, PRIORITY) == -1)
		{
			perror("Sending message error");
			exit(EXIT_FAILURE);
		}

		ds[1] = mq_open(QUEUE_DOWN_STREAM, O_RDONLY | O_CREAT | O_EXCL, S_IRWXU, &queue_attr);

		if (ds[1] == -1)
		{
		    perror("Creating queue error");
	    	exit(EXIT_FAILURE);
		}

		if (mq_receive(ds[1], new_text, SIZE, NULL) == -1)
		{
			perror("cannot receive");
			exit(EXIT_FAILURE);
		}

		printf("Message from DS: %s\n", new_text);

		if (mq_close(ds[0]) == -1 || mq_close(ds[1]) == -1) perror("Closing queue error");



		if (mq_unlink(QUEUE_UP_STREAM) == -1 || mq_unlink(QUEUE_DOWN_STREAM) == -1) perror("Removing queue error");



		exit(EXIT_SUCCESS);
	}
}
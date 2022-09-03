#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>  

#define QUEUE_NAME "/my_queue"
#define PRIORITY 1
#define SIZE 256

int main()
{
	pid_t pid = fork();
    if(pid == 0)
	{
        if(execl("./build/mq2","",NULL) == -1)
        {
            perror("exec");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
		mqd_t ds[2];
		char new_text[SIZE];
		char text[] = "Hi, queue 2";
		struct mq_attr queue_attr;

		queue_attr.mq_maxmsg = 10; //max msg amount
		queue_attr.mq_msgsize = SIZE; //max size queue
		queue_attr.mq_flags = 0;
		queue_attr.mq_curmsgs = 0;

		ds[0] = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &queue_attr);
		ds[1] = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR, &queue_attr);

		if (ds[0] == -1 || ds[1] == -1)
		{
		    perror("Creating queue error");
	    	exit(EXIT_FAILURE);
		}

		if (mq_send(ds[0], text, strlen(text), PRIORITY) == -1)
		{
			perror("Sending message error");
			exit(EXIT_FAILURE);
		}

		if (mq_receive(ds[1], new_text, SIZE, NULL) == -1)
		{
			perror("cannot receive");
			exit(EXIT_FAILURE);
		}

		printf("Message: %s\n", new_text);

		if (mq_close(ds[0]) == -1) perror("Closing queue error");

		if (mq_close(ds[1]) == -1) perror("Closing queue error");

		//if (mq_unlink(QUEUE_NAME) == -1) perror("Removing queue error");

		exit(EXIT_SUCCESS);
	}
}
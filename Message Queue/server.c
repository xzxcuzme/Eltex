#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>  

#define QUEUE_CLIENT_TO_SERVER "/queue_client_to_server"
#define QUEUE_SERVER_TO_CLIENT "/queue_server_to_client"
#define PRIORITY 1
#define SIZE 256

int main()
{
	mqd_t ds[2];
	char message[SIZE];
	struct mq_attr queue_attr;

	queue_attr.mq_maxmsg = 10; //max msg amount
	queue_attr.mq_msgsize = SIZE; //max size queue
	queue_attr.mq_flags = 0;
	queue_attr.mq_curmsgs = 0;

	ds[0] = mq_open(QUEUE_CLIENT_TO_SERVER, O_RDONLY | O_CREAT | O_EXCL, S_IRWXU, &queue_attr);

	if (ds[0] == -1)
	{
		if (errno!=EEXIST)
		{
		    perror("Creating queue error");
	    	exit(EXIT_FAILURE);
		} 
		else 
		{
			ds[0] = mq_open(QUEUE_CLIENT_TO_SERVER, O_RDONLY);
		}
	}
	while(1)
	{
		if (mq_receive(ds[0], message, SIZE, NULL) == -1)
		{
			perror("cannot receive");
			exit(EXIT_FAILURE);
		}

		printf("%s\n", message);
	}
	if (mq_close(ds[0]) == -1) perror("Closing queue error");
	

	exit(EXIT_SUCCESS);
}
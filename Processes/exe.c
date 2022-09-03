#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{

	printf("Try exe next command: <%s %s %s>\n", argv[1],argv[2],argv[3]);

	char *newargv[] = {0};
	char *newenviron[] = { NULL };

	if (argc != 4) {
	   fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
	   exit(EXIT_FAILURE);
	}

	newargv[0] = argv[1];
	newargv[1] = argv[2];
	newargv[2] = argv[3];

	execve(argv[1], newargv, newenviron);
	perror("execve");   /* execve() returns only on error */
	exit(EXIT_FAILURE);



   execve(argv[1], newargv, newenviron);
   perror("execve");   /* execve() returns only on error */
   exit(EXIT_FAILURE);
}

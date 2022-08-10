#include <stdio.h>
#include <string.h>

int main()
{
	char input[256];

	FILE *file;

	file = fopen("./newfile.txt", "r");

	if (file == NULL) printf ("error\n");

	if (file) fgets(input, sizeof(input), file);
	else printf("error\n");

	for (int i = strlen(input)-1; i >= 0; --i)
	{
		fseek(file, i, SEEK_SET);
		fgets(input, sizeof(char)+1, file);
		printf("%s", input);
	}

	printf("\n");

	if (fclose (file) == EOF) printf("error\n");

	return 0;
}
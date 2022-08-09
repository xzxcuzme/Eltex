#include <stdio.h>
#include <string.h>

int main()
{
	char input[256];
	FILE *file;

	file = fopen("./newfile.txt", "r");

	if (file) fgets(input, 256, file);
	else printf("error");

	fseek(file, strlen(input), SEEK_SET);
	printf("%ld\n", strlen(input));

	fgets(input, sizeof(input), file);
 
	printf("%s\n", input);
	
	return 0;
}
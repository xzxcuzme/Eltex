#include <stdio.h>

int main()
{
	char text[]="Hello_world";
	FILE *file;

	file = fopen("./newfile.txt", "w");
	
 	if (file) fputs(text, file);
 	else printf("error");

	return 0;
}
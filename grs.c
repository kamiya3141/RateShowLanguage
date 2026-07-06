#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAPE_SIZE 30000
#define MAX_BUFFER_SIZE (1024 * 2)
#define FILE_EXT ".rslng"

int check_extension(const char *filename)
{
	const char *ext = strrchr(filename, '.');
	if (!ext)
		return 0;
	return strcmp(ext, FILE_EXT) == 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <source_file" FILE_EXT ">\n", argv[0]);
		return 1;
	}

	if (!check_extension(argv[1]))
	{
		fprintf(stderr, "Error: Source file must have " FILE_EXT " extension.\n");
		return 1;
	}

	FILE *src = fopen(argv[1], "r");
	if (!src)
	{
		perror("Error opening source file");
		return 1;
	}

	unsigned char tape[TAPE_SIZE] = {0};
	unsigned char *ptr = tape;

	const char *keywords_array[] = {
		"きちーww",
		"ええてw",
		"うおw",
		"どわー笑",
		"ちょwお前必死やんww"
	};

	char buffer[MAX_BUFFER_SIZE];
	while (fgets(buffer, sizeof(buffer), src))
	{
		char *p = buffer;

		char *comment_pos = strstr(p, "//");
		if (comment_pos)
		{
			*comment_pos = '\0';
		}

		while (*p)
		{
			if (strncmp(p, keywords_array[0], strlen(keywords_array[0])) == 0)
			{
				++ptr;
				p += strlen(keywords_array[0]);
			}
			else if (strncmp(p, keywords_array[1], strlen(keywords_array[1])) == 0)
			{
				--ptr;
				p += strlen(keywords_array[1]);
			}
			else if (strncmp(p, keywords_array[2], strlen(keywords_array[2])) == 0)
			{
				++(*ptr);
				p += strlen(keywords_array[2]);
			}
			else if (strncmp(p, keywords_array[3], strlen(keywords_array[3])) == 0)
			{
				--(*ptr);
				p += strlen(keywords_array[3]);
			}
			else if (strncmp(p, keywords_array[4], strlen(keywords_array[4])) == 0)
			{
				putchar(*ptr);
				p += strlen(keywords_array[4]);
			}
			else
			{
				p++;
			}
		}
	}
	fclose(src);
	return 0;
}

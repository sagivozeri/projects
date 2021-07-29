#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char** argv)
{
	int fd = open("./text.txt", O_RDWR, S_IRUSR | S_IWUSR);
	struct stat sb;
	char *file_in_mem;
	int i;

	if (fstat(fd, &sb) == -1)
		perror("couldn't get file size\n");

	printf("file size is %ld\n", sb.st_size);

	file_in_mem = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	for (i = 0 ; i < sb.st_size ; i++) {
		if ((i % 2) == 0)
			file_in_mem[i] = toupper(file_in_mem[i]);

		printf("%c", file_in_mem[i]);
	}

	printf("\n");

	munmap(file_in_mem, sb.st_size);
	close(fd);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 128
#define DATA_SIZE (BUFF_SIZE - sizeof(void*) - sizeof(char))

void *simple_alloc()
{
	return malloc(BUFF_SIZE);
}

void *simple_free(void *buff)
{
	return free(buff);
}

struct str_buf_t {
	char data[DATA_SIZE];
	char size;
	struct str_buf_t *next;
};

void str_free(str_buf_t *str)
{
	struct str_buf_t *tmp;

	while (str) {
		tmp = str;
		str = str->next;
		simple_free(tmp);
	}

}

struct str_buf_t *str_alloc(int size)
{
	struct str_buf_t *str = NULL, *curr = NULL, *prev = NULL;
	int remaining_size = size;

	if (size <= 0)
		return NULL;

	while(remaining_size) {
		curr = simple_alloc();
		if (!curr) {
			str_free(str);
			return NULL;
		}

		curr->next = NULL;

		if (remaining_size > DATA_SIZE) {
			curr->size = DATA_SIZE;
			remaining_size -= DATA_SIZE;
		} else {
			curr->size = remaining_size;
			remaining_size = 0;
		}

		if (!prev)
			str = curr;
		else
			prev->next = curr;

		prev = curr;
	}

	return str;
}

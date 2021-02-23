#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10000
#define KEY_MAX_SIZE 1024

struct list {
	char key[KEY_MAX_SIZE];
	int val;
	struct list *next;
};

struct list * hash_table[HASH_SIZE] = {NULL};

int hash_func(const char *key)
{
	int i, sum = 0;
	
	for(i = 0; i < strlen(key); i++)
		sum += key[i] * i * i;

	return sum % HASH_SIZE;
}

int is_exist(struct list *head, const char *key)
{
	while (head) {
		if (!strcmp(head->key, key))
				return 1;

		head = head->next;
	}

	return 0;
}

void insert_elem(const char *key, int val)
{
	struct list *node;
	int idx = hash_func(key);
	
	if (is_exist(hash_table[idx], key)) return;

	node = (struct list*)malloc(sizeof(struct list));
	strcpy(node->key, key);
	node->val = val;
	node->next = hash_table[idx];

	hash_table[idx] = node;
}

void free_hash()
{
	struct list *head, *tmp;
	int i;

	for (i = 0; i < HASH_SIZE; i++) {
		if (!hash_table[i])
			continue;

		head = hash_table[i];
		while (head) {
			tmp = head;
			head = head->next;
			free(tmp);
		}
	}
}

void print_hash()
{
	struct list *head;
	int i;

	printf("\nHash Table\n");

	for (i = 0; i < HASH_SIZE; i++) {
		if (!hash_table[i])
			continue;

		printf("IDX %d:\n", i);
		head = hash_table[i];
		while (head) {
			printf("Word: %s Occurances: %d\n", head->key, head->val);
			head = head->next;
		}
		printf("\n");
	}
}

int find_num_occurances(FILE *f, const char *word)
{
	char tmp[KEY_MAX_SIZE];
	int num = 0;

	while (fscanf(f, "%s", tmp) == 1) {
		if (!strcmp(tmp, word))
			num++;
	}

	return num;
}

int get_val(const char *key)
{
	int idx = hash_func(key);
	struct list *head;

	head = hash_table[idx];
	while (head) {
		if (!strcmp(head->key, key))
			return head->val;

		head = head->next;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	char *filename;
	FILE *fp;
	char word[KEY_MAX_SIZE];
	int num;
	long int pos;

	if (argc != 2) {
		printf("Num of args should be 1 (filename)\n");
		return -1;
	}
		
	filename = argv[1];
	printf("Openning file %s\n", filename);
	fp = fopen(filename, "r");

	if (!fp) {
		printf("No such file %s\n", filename);
		return -1;
	}

	while (fscanf(fp, "%s", word) == 1) {
		if (get_val(word))
			continue;

		pos = ftell(fp);
		num = find_num_occurances(fp, word);
		fseek(fp, pos, SEEK_SET);
		insert_elem(word, num+1);
	}

	print_hash();

	printf("\n\n");
	while (1) {
		printf("Enter a word to search:\n");
		scanf("%s", word);
		if (!strcmp(word, "NULL"))
			break;

		num = get_val(word);
		printf("%s is shown %d times in file\n", word, num);

	}
	
	free_hash();
	fclose(fp);

	return 0;
}

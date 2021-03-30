#include <stdio.h>
#include <stdlib.h>

struct entry {
	int num;
	int idx;

	struct entry *next;
};

struct entry **hash_table;
int table_size;

static inline int hash(int num)
{
	return  abs(num % table_size);
}

static inline int hash_alloc()
{
	int i;

	hash_table = (struct entry**)malloc(sizeof(struct entry *) * table_size);
	if (!hash_table) {
		printf("Allocation failed\n");
		return 1;
	}

	for (i = 0; i < table_size; i++)
		hash_table[i] = NULL;

	return 0;
}

static inline void hash_display()
{
	struct entry *tmp;
	int i;

	for (i = 0; i < table_size; i++) {
		tmp = hash_table[i];

		while(tmp) {
			printf("%d: num %d idx %d\n", i, tmp->num, tmp->idx);

			tmp = tmp->next;
		}
	}
}

static inline void hash_set(int key, struct entry *e)
{
	struct entry **tmp = &hash_table[key];

	while(*tmp)
		tmp = &((*tmp)->next);

	*tmp = e;
}

static inline int hash_get(int key, int val)
{
	struct entry *tmp = hash_table[key];

	while(tmp) {
		if (tmp->num == val)
			return tmp->idx;

		tmp = tmp->next;
	}

	return -1;
}

static inline void hash_free()
{
	struct entry *tmp1, *tmp2;
	int i;

	for (i = 0; i < table_size; i++) {
		tmp1 = hash_table[i];

		while(tmp1) {
			tmp2 = tmp1;
			tmp1 = tmp1->next;
			free(tmp2);
		}
	}

	free(hash_table);
}

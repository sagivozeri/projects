#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct entry {
	char name[10];
	int age;
	int height;
	int weight;

	struct entry *next;
};

struct entry **hash_table;
int table_size;

int hash(char *name)
{
	int len = strlen(name);
	int i;
	int key = 0;
	
	for (i = 0; i < len; i++)
		key += name[i];
	
	key = key % table_size;
	
	return key;
}

void hash_set(int key, struct entry *e)
{
	struct entry **tmp = &hash_table[key];
	
	while(*tmp)
		tmp = &((*tmp)->next);
		
	*tmp = e;
}

int add_student()
{
	struct entry *student;
	char name[10];
	int age;
	int height;
	int weight;
	int key;
	time_t t;
	
	srand((unsigned)time(&t));
	
	student = (struct entry*)malloc(sizeof(struct entry));
	if (!student) {
		printf("Allocation failed\n");
		return 1;
	}
	
	printf("Enter name: ");
	scanf("%s", name);
	if(strlen(name) > 9) {
		printf("Name is too long\n");
		free(student);
		return 1;
	}
	
	strcpy(student->name, name);
	student->age = 20 + rand() % 20;
	student->height = 160 + rand() % 40;
	student->weight = 60 + rand() % 30;
	student->next = NULL;
	
	key = hash(name);
	hash_set(key, student);
	
	return 0;
}

int hash_alloc()
{
	int i;
	
	hash_table = (struct entry**)malloc(sizeof(struct entry*) * table_size);
	if (!hash_table) {
		printf("Allocation failed\n");
		return 1;
	}
	
	for (i = 0; i < table_size; i++)
		hash_table[i] = NULL;

	return 0;
}

void hash_display()
{
	struct entry *tmp;
	int i;
	
	for (i = 0; i < table_size; i++) {
		tmp = hash_table[i];
		
		while(tmp) {
			printf("%d: name %s age %d height %d weight %d\n", i, tmp->name, tmp->age, tmp->height, tmp->weight);
			
			tmp = tmp->next;
		}
	}
}

int hash_get(char *name)
{
	int key = hash(name);
	struct entry *tmp = hash_table[key];;
	
	while(tmp) {
		if (!strcmp(tmp->name, name)) {
			printf("name %s age %d height %d weight %d\n", tmp->name, tmp->age, tmp->height, tmp->weight);
			return 0;
		}

		tmp = tmp->next;	
	}

	return 1;
}

void resc_free()
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

int main()
{
	int size, i;
	char student_str[10];
	int iter = 0;
	
	printf("How many students? ");
	scanf("%d", &size);
	
	table_size = size * 2;

	if (hash_alloc())
		return 1;
	
	for (i = 0; i < size; i++) {
		if (add_student())
			goto err;
	}
	
	hash_display();
	
	while (iter < 10) {
		printf("Which student do you want to find? ");
		scanf("%s", student_str);
	
		if (!hash_get(student_str))
			break;
		
		printf("Student wasn't found.\n");
		iter++;
	}

err:
	resc_free();

	return 0;
}

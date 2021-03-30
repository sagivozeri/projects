#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int id;
	int visited;
	struct node *next;
} Node;

typedef struct output_node {
	int id;
	struct output_node *prev;
	struct output_node *next;

} OutNode;

Node** node_arr;
OutNode *output_head = NULL;
OutNode *output_ptr = NULL;
int num_nodes;
int total_visit_count;

void calc_total_visit_count()
{
	Node *curr;

	for (int i; i < num_nodes; i++) {
		curr = node_arr[i];

		while (curr) {
			total_visit_count++;
			curr = curr->next;
		}
	}

	printf("Total visit count = %d\n", total_visit_count);
}

void add_node_to_graph(int id, int neigh_id)
{
	Node *head = node_arr[id];
	Node *new_neigh = (Node*)malloc(sizeof(Node));
	
	if (!new_neigh) {
		printf("Allocation failed\n");
		return;
	}

	new_neigh->id = neigh_id;
	new_neigh->visited = 0;
	new_neigh->next = NULL;

	if (!head) {
		node_arr[id] = new_neigh;
		return;
	}

	while (head->next)
		head = head->next;

	head->next = new_neigh;
}

void init_graph()
{
	printf("Enter number of  nodes: ");
	scanf("%d", &num_nodes);

	node_arr = (Node**)malloc(sizeof(Node*) * num_nodes);
	if (!node_arr) {
		printf("Allocation failed\n");
		return;
	}

	for (int node_id = 0; node_id < num_nodes; node_id++) {
		int neigh_id;

		printf("Enter neighbors of node %d:\n", node_id);
		while (1) {
			scanf("%d", &neigh_id);
			if (neigh_id < 0 || neigh_id >= num_nodes)
				break;

			add_node_to_graph(node_id, neigh_id);
		}
	}

	calc_total_visit_count();
}

void print_path()
{
	OutNode *tmp = output_head;

	while (tmp) {
		printf("%d -> ", tmp->id);
		tmp = tmp->next;
	}

	printf("\n");
}

void add_new_output_node(int id)
{
	OutNode *new, *tmp;
	
	new = (OutNode*)malloc(sizeof(*new));
	if (!new) {
		printf("Allocation failed\n");
		return;
	}

	printf("Adding new id %d to output list\n", id);

	new->id = id;

	if (!output_head) {
		new->prev = NULL;
		new->next = NULL;
		output_head = new;
		output_ptr = new;
		print_path();
		return;
	}	

	new->next = output_ptr->next;
	if (output_ptr->next)
		output_ptr->next->prev = new;
	output_ptr->next = new;
	new->prev = output_ptr;

	output_ptr = new;

	print_path();
}

int has_free_neigh(int id, int *neigh_id)
{
	Node *curr = node_arr[id];

	while (curr) {
		if (curr->visited == 0) {
			*neigh_id = curr->id;
			return 1;
		}

		curr = curr->next;
	}

	return 0;
}

void mark_neigh_as_visited(int id, int neigh_id)
{
	Node *tmp = node_arr[id];

	while (tmp) {
		if (tmp->id == neigh_id) {
			if (tmp->visited == 1) {
				printf("Error!!! neigh_id %d of id %d is already marked as visited\n", neigh_id, id);
				return;
			}
			tmp->visited = 1;
		}

		tmp = tmp->next;
	}
}

void find_path()
{
	int curr_id = 0, visit_count = 0, neigh_id;

	add_new_output_node(curr_id);
	
	while (visit_count < total_visit_count) {
		if (has_free_neigh(curr_id, &neigh_id)) {
			mark_neigh_as_visited(curr_id, neigh_id);
			mark_neigh_as_visited(neigh_id, curr_id);
			visit_count += 2;
			curr_id = neigh_id;
			add_new_output_node(curr_id);
		} else {
			output_ptr = output_ptr->prev;
			curr_id = output_ptr->id;
		}
	}
}

void free_arr()
{
	Node *tmp, *curr;

	for (int i = 0; i < num_nodes; i++) {
		curr = node_arr[i];
		while(curr) {
			tmp = curr;
			curr = curr->next;
			free(tmp);
		}
	}

	free(node_arr);
}

void free_output()
{
	OutNode *tmp;

	while(output_head) {
		tmp = output_head;
		output_head = output_head->next;
		free(tmp);
	}
}

int main()
{
	init_graph();
	find_path();

	printf("Final Path:\n");
	print_path();
	free_arr();
	free_output();

	return 0;
}

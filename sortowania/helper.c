#ifndef HELPER
#define HELPER

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N_HELPER 15
#define N_MODULO (3*N_HELPER)

typedef struct s_node {
	int val;
	struct s_node *next;
} node;

typedef struct s_nnode {
	node * val;
	struct s_nnode *next;
} nnode;

typedef struct s_queue {
	nnode *head;
	nnode *tail;
	int size;
} queue;

int * data_create(void)
{
	int *result = (int *) malloc(N_HELPER*sizeof(int));
	int i=0;
	srand(time(NULL));
	for(;i<N_HELPER; i++)
		result[i] = rand() % N_MODULO;
	return result;
}

int data_length(void)
{
	return N_HELPER;
}

int data_modulo(void)
{
	return N_MODULO;
}

void data_print(int * arr, int n)
{
	int i=0;
	for(;i<n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void data_destroy(int *arr)
{
	free(arr);
}

node * list_create(void)
{
	node *result = NULL;
	int i=0;
	srand(time(NULL));
	for(;i<N_HELPER;i++)
	{
		node *tmp = (node *) malloc(sizeof(node));
		tmp->next = result;
		tmp->val = rand() % (3*N_HELPER);
		result = tmp;
	}
	return result;
}

void list_print(node *list)
{
	while(list != NULL)
	{
		printf("%d ", list->val);
		list = list->next;
	}
	printf("\n");
}

node * list_tail(node *list)
{
	while(list->next) list = list->next;
	return list;
}

void list_destroy(node *list)
{
	node * tmp;
	while(list != NULL)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

node * stack_init()
{
	node *tmp = (node *) malloc(sizeof(node));
	tmp->next = NULL;
	tmp->val = 0;
	return tmp;
}

int stack_empty(node * stack)
{
	return !stack->val;
}

void stack_push(node * stack, int val)
{
	node *tmp = (node *) malloc(sizeof(node));
	tmp->val = val;
	tmp->next = stack->next;
	stack->next = tmp;
	stack->val++;
}

int stack_pop(node * stack)
{
	node *tmp = stack->next;
	int r = tmp->val;
	stack->next = stack->next->next;
	stack->val--;
	free(tmp);
	return r;
}

queue * queue_init()
{
	queue *tmp = (queue *) malloc(sizeof(queue));
	tmp->head = NULL;
	tmp->tail = NULL;
	tmp->size = 0;
	return tmp;
}

node * queue_get(queue *q)
{
	node *tmp;
	nnode *tmp2;
	if(q->size == 1)
	{
		tmp = q->head->val;
		free(q->head);
		q->head = NULL;
		q->tail = NULL;
		q->size = 0;
	}
	else
	{
		tmp = q->head->val;
		tmp2 = q->head;
		q->head = q->head->next;
		free(tmp2);
		q->size--;
	}
	return tmp;
}

void queue_put(queue *q, node *val)
{
	nnode *tmp = (nnode *) malloc(sizeof(nnode));
	tmp->val = val;
	tmp->next = NULL;
	if(q->size == 0)
	{
		q->head = tmp;
		q->tail = tmp;
		q->size++;
	}
	else
	{
		q->tail->next = tmp;
		q->tail = tmp;
		q->size++;
	}
}

void queue_destroy(queue *q)
{
	while(q->size) queue_get(q);
	free(q);
}
#endif
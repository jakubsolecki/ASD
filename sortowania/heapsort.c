#include <stdio.h>
#include "helper.c"
#define PARENT(x) x/2
#define LEFT(x) 2*x
#define RIGHT(x) 2*x+1

struct heap
{
	int *data;
	int data_length;
	int size;
};

void heapify(struct heap *a, int i);
void build_heap(struct heap *a); 
void heapsort(struct heap *a);

int main()
{
	// tworzenie kopca
	struct heap a;
	a.data = data_create();
	a.data_length = data_length();
	
	// prezentowanie nieposortowanych danych
	data_print(a.data, a.data_length);
	
	// sortowanie
	heapsort(&a);
	
	// prezentowanie posortowanych danych
	data_print(a.data, a.data_length);
	
	// niszczenie tablicy
	data_destroy(a.data);
	
	return 0;
}

void heapify(struct heap *a, int i)
{
	int max_ind = i;
	if(LEFT(i) < a->size && a->data[LEFT(i)] > a->data[max_ind])
		max_ind = LEFT(i);
	if(RIGHT(i) < a->size && a->data[RIGHT(i)] > a->data[max_ind])
		max_ind = RIGHT(i);
	if(max_ind != i)
	{
		swap(&a->data[max_ind], &a->data[i]);
		heapify(a, max_ind);
	}
}

void build_heap(struct heap *a) 
{
	a->size = a->data_length;
	int i=PARENT(a->size-1);
	for(; i >= 0; i--)
		heapify(a, i);
}

void heapsort(struct heap *a) 
{
	build_heap(a);
	int i=a->size-1;
	for(; i>0; i--)
	{
		swap(&a->data[0], &a->data[i]);
		a->size--;
		heapify(a, 0);
	}
}
#include "helper.c"

void quicksort(int * arr, int l, int r);
int partition(int * arr, int l, int r);

int main()
{
	int *arr = data_create();
	data_print(arr, data_length());
	quicksort(arr, 0, data_length() -1);
	data_print(arr, data_length());
	data_destroy(arr);
	return 0;
}

void quicksort(int * arr, int l, int r)
{
	node *stack = stack_init();
	stack_push(stack, l);
	stack_push(stack, r);
	
	int i, j, q;
	while(!stack_empty(stack))
	{
		j = stack_pop(stack);
		i = stack_pop(stack);
		q = partition_lomuto(arr, i, j);
		if(i<q-1)
		{
			stack_push(stack, i);
			stack_push(stack, q-1);
		}
		if(q+1<j)
		{
			stack_push(stack, q+1);
			stack_push(stack, j);
		}
	}
}

int partition_lomuto(int * arr, int l, int r)
{
	int pivot = arr[r];
	int i=l,j=l;
	for(; i<r; i++)
		if(arr[i]<=pivot)
			swap(&arr[j++], &arr[i]);
	swap(&arr[j], &arr[r]);
		
	return j;
}
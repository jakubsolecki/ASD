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
	while(l < r)
	{
		int q = partition_lomuto(arr, l, r);
		quicksort(arr, l, q-1);
		l = q+1;
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
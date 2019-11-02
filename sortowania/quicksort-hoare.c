#include "helper.c"

void quicksort(int * arr, int l, int r);
int partition_hoare(int *arr, int l, int r);

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
	if(l<r)
	{
		int q = partition_hoare(arr, l, r);
		quicksort(arr, l, q);
		quicksort(arr, q+1,r);
	}
}

int partition_hoare(int *arr, int l, int r)
{
	int pivot = arr[l];
	int i = l-1;
	int j = r+1;
	while(1)
	{
		do j--; while(arr[j] > pivot);
		do i++; while(arr[i] < pivot);
		if(i<j)
			swap(&arr[i], &arr[j]);
		else
			return j;
	}
}
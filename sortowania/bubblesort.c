#include "helper.c"

void sort(int * arr, int n);

int main()
{
	int *arr = data_create();
	data_print(arr, data_length());
	sort(arr, data_length());
	data_print(arr, data_length());
	data_destroy(arr);
	return 0;
}

void sort(int * arr, int n)
{
	int i, j;
	for(i=1;i<n; i++)
		for(j=n; j>=i; j--)
			if(arr[j-1] > arr[j])
				swap(&arr[j], &arr[j-1]);
}
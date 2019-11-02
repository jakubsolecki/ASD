#include "helper.c"

void sort(int *arr, int n);

int main()
{
	int *arr = data_create();
	data_print(arr, data_length());
	sort(arr, data_length());
	data_print(arr, data_length());
	data_destroy(arr);
	return 0;
}

void sort(int *arr, int n)
{
	int i=0, j, min;
	for(; i<n-1; i++)
	{
		min=i;
		for(j=i+1; j<n; j++)
			if(arr[j] < arr[min]) min = j;
		swap(&arr[i], &arr[min]);
	}
}


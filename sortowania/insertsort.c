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
	int tmp, i=1, j;
	for(; i<n; i++)
	{
		tmp = arr[i];
		j = i-1;
		while(j >= 0 && tmp < arr[j])
		{
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = tmp;
	}
}
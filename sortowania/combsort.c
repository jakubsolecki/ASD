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
	int gap = n;
	int top;
	int i, j;
	int swapped;
	do
	{
		swapped = 0;
		gap /= 1.3;
		if(gap < 1) gap = 1;
		top = n -gap;
		for(i=0; i<top; i++)		
		{
			j = i+gap;
			if(arr[i] > arr[j])
			{
				swap(&arr[j], &arr[i]);
				swapped = 1;
			}
		}
	}
	while(gap>1 || swapped);
}
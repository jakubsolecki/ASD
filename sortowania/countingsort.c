#include "helper.c"

void sort(int *arr, int n, int k);

int main()
{
	int *arr = data_create();
	data_print(arr, data_length());
	sort(arr, data_length(), data_modulo());
	data_print(arr, data_length());
	data_destroy(arr);	
	return 0;
}

void sort(int *arr, int n, int k)
{
	int * b = (int *) malloc(n*sizeof(int));
	int * c = (int *) malloc(k*sizeof(int));
	int i;
	
	for(i=0; i<k; i++) c[i] = 0;
	for(i=0; i<n; i++) c[arr[i]]++;
	for(i=1; i<k; i++) c[i] += c[i-1];
	for(i=n-1; i>=0; i--) b[--c[arr[i]]] = arr[i];
	for(i=0; i<n; i++) arr[i] = b[i];
	
	free(b);
	free(c);
}
#include "helper.c"

void sort(int *arr, int size);
void merge(int *arr, int a, int s, int b);
int min(int a, int b)
{
	return (a < b ? a : b);
}

int main()
{
	int *arr = data_create();
	data_print(arr, data_length());
	sort(arr, data_length());
	data_print(arr, data_length());
	data_destroy(arr);	
	return 0;
}

void sort(int *arr, int size)
{
	int i;
	int len = 1;
	while (len <=size)
	{
		len *= 2;
		for (i = 0; i < size; i += len)
		{
			if (i + len > size)
			{
				if (i + len/2 <= size)
					merge(arr,i,i+(len/2)-1,size-1);
			}
			else
				merge(arr,i,i+(len/2)-1,i+len-1);
		}
	}
}
void merge(int *arr, int a, int s, int b)
{
	int l_size=s-a+1;
	int r_size=b-s;
	int *l = (int *) malloc(l_size*sizeof(int));
	int *r = (int *) malloc(r_size*sizeof(int));
	
	int i,j,k;
	for(i=0;i<l_size;i++) l[i] = arr[a+i];
	for(i=0;i<r_size;i++) r[i] = arr[s+1+i];
	
	i=0, j=0, k=a;
	while(i<l_size && j<r_size)
		if(l[i] < r[j]) 
			arr[k++] = l[i++];
		else
			arr[k++] = r[j++];

	while(i<l_size) arr[k++] = l[i++];
	while(j<r_size) arr[k++] = r[j++];
	
	free(l);
	free(r);
}
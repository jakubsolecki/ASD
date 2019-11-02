#include "helper.c"

node * sort(node *head);
node * select(node **head);

int main()
{
	node *list = list_create();
	list_print(list);
	list = sort(list);
	list_print(list);
	list_destroy(list);
	return 0;
}

node * sort(node *head)
{
	node *result=NULL; // wskaznik na posortowana liste
	node *tmp; // wskaznik roboczy
	
	while(head)
	{
		tmp = select(&head);
		tmp->next = result;
		result = tmp;
	}
	
	return result;
}

node * select(node **head)
{
	node *sentinel = (node *) malloc(sizeof(node)); // tworzenie i przypinanie wartownika
	sentinel->next = *head;
	node *tmp = *head; // wskaznik roboczy
	node *prev_max = sentinel; // wskaznik na element poprzedzajacy element maksymalny
	
	while(tmp->next) // szukanie maksimum
	{
		if(tmp->next->val > prev_max->next->val) prev_max = tmp;
		tmp = tmp->next;
	}
	
	node *max = prev_max->next; // wypinanie elementu maksymalnego
	prev_max->next = prev_max->next->next;
	max->next = NULL;
	
	*head = sentinel->next;
	free(sentinel); // usuwanie wartownika
	
	return max;
}
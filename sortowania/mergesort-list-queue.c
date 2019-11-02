#include "helper.c"

node * sort(node *head, node *tail);
node * seek(node **head);
node * merge(node *list1, node *list2);
void repin(node **from, node **to);


int main()
{
	node *list = list_create();
	list_print(list);
	list = sort(list, list_tail(list));
	list_print(list);
	list_destroy(list);
	return 0;
}

node * sort(node *head, node *tail) // sortujemy wykorzystujac serie naturalne
{
	queue *q = queue_init(); // tworzenie kolejki
	
	node *tmp; // wskaznik roboczy;
	while(tmp = seek(&head)) queue_put(q, tmp); // dodawanie serii naturalnych do kolejki
	while(q->size > 1) queue_put(q, merge(queue_get(q), queue_get(q))); // sortowanie
	
	tmp = queue_get(q); // zwracanie wyniku i niszczenie kolejki
	queue_destroy(q);
	return tmp;
}

node * seek(node **head)
{
	if(*head == NULL) return NULL; // jezeli lista jest pusta to zwracamy NULL
	
	node *result = *head; // zwracany ciag zaczyna sie na poczatku listy
	node *tmp; 
	while((*head)->next != NULL && (*head)->val <= (*head)->next->val) *head = (*head)->next; // szukamy osatniego elementu w ciagu niemalejacym
	tmp = *head; 
	*head = (*head)->next; // przepinanie na ostatni element
	tmp->next = NULL;
	
	return result;
}

node * merge(node *list1, node *list2)
{	
	node *result = (node *) malloc(sizeof(node)); // tworzenie wartownika
	result->next = NULL;
	node *result_tail = result; // wskaznik na ostatni element posortowanej listy

	while(list1 != NULL && list2 != NULL)
	{
		// wybieranie elementu do wpiecia w liste wynikowa
		if(list1->val <= list2->val) repin(&list1, &result_tail);
		else repin(&list2, &result_tail);
	}
	
	while(list1 != NULL) repin(&list1, &result_tail);
	while(list2 != NULL) repin(&list2, &result_tail);
	node *tmp = result->next;
	free(result); // usuwanie wartownika
	return tmp;
}

void repin(node **from, node **to)
{
	node *tmp = *from;
	*from = (*from)->next;
	(*to)->next = tmp;
	tmp->next = NULL;
	*to = tmp;	
}
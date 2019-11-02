#include "helper.c"

node * sort(node *head);
node * seek(node **head);
void merge(node *list1, node *list2, node **head, node **tail);
void repin(node **from, node **to);


int main()
{
	node *list = list_create();
	list_print(list);
	list = sort(list);
	list_print(list);
	list_destroy(list);
	return 0;
}

node * sort(node *head) // sortujemy wykorzystujac serie naturalne
{
	if(head == NULL) return NULL; // jezeli lista jest pusta to nic nie robimy
	
	// szukamy ogona listy
	node *tail;
	for(tail = head; tail->next != NULL; tail = tail->next);

	node *list1, *list2; // dwie listy do scalenia
	node *merged_head, *merged_tail; // wskaznik na posortowana liste
	
	while(1)
	{
		list1 = seek(&head); // szukanie dwoch posortowanych podlist
		list2 = seek(&head);
		if(list2 == NULL) return list1; // jezeli druga jest pusta, to zwracamy pierwsza - jest cala i posortowana
		merge(list1, list2, &merged_head, &merged_tail); // laczenie dwoch podlist
		if(head == NULL) return merged_head; // jezeli laczylismy tylko dwie listy to konczymy
		tail->next = merged_head;
		tail = merged_tail;
	}
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

void merge(node *list1, node *list2, node **head, node **tail)
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
		
	*head = result->next;
	*tail = result_tail;
	free(result); // usuwanie wartownika
}

void repin(node **from, node **to)
{
	node *tmp = *from;
	*from = (*from)->next;
	(*to)->next = tmp;
	tmp->next = NULL;
	*to = tmp;	
}
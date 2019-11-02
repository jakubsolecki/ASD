#include "helper.c"

node * sort(node *head);
void quicksort(node *head, node *tail);
node * partition_lomuto(node *head, node *tail);

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
	node *tail, *tmp;
	for(tmp=head; tmp!=NULL; tmp=tmp->next) tail = tmp; // szukanie ogona
	
	// tworzenie wartownika na poczatku listy
	tmp = (node *) malloc(sizeof(node));
	tmp->next = head;
	head = tmp;
	
	// sortowanie
	quicksort(head, tail);
	
	// usuwanie wartownika
	head = tmp->next;
	free(tmp);
	
	// zwracanie posortowanej listy
	return head;
}

void quicksort(node *head, node *tail)
{
	if(head->next != tail)
	{
		node *q = partition_lomuto(head, tail);
		quicksort(head, q);
		//quicksort(q->next, tail);
	}
}

node * partition_lomuto(node *head, node *tail) // head to jeden wczesniej, tail to ostatni
{
	node *tail_succ = tail->next; // wskaznik na element po tail
	
	node *left = (node *) malloc(sizeof(node)); // elementy mniejsze lub rowne (+ wartownik)
	left->next = NULL;
	node *left_last=NULL; // wskaznik na ostatni element lewej czesci
	
	node *right = (node *) malloc(sizeof(node)); // elementy wieksze (+ wartownik)
	right->next = NULL;
	node *right_last=NULL; // wskaznik na ostatni element prawej czesci
	
	node *tmp, *tmp_next; // wskazniki robocze 
	for(tmp = head->next, tmp_next = tmp->next; tmp != tail; tmp = tmp_next, tmp_next=tmp_next->next) // tmp ustawiamy na pierwszy sensowny element i jedziemy po liscie (pivot to tail)
	{
		if(tmp->val <= tail->val)
		{
			tmp->next = left->next;
			left->next = tmp;
			if(left_last == NULL)
				left_last = tmp;
		}
		else
		{
			tmp->next = right->next;
			right->next = tmp;
			if(right_last == NULL)
				right_last = tmp;
		}
	}
	
	// sklejanie list - 4 przypadki, bo nie wiem jak inaczej (a moze sie nawet nie da)
	if(left_last != NULL && right_last != NULL) // left i right sa niepuste
	{
		// przypinamy od konca
		right_last->next = tail_succ;
		tail->next = right->next;
		free(right);
		left_last->next = tail;
		head->next = left->next;
		free(left);
		return left_last;
	}
	else if(left_last == NULL && right_last == NULL) // left i right sa puste
	{
		// przypinamy od konca
		free(right);
		free(left);
		tail->next = tail_succ;
		head->next = tail;
		return head;
	}
	else if(left_last == NULL) // left jest puste
	{
		// przypinamy od konca
		right_last->next = tail_succ;
		tail->next = right->next;
		free(right);
		free(left);
		head->next = tail;
		return head;
	}
	else if(right_last == NULL) // right jest puste
	{
		// przypinamy od konca
		free(right);
		tail->next = tail_succ;
		left_last->next = tail;
		head->next = left->next;
		free(left);
		return left_last;
	}
	
	return tail; // zwracanie pivota
}
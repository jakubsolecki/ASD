#include "helper.c"

node * sort(node *head);
void insert(node *s, node *x);

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
	node *s = (node *) malloc(sizeof(node));
	s->next = NULL;
	node *tmp = head, *tmp_n;
	while(tmp != NULL)
	{
		tmp_n = tmp->next;
		insert(s, tmp);
		tmp = tmp_n;
	}
	tmp = s->next;
	free(s);
	return tmp;
}

void insert(node *s, node *x)
{
	while(s->next != NULL)
	{
		if(x->val < s->next->val) break;
		s = s->next;
	}
	x->next = s->next;
	s->next = x;
}
#include "push_swap.h"

void 	asip_fl_change(t_list **stack_A)
{
	t_list		*cur;

	cur = *stack_A;
	while (cur)
	{
		cur->content->flag = 0;
		cur = cur->next;
	}
}

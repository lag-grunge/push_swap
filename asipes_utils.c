#include "push_swap.h"

void 	asip_fl_change(t_dlist **stack_A)
{
	t_dlist		*cur;
    t_ps_data   *content;

	cur = *stack_A;
	while (cur)
	{
        content = cur->content;
        content->flag = 0;
		cur = cur->next;
	}
}
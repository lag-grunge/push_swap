#include "push_swap.h"

void 	asip_fl_change(t_dlist **stack_A)
{
	t_list		*cur;

	cur = *stack_A;
	while (cur)
	{
        ((t_ps_data *)cur->content)->flag = 0;
		cur = cur->next;
	}
}

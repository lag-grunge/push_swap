#include "push_swap.h"
#include "merge_sort.h"

/* merge_fl_change  - change flags
 * mode 0 - change in begin ( = pos of sorted array)
 * mode -1 - change when 1 chunk in stack
 * mode (>1) - change after merge of 2 chnks less length,
 * number of mode then is length of new chunk */

static void	merge_set_flag_default(t_dlist *cur, void *flag)
{
	t_ps_data	*content;

	content = cur->content;
	if (!flag)
	{
		content->flag = -(1 + content->pos);
		return ;
	}
	content->flag = *(size_t *)flag;
}

void	merge_fl_change_bottom(t_dlist *stack_A, size_t count, size_t flag)
{
	t_dlist	*cur;
	size_t	i;

	i = 0;
	cur = stack_A->prev;
	while (i < count)
	{
		merge_set_flag_default(cur, &flag);
		cur = cur->prev;
		i++;
	}
}

void	merge_fl_change(t_dlist *stack_A, int mode, size_t *flag)
{
	if (mode == 0)
		ft_dlstmap(stack_A, &merge_set_flag_default, flag);
}

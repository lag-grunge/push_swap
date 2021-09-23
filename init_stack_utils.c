#include "push_swap.h"

static t_dlist *check_item_and_next(t_dlist *item, int elem)
{
    t_ps_data   *content;

    content = item->content;
    if (elem == content->val)
        return (NULL);
    return (item->next);
}

static int	check_is_uniq(t_dlist *stack, int elem)
{
    t_dlist     *cur;

    if (!stack)
        return (1);
    cur = check_item_and_next(stack, elem);
	while (cur && cur != stack)
        cur = check_item_and_next(cur, elem);
    if (!cur)
        return (0);
    else
	    return (1);
}

static int	add_new_elem(t_dlist **stack, int elem)
{
	t_ps_data	*new_data;
	t_dlist		*new_list;

	new_data = (t_ps_data *)malloc(sizeof(t_ps_data) * 1);
	new_data->val = elem;
	new_data->pos = -1;
	new_list = ft_dlst_new_elem(new_data);
	if (!new_list)
		return (0);
    ft_dlst_add(stack, new_list);
	return (1);
}

int	proc_elem(t_dlist **stack, char **arg_sp, int j)
{
	int elem;

	elem = ft_atoi(arg_sp[j]);
	if (!(check_is_uniq(*stack, elem))) 
		return (2);
	else if (!(add_new_elem(stack, elem)))
		return (3);
	return (0);
}
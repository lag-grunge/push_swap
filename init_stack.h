#include "push_swap.h"

static t_dlist *check_item_and_next(t_dlist *item, int elem)
{
    t_ps_data   *content;

    content = item->content;
    if (elem == content->val)
        return (NULL);
    return (item->next);
}

int	check_is_uniq(t_dlist *stack, int elem)
{
    t_dlist     *cur;

    cur = stack;
    cur = check_item_and_next(stack, elem);
	while (cur && cur != stack)
        cur = check_item_and_next(cur, elem);
    if (!cur)
        return (0);
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

static size_t	ft_spllen(char **spl)
{
	size_t	i;

	i = 0;
	while (*spl++)
		i++;
	return (i);
}

static int	proc_elem(t_dlist **stack, char **arg_sp, int j)
{
	int elem;

	elem = ft_atoi(arg_sp[j]);
	if (!(check_is_uniq(*stack, elem))) 
		return (2);
	else if (!(add_new_elem(stack, elem)))
		return (3);
	return (0);
}

void	init_stack(int argc, char *argv[], t_dlist **stack, t_stck_data *data)
{
	int		i;
	int		j;
	char	**arg_sp;
	int		ret;
	t_dlist *cur_stack;

	i = argc;
	ret = 0;
	cur_stack = NULL;
	while (--i > 0)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(3, (void *)cur_stack, &free_stack, data); 
		j = ft_spllen(arg_sp);
		while (--j > -1 && ret == 0)
			ret = proc_elem(&cur_stack, arg_sp, j);
		free_split(arg_sp);
		if (ret)
			exit_error(ret, (void *)cur_stack, &free_stack, data);
	}
	*stack = cur_stack;
}

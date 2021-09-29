
#include "push_swap.h"
#include "libft.h"

static void	insert(t_dlist *cur, size_t i, int *arr_sorted)
{
	int	new_elem;

	new_elem = ((t_ps_data *)(cur->content))->val;
	while (i > 0 && new_elem < arr_sorted[i - 1])
	{
		arr_sorted[i] = arr_sorted[i - 1];
		i--;
	}
	arr_sorted[i] = new_elem;
}

static void correct_pos_for_elem(t_dlist *cur, void *arr_sorted)
{
    t_ps_data   *content;
    int         elem;
    size_t      i;

    content = cur->content;
    elem = content->val;
    i = 0;
    while (elem != ((int *)arr_sorted)[i])
        i++;
    content->pos = i;
}

int		*insertion_sort(t_dlist *stack, size_t size)
{
	int		*arr_sorted;
	size_t	i;
	t_dlist  *cur;

	cur = stack;
	arr_sorted = (int *)malloc(sizeof(int) * size);
	if (!arr_sorted)
		exit_error(3, NULL, NULL, NULL);
	i = 0;
	while (i < size)
	{
		insert(cur, i, arr_sorted);
		cur = cur->next;
		i++;
	}
    ft_dlstmap(stack, &correct_pos_for_elem, arr_sorted);
	return (arr_sorted);
}

void	check_if_stack_sorted(t_dlist **stack, int chckr, t_stck_data *data)
{
	t_dlist	*cur;
	size_t	i;

	cur = *stack;
	i = 0;
	while (cur != *stack || !i)
	{
		if (!(seek_pos(cur, i, 1)))
		{
			if (chckr)
				break ;
			return ;
		}
		i++;
		cur = cur->next;
	}
	if (i < data->size)
	{
		write(1, "KO\n", 3);
		exit_error(5, (void *)*stack, &free_stack, data);
	}
	else if (chckr)
		write(1, "OK\n", 3);
	else 
		exit_error(0, (void *)*stack, &free_stack, data);
}
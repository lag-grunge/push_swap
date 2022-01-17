/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorted_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:00:09 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:00:12 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static void	correct_pos_for_elem(t_dlist *cur, void *arr_sorted)
{
	t_ps_data	*content;
	int			elem;
	size_t		i;

	content = cur->content;
	elem = content->val;
	i = 0;
	while (elem != ((int *)arr_sorted)[i])
		i++;
	content->pos = i;
}

int	*insertion_sort(t_dlist *stack, size_t size)
{
	int		*arr_sorted;
	size_t	i;
	t_dlist	*cur;

	cur = stack;
	if (!size)
		return (NULL);
	arr_sorted = (int *)malloc(sizeof(int) * size);
	if (!arr_sorted)
		exit_error(MALLOC_ERROR, NULL, NULL, NULL);
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
	while (cur && (cur != *stack || !i))
	{
		if (get_pos(cur) != i)
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
		write(2, "KO\n", 3);
		exit_error(STACK_NOT_SORTED_O_NOT_FULL, *stack, &free_stack, data);
	}
	else if (chckr)
		write(2, "OK\n", 3);
	else
		exit_error(OK_STACK_SORTED, *stack, &free_stack, data);
}

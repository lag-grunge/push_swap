/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos_val.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 10:06:58 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/08 10:07:00 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	get_pos(t_dlist *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->pos);
}

size_t	get_flag(t_dlist *stack_elem)
{
	return (((t_ps_data *)(stack_elem->content))->flag);
}

size_t	*set_flag(t_dlist *stack_elem)
{
	return (&(((t_ps_data *)(stack_elem->content))->flag));
}

int	seek_pos(t_dlist *stack, size_t part, size_t size)
{
	size_t	pos;

	pos = ((t_ps_data *)(stack->content))->pos;
	if (pos >= part && pos < part + size)
		return (1);
	return (0);
}

void	partition(t_dlist **st_2, t_dlist **st_1, size_t start, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (seek_pos(*st_1, start, size))
		{
			execute_command("pb", st_1, st_2, 0);
			i++;
		}
		else
			execute_command("ra", st_1, st_2, 0);
	}
}

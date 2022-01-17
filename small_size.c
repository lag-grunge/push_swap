/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:56:37 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:56:44 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_2(t_dlist	**stack_A)
{
	if (seek_pos(*stack_A, 1, 1))
		execute_command("sa", stack_A, NULL, 0);
	return ;
}

void	small_3(t_dlist	**stack_A, int start)
{
	if (seek_pos(*stack_A, start + 2, 1))
		execute_command("ra", stack_A, NULL, 0);
	else if (seek_pos((*stack_A)->next, start + 2, 1))
		execute_command("rra", stack_A, NULL, 0);
	if (seek_pos(*stack_A, start + 1, 1))
		execute_command("sa", stack_A, NULL, 0);
	return ;
}

void	small_4(t_dlist	**stack_a)
{
	t_dlist	*stack_b;

	stack_b = NULL;
	partition(&stack_b, stack_a, 0, 1);
	small_3(stack_a, 1);
	execute_command("pa", stack_a, &stack_b, 0);
}

void	small_5(t_dlist	**stack_a)
{
	int		res;
	t_dlist	*stack_b;

	stack_b = NULL;
	res = 0;
	partition(&stack_b, stack_a, 0, 2);
	if (get_pos(stack_b) == 0)
	{
		if (get_pos(*stack_a) == 4)
			res = execute_command("rr", stack_a, &stack_b, 0);
		else if (get_pos((*stack_a)->next) == 4)
			res = execute_command("rrr", stack_a, &stack_b, 0);
		if (!res && get_pos(*stack_a) == 3)
			execute_command("ss", stack_a, &stack_b, 0);
		else if (get_pos(*stack_a) == 3)
			execute_command("sa", stack_a, &stack_b, 0);
		else if (!res)
			execute_command("sb", stack_a, &stack_b, 0);
	}
	else
		small_3(stack_a, 2);
	execute_command("pa", stack_a, &stack_b, 0);
	execute_command("pa", stack_a, &stack_b, 0);
}

void	small_size(t_dlist **stack_A, size_t size)
{
	if (size == 2)
		small_2(stack_A);
	else if (size == 3)
		small_3(stack_A, 0);
	else if (size == 4)
		small_4(stack_A);
	else if (size == 5)
		small_5(stack_A);
}

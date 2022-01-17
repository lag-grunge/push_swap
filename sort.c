/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:02:26 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:02:50 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort(t_dlist **stack_a, t_stck_data *data)
{
	t_dlist	*stack_b;

	if (data->size >= 2 && data->size <= 5)
	{
		small_size(stack_a, data->size);
		return ;
	}
	init_stack(0, NULL, &stack_b, data);
	distance_sort(stack_a, &stack_b, data);
	free_stack(stack_b);
}

/*	if (6 <= data->size && data->size <= ALGO_BORDER)
//		asipes_sort(stack_A, &stack_B, data);
//	else if (ALGO_BORDER < data->size)
//		merge_sort(stack_A, &stack_B, data);*/

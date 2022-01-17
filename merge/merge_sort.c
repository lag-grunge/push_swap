/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:01:38 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:01:48 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "merge_sort.h"

void	merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *cmn_data)
{
	t_merge	data;
	t_dlist	**stck_ptr[4];

	data.st_ptr = stck_ptr;
	init_data_flags(&data, cmn_data);
	init_data_stacks(&data, stack_B, stack_A);
	init_2chnks(&data);
	while (data.i_a != 1 || data.i_b != 0)
	{
		merge_chunks_of_one_size(&data);
		data.i_a = count_chunks(*stack_A);
		data.i_b = count_chunks(*stack_B);
	}
}

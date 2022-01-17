/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:00:15 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:00:21 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_data_stuff(t_stck_data *data)
{
	data->arr_sorted = NULL;
	data->cmd_array = NULL;
	data->op_lines = NULL;
	data->size_a = data->size;
	data->size_b = 0;
}

int	main(int argc, char *argv[])
{
	t_dlist		*stack_a;
	t_stck_data	data;

	check_input(argc, argv, &data);
	if (data.size == 0 || data.size == 1)
		exit_error(OK_STACK_SORTED, NULL, NULL, NULL);
	init_data_stuff(&data);
	init_stack(argc, argv, &stack_a, &data);
	data.arr_sorted = insertion_sort(stack_a, data.size);
	if (!data.arr_sorted)
		exit_error(MALLOC_ERROR, (void *) stack_a, &free_stack, &data);
	check_if_stack_sorted(&stack_a, IS_CHECKER, &data);
	data.cmd_array = init_command_array(&data);
	if (!data.cmd_array || !data.op_lines)
		exit_error(MALLOC_ERROR, (void *)stack_a, &free_stack, &data);
	sort(&stack_a, &data);
	exit_error(OK_STACK_SORTED, (void *)stack_a, &free_stack, &data);
}

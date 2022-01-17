/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:58:22 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:58:23 by sdalton          ###   ########.fr       */
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

static int	oper_lines(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
	char	*op_line;
	int		ret;

	ret = get_next_line(&op_line);
	if (ret == -1)
	{
		free_stack(*stack_B);
		exit_error(GNL_READ_MALLOC_ERROR, *stack_A, free_stack, data);
	}
	else if (ret == 0)
		return (ret);
	else if (!execute_command(op_line, stack_A, stack_B, 1))
	{
		free(op_line);
		free_stack(*stack_B);
		exit_error(INCORRECT_COMMAND, *stack_A, free_stack, data);
	}
	free(op_line);
	return (ret);
}

int	main(int argc, char *argv[])
{
	t_dlist		*stack_a;
	t_dlist		*stack_b;
	t_stck_data	data;
	int			ret;

	if (argc == 1)
		exit_error(0, NULL, NULL, NULL);
	check_input(argc, argv, &data);
	init_data_stuff(&data);
	init_stack(argc, argv, &stack_a, &data);
	data.arr_sorted = insertion_sort(stack_a, data.size);
	init_stack(0, NULL, &stack_b, &data);
	ret = oper_lines(&stack_a, &stack_b, &data);
	while (1 == ret)
		ret = oper_lines(&stack_a, &stack_b, &data);
	free_stack(stack_b);
	check_if_stack_sorted(&stack_a, IS_CHECKER, &data);
	exit_error(OK_STACK_SORTED, stack_a, &free_stack, &data);
}

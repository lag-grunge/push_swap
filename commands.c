/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:58:25 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:58:28 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	put_command(char *op_line)
{
	write(1, op_line, ft_strlen(op_line));
	write(1, "\n", 1);
}

static void	fill_op_lines(t_stck_data *data)
{
	data->op_lines = (char **)malloc(sizeof(char *) * (CMDS_NUMBER + 1));
	if (!data->op_lines)
		return ;
	data->op_lines[ra] = ft_strdup("ra");
	data->op_lines[rra] = ft_strdup("rra");
	data->op_lines[sa] = ft_strdup("sa");
	data->op_lines[pa] = ft_strdup("pa");
	data->op_lines[rb] = ft_strdup("rb");
	data->op_lines[rrb] = ft_strdup("rrb");
	data->op_lines[sb] = ft_strdup("sb");
	data->op_lines[pb] = ft_strdup("pb");
	data->op_lines[rr] = ft_strdup("rr");
	data->op_lines[rrr] = ft_strdup("rrr");
	data->op_lines[ss] = ft_strdup("ss");
	data->op_lines[CMDS_NUMBER] = NULL;
}

t_comnd	*init_command_array(t_stck_data *data)
{
	t_comnd	*cmd_array;

	cmd_array = malloc(sizeof(t_comnd) * CMDS_NUMBER);
	if (!cmd_array)
		return (NULL);
	cmd_array[ra] = rotate;
	cmd_array[rra] = reverse_rotate;
	cmd_array[sa] = swap;
	cmd_array[pa] = push;
	cmd_array[rb] = cmd_array[ra];
	cmd_array[rrb] = cmd_array[rra];
	cmd_array[sb] = cmd_array[sa];
	cmd_array[pb] = cmd_array[pa];
	cmd_array[rr] = rotate_both;
	cmd_array[rrr] = reverse_rotate_both;
	cmd_array[ss] = swap_both;
	fill_op_lines(data);
	return (cmd_array);
}

static int	solo(char *op_line, t_dlist **stack_A, t_dlist **stack_B, int chkr)
{
	if (!ft_strncmp("ra", op_line, MAX_COMMAND_LENGTH + 1))
		rotate(stack_A);
	else if (!ft_strncmp("rra", op_line, MAX_COMMAND_LENGTH + 1))
		reverse_rotate(stack_A);
	else if (!ft_strncmp("rb", op_line, MAX_COMMAND_LENGTH + 1))
		rotate(stack_B);
	else if (!ft_strncmp("rrb", op_line, MAX_COMMAND_LENGTH + 1))
		reverse_rotate(stack_B);
	else if (!ft_strncmp("sa", op_line, MAX_COMMAND_LENGTH + 1))
		swap(stack_A);
	else if (!ft_strncmp("sb", op_line, MAX_COMMAND_LENGTH + 1))
		swap(stack_B);
	else
		return (0);
	if (!chkr)
		put_command(op_line);
	return (1);
}

int	execute_command(char *op, t_dlist **stack_A, t_dlist **stack_B, int chkr)
{
	if (solo(op, stack_A, stack_B, chkr))
		return (1);
	else if (!ft_strncmp("pa", op, MAX_COMMAND_LENGTH + 1))
		push(stack_A, stack_B);
	else if (!ft_strncmp("pb", op, MAX_COMMAND_LENGTH + 1))
		push(stack_B, stack_A);
	else if (!ft_strncmp("rr", op, MAX_COMMAND_LENGTH + 1))
		rotate_both(stack_A, stack_B);
	else if (!ft_strncmp("rrr", op, MAX_COMMAND_LENGTH + 1))
		reverse_rotate_both(stack_A, stack_B);
	else if (!ft_strncmp("ss", op, MAX_COMMAND_LENGTH + 1))
		swap_both(stack_A, stack_B);
	else
		return (0);
	if (!chkr)
		put_command(op);
	return (1);
}

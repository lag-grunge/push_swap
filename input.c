/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:02:15 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:02:20 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_split(void *data)
{
	size_t	i;
	char	**arg_sp;

	i = 0;
	arg_sp = (char **)data;
	while (arg_sp[i])
	{
		free(arg_sp[i]);
		i++;
	}
	free(arg_sp);
}

void	free_stack(void *data)
{
	t_dlist	*stack;

	stack = (t_dlist *)data;
	ft_dlst_clear(&stack, &free);
}

void	free_data_stuff(void *stck_data)
{
	t_stck_data	*data;

	data = stck_data;
	if (data->arr_sorted)
		free(data->arr_sorted);
	if (data->cmd_array)
		free(data->cmd_array);
	if (data->op_lines)
		free_split(data->op_lines);
}

void	exit_error(size_t code, void *strct, t_fr_func func, t_stck_data *data)
{
	if (strct)
		func(strct);
	if (data)
		free_data_stuff(data);
	if (code != OK_STACK_SORTED && code != STACK_NOT_SORTED_O_NOT_FULL)
		write(2, ERROR_MSG, ft_strlen(ERROR_MSG));
	exit(code);
}

void	check_input(int argc, char *argv[], t_stck_data *data)
{
	int		i;
	int		j;
	char	**arg_sp;
	int		ovflw;

	i = 0;
	data->size = 0;
	ovflw = 0;
	while (++i < argc)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(MALLOC_ERROR, NULL, NULL, NULL);
		j = -1;
		while (arg_sp[++j])
		{
			if (!check_for_forbidden_symbols(arg_sp[j]))
				exit_error(INCORRECT_INPUT, (void *)arg_sp, &free_split, NULL);
			ft_atoi_base(arg_sp[j], "0123456789", "\0", &ovflw);
			if (ovflw)
				exit_error(INPUT_OVERFLOW, (void *)arg_sp, &free_split, NULL);
		}
		data->size += j;
		free_split(arg_sp);
	}
}

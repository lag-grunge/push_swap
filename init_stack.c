/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:59:06 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:59:07 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	init_stack(int argc, char *argv[], t_dlist **stack, t_stck_data *data)
{
	int		i;
	int		j;
	char	**arg_sp;
	int		ret;
	t_dlist	*cur_stack;

	i = argc;
	ret = 0;
	cur_stack = NULL;
	while (--i > 0)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(MALLOC_ERROR, (void *)cur_stack, &free_stack, data);
		j = ft_spllen(arg_sp);
		while (--j > -1 && ret == 0)
			ret = proc_elem(&cur_stack, arg_sp, j);
		free_split(arg_sp);
		if (ret)
			exit_error(ret, (void *)cur_stack, &free_stack, data);
	}
	*stack = cur_stack;
}

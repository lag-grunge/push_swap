/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:56:53 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:57:01 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "libft.h"

void	ft_dlstmap(t_dlist *dlst, void (*proc)(), void *params)
{
	t_dlist	*cur;

	cur = dlst;
	proc(cur, params);
	cur = cur->next;
	while (cur != dlst)
	{
		proc(cur, params);
		cur = cur->next;
	}
}

/*
int main(int argc, char *argv[])
{
	size_t	i;
	t_dlist	*dlst;
	t_dlist	*tmp;
	
	i = 1;
	while (i < argc)
	{
		ft_dlst_add(&dlst, argv[i]);
		i++;
	}
	i = 1;
	tmp = dlst;
	while (i < argc)
	{
		ft_putstr_fd(tmp->content, 1);
		printf("%p\n", tmp);
		i++;
		tmp = tmp->next;
	}
	ft_dlst_clear(dlst, free);
}*/

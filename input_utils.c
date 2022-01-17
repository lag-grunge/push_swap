/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:58:39 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:58:40 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	one_sign(char **s)
{
	if (**s == '+' || **s == '-')
		*s = *s + 1;
}

static void	whileisdigit(char **s)
{
	while (ft_isdigit(**s))
		*s = *s + 1;
}

int	check_for_forbidden_symbols(char *s)
{
	one_sign(&s);
	whileisdigit(&s);
	if (*s != 0)
		return (0);
	return (1);
}

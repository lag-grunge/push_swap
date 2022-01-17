/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   both_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:58:45 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:58:46 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_both(t_dlist **stack, t_dlist **stack2)
{
	rotate(stack);
	rotate(stack2);
}

void	reverse_rotate_both(t_dlist **stack, t_dlist **stack2)
{
	reverse_rotate(stack);
	reverse_rotate(stack2);
}

void	swap_both(t_dlist **stack, t_dlist **stack2)
{
	swap(stack);
	swap(stack2);
}

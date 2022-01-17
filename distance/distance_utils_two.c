/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:59:17 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:59:18 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	min_int(int *ind, int *array, int size)
{
	int	i;

	if (size < 1)
		return (0);
	*ind = 0;
	i = 1;
	while (i < size)
	{
		if (array[*ind] > array[i])
			*ind = i;
		i++;
	}
	return (array[*ind]);
}

static int	max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	min_dist(int a, int b, int *d)
{
	if (a <= b)
	{
		*d = b - a;
		return (a);
	}
	*d = a - b;
	return (b);
}

int	f(int rarb)
{
	if (rarb == ra)
		return (0);
	else if (rarb == rb)
		return (1);
	else if (rarb == rra)
		return (2);
	return (3);
}

int	find_actions(int *one_actions)
{
	int	min;
	int	ind;
	int	sums[4];

	sums[0] = max(one_actions[f(ra)], one_actions[f(rb)]);
	sums[1] = one_actions[f(ra)] + one_actions[f(rrb)];
	sums[2] = max(one_actions[f(rra)], one_actions[f(rrb)]);
	sums[3] = one_actions[f(rra)] + one_actions[f(rb)];
	min = min_int(&ind, sums, 4);
	if (ind == 2 || ind == 3)
		one_actions[f(ra)] = 0;
	if (ind == 0 || ind == 1)
		one_actions[f(rra)] = 0;
	if (ind == 1 || ind == 2)
		one_actions[f(rb)] = 0;
	if (ind == 0 || ind == 3)
		one_actions[f(rrb)] = 0;
	return (min);
}

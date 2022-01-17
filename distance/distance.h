/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:23:44 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:23:45 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISTANCE_H
# define DISTANCE_H

void	find_best_actions(int *min_actions, t_dlist **stack_a, \
							t_dlist **stack_b, t_stck_data *data);
int		find_actions(int *one_actions);
int		min_dist(int a, int b, int *d);
int		f(int rarb);

#endif

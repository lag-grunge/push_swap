/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asipes_sort.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 10:29:28 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 10:30:50 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASIPES_SORT_H
# define ASIPES_SORT_H

typedef struct s_cmn_asip_data {
	size_t	size;
	size_t	max;
	size_t	mid;
	size_t	next;
	size_t	flag;
	t_comnd	*cmd_array;
	char	**op_lines;
	t_dlist	**stack_a;
	t_dlist	**stack_b;
}				t_cmn_asip_data;

void	asip_fl_change(t_dlist **stack_a);
void	restore_data_max_mid(t_cmn_asip_data *data);
int		correct_a_chain(t_dlist **stack_a, t_cmn_asip_data *data);
int		oper_b_elem(t_cmn_asip_data *data, int sec);
void	init_data(t_cmn_asip_data *cmn_data, t_stck_data *data);
void	restore_size(t_cmn_asip_data *cmn_data, t_stck_data *data);
void	exec_n_cmd_asip(int cmd_num, size_t n, t_cmn_asip_data *data);

#endif

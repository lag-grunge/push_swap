/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 11:50:56 by sdalton           #+#    #+#             */
/*   Updated: 2022/01/16 11:50:58 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DLST_H
# define FT_DLST_H
# include <stdlib.h>

typedef struct s_dlist {
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

t_dlist	*ft_dlst_new_elem(void *content);
void	ft_dlst_add(t_dlist **dlst, t_dlist *new_elem);
size_t	ft_dlst_size(t_dlist *dlst);
t_dlist	*ft_dlst_pop(t_dlist **dlst, t_dlist *cur);
void	ft_dlst_clear(t_dlist **dlst, void (*free_func)(void *));
void	ft_dlstmap(t_dlist *dlst, void (*proc)(), void *params);

#endif

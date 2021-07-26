#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_ps_data	{
	int		val;
	size_t	pos;
}				t_ps_data;

void	free_split(void *data);
void	free_stack(void *data);
void exit_error(size_t err, void *strct, void (*free_func)(void *));
void	small_size(t_list **stack_A, int size);

void	rotate(t_list **stack);
void	push(t_list **stack1, t_list **stack2);
void	swap(t_list **stack);
int		seek_pos(t_list *stack, size_t part, size_t size);
void	partition(t_list **stack2, t_list **stack1, size_t part, size_t size);

void	insert(t_list *cur, size_t i, int *arr_sorted);
int		*insertion_sort(t_list *stack, size_t size);
void	correct_pos(t_list *stack, int *arr_sorted);

int	check_is_uniq(t_list *stack, int elem);
int	add_new_elem(t_list **stack, int elem);
int	proc_elem(t_list **stack, char **arg_sp, int j);
int check_is_zero(char *s);
size_t	check_input(int argc, char *argv[]);
t_list	*init_stack(int argc, char *argv[]);

void	small_2(t_list	**stack);
void	small_3(t_list	**stack);
void	small_4(t_list	**stack);
void	small_5(t_list	**stack);

#include <stdio.h>
void print_arr(int *arr, size_t size);
void print_stack(t_list *stack);
#endif

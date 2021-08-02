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
void exit_error(size_t err, void *strct, void (*free_func)(void *), int *arr);
void	small_size(t_list **stack_A, int size);

void	rotate(t_list **stack);
void	reverse_rotate(t_list **stack);
void	push(t_list **stack1, t_list **stack2);
void	swap(t_list **stack);
int		seek_pos(t_list *stack, size_t part, size_t size);
size_t	get_pos(t_list *stack, size_t i);
void	rotate_both(t_list **stack1, t_list **stack2);
void	reverse_rotate_both(t_list **stack1, t_list **stack2);
void	swap_both(t_list **stack1, t_list **stack2);
void	partition(t_list **stack2, t_list **stack1, size_t part, size_t size);

int get_next_line(char **line);
int 	execute_command(char *op_line, t_list **stack_A, t_list **stack_B);
# define ra rotate(stack_A);
# define rra reverse_rotate(stack_A);
# define sa swap(stack_A);
# define pa push(stack_A, stack_B);
# define rb rotate(stack_B);
# define rrb reverse_rotate(stack_B);
# define sb swap(stack_B);
# define pb push(stack_B, stack_A);
# define rrr reverse_rotate_both(stack_A, stack_B);
# define rr rotate_both(stack_A, stack_B);
# define ss swap_both(stack_A, stack_B);

void	insert(t_list *cur, size_t i, int *arr_sorted);
int		*insertion_sort(t_list *stack, size_t size);
void	correct_pos(t_list *stack, int *arr_sorted);
void	check_if_stack_sorted(t_list **stack, size_t size, int chckr, int *arr);

int	check_is_uniq(t_list *stack, int elem);
int	add_new_elem(t_list **stack, int elem);
int	proc_elem(t_list **stack, char **arg_sp, int j);
int check_is_zero_or_overflow(char *s, int elem);
size_t	check_input(int argc, char *argv[]);
void	init_stack(int argc, char *argv[], t_list **stack);

void	small_2(t_list	**stack);
void	small_3(t_list	**stack, int start);
void	small_4(t_list	**stack);
void	small_5(t_list	**stack);

void radix_sort(t_list **stack_A, t_list **stack_B, size_t size);
void big_sort(t_list **stack_A, t_list **stack_B, size_t size);

#include <stdio.h>
void print_arr(int *arr, size_t size);
void print_stack(t_list *stack);
#endif

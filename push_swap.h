#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_dlst.h"

typedef struct s_ps_data	{
	int		val;
	size_t	pos;
	size_t	flag;
}				t_ps_data;

typedef struct s_stck_data	{
	size_t	size;
	size_t	i_A;
	size_t	i_B;
	int		*arr_sorted;
}				t_stck_data;

typedef	struct s_cmn_asip_data	{
	size_t  size;	
	size_t	max;
	size_t	mid;
	size_t	next;
	size_t	flag;
}				t_cmn_asip_data;

typedef void (*free_func)(void *);

void	free_split(void *data);
void	free_stack(void *data);
void	exit_error(size_t err, void *strct, free_func f, t_stck_data *data);
void	small_size(t_dlist **stack_A, size_t size);

void	rotate(t_dlist **stack);
void	reverse_rotate(t_dlist **stack);
void	push(t_dlist **stack1, t_dlist **stack2);
void	swap(t_dlist **stack);
int		seek_pos(t_dlist *stack, size_t part, size_t size);
size_t	get_pos(t_dlist *stack_elem);
int		get_flag(t_dlist *stack_elem);
size_t	*set_flag(t_dlist *stack_elem);
void	rotate_both(t_dlist **stack1, t_dlist **stack2);
void	reverse_rotate_both(t_dlist **stack1, t_dlist **stack2);
void	swap_both(t_dlist **stack1, t_dlist **stack2);
void	partition(t_dlist **stack2, t_dlist **stack1, size_t part, size_t size);

int 	get_next_line(char **line);
int 	execute_command(char *op_line, t_dlist **stack_A, t_dlist **stack_B);

void	insert(t_dlist *cur, size_t i, int *arr_sorted);
int		*insertion_sort(t_dlist *stack, size_t size);
void	correct_pos(t_dlist *stack, int *arr_sorted);
void	check_if_stack_sorted(t_dlist **stack, int chckr, t_stck_data *data);

//int	check_is_uniq(t_dlist *stack, int elem);
//int	add_new_elem(t_dlist **stack, int elem);
//int	proc_elem(t_dlist **stack, char **arg_sp, int j);
//int check_is_zero_or_overflow(char *s, int elem);
void	check_input(int argc, char *argv[], t_stck_data *stck_data);
void	init_stack(int argc, char *argv[], t_dlist **stack, t_stck_data *data);

void	small_2(t_dlist	**stack);
void	small_3(t_dlist	**stack, int start);
void	small_4(t_dlist	**stack);
void	small_5(t_dlist	**stack);

void radix_sort(t_dlist **stack_A, t_dlist **stack_B, size_t size);
int 	merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);
int 	asipes_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);
	void 	merge_fl_change(t_dlist **stack_A);
	void 	asip_fl_change(t_dlist **stack_A);
	void restore_data_max_mid(t_cmn_asip_data *data);
    int operBelem(t_dlist **stack_A, t_dlist **stack_B, t_cmn_asip_data *data, int sec);
	
void big_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);

#define MAX_COMMAND_LENGTH 3
#define ERROR_1 "Error: non-integer elem\n"
#define ERROR_2 "Error: non-unique elem\n"
#define ERROR_3 "Error: cannot allocate memory or non-correct arg\n"
#define ERROR_4 "Error: checker got non-correct command\n"
#define ERROR_5 "Error: stack_A is not full or not sorted\n"

#include <stdio.h>
void print_arr(int *arr, size_t size);
void print_stack(t_dlist *stack);
void	debug_print_stack(t_dlist **stack_A, t_dlist **stack_B);
#endif

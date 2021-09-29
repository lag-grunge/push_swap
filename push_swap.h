#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> //----------------------------------
#include "libft/libft.h"
#include "libft/ft_dlst/ft_dlst.h"

typedef void (*free_func)(void *);
typedef void (*command)();
enum cmds_codes {ra, rra, sa, pa, rb, rrb, sb, pb, rr, rrr, ss};
#define CMDS_NUMBER 11

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
    command *cmd_array;
    char    **op_lines;
}				t_stck_data;



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
size_t	get_flag(t_dlist *stack_elem);
size_t	*set_flag(t_dlist *stack_elem);
void	rotate_both(t_dlist **stack1, t_dlist **stack2);
void	reverse_rotate_both(t_dlist **stack1, t_dlist **stack2);
void	swap_both(t_dlist **stack1, t_dlist **stack2);
void	partition(t_dlist **stack2, t_dlist **stack1, size_t part, size_t size);

int 	get_next_line(char **line);
void	put_command(char *op_line);
int 	execute_command(char *op_line, t_dlist **stack_A, t_dlist **stack_B);
command *init_command_array(t_stck_data *data);

int		*insertion_sort(t_dlist *stack, size_t size);
void	correct_pos(t_dlist *stack, int *arr_sorted);
void	check_if_stack_sorted(t_dlist **stack, int chckr, t_stck_data *data);

void	check_input(int argc, char *argv[], t_stck_data *stck_data);
void	init_stack(int argc, char *argv[], t_dlist **stack, t_stck_data *data);
int	    proc_elem(t_dlist **stack, char **arg_sp, int j);

void	small_2(t_dlist	**stack);
void	small_3(t_dlist	**stack, int start);
void	small_4(t_dlist	**stack);
void	small_5(t_dlist	**stack);

void    merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);
void    merge_sort2(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *cmn_data);
void    radix_sort(t_dlist **stack_A, t_dlist **stack_B, size_t size);
int 	asipes_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);

void big_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);

#define MAX_COMMAND_LENGTH 3
#define ERROR_1 "Error: non-integer elem\n"
#define ERROR_2 "Error: non-unique elem\n"
#define ERROR_3 "Error: cannot allocate memory or non-correct arg\n"
#define ERROR_4 "Error: checker got non-correct command\n"
#define ERROR_5 "Error: stack_A is not full or not sorted\n"

void    print_arr(int *arr, size_t size);
void    print_stack(t_dlist *stack);
void    debug_print_stack(t_dlist **stack_A, t_dlist **stack_B);
#endif

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

int		seek_pos(t_dlist *stack, size_t part, size_t size);
size_t	get_pos(t_dlist *stack_elem);
size_t	get_flag(t_dlist *stack_elem);
size_t	*set_flag(t_dlist *stack_elem);

void	rotate(t_dlist **stack);
void	reverse_rotate(t_dlist **stack);
void	push(t_dlist **stack1, t_dlist **stack2);
void	swap(t_dlist **stack);
void	rotate_both(t_dlist **stack1, t_dlist **stack2);
void	reverse_rotate_both(t_dlist **stack1, t_dlist **stack2);
void	swap_both(t_dlist **stack1, t_dlist **stack2);
void	partition(t_dlist **stack2, t_dlist **stack1, size_t part, size_t size);

int 	get_next_line(char **line);
void	put_command(char *op_line);
int 	execute_command(char *op_line, t_dlist **stack_A, t_dlist **stack_B);
command *init_command_array(t_stck_data *data);

int		*insertion_sort(t_dlist *stack, size_t size);
void	check_if_stack_sorted(t_dlist **stack, int chckr, t_stck_data *data);

void	check_input(int argc, char *argv[], t_stck_data *stck_data);
void	init_stack(int argc, char *argv[], t_dlist **stack, t_stck_data *data);
int	    proc_elem(t_dlist **stack, char **arg_sp, int j);

void	small_size(t_dlist **stack_A, size_t size);
void	small_2(t_dlist	**stack);
void	small_3(t_dlist	**stack, int start);
void	small_4(t_dlist	**stack);
void	small_5(t_dlist	**stack);

void    sort(t_dlist **stack_A, t_stck_data *data);
void    merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);
int 	asipes_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data);

#ifndef ALGO_BORDER
# define ALGO_BORDER 420
#endif

#define MAX_COMMAND_LENGTH 3
#define COMMAND_NOT_EXECUTES 4
#define GNL_READ_MALLOC_ERROR 5
#define ERROR_MSG "Error\n"

void    print_arr(int *arr, size_t size);
void    print_stack(t_dlist *stack);
void    debug_print_stack(t_dlist **stack_A, t_dlist **stack_B);
#endif

#ifndef MERGE_SORT_H
# define MERGE_SORT_H

typedef struct s_merge_data
{
	t_dlist	**stack_A;
	t_dlist	**stack_B;
	t_dlist	***st_ptr;
	size_t	size;
	size_t	i_A;
	size_t	i_B;
	size_t	cur_flag;
	t_comnd	*cmd_array;
	char	**op_lines;
}	t_merge;

enum e_stcks_names
{
	first_stack,
	second_stack,
	stack_for_input,
	cur_stack
};
enum e_oper_mode
{
	from_b_to_a,
	from_a_to_a,
	from_a_to_b,
	from_b_to_b
};

void	merge_fl_change(t_dlist *stack_A, int mode, size_t *flag);
void	merge_fl_change_bottom(t_dlist *stack_A, size_t count, size_t flag);

void	init_2chnks(t_merge *data);
void	init_data_flags(t_merge *data, t_stck_data *cmn_data);
void	init_data_stacks(t_merge *data, t_dlist **stack_B, t_dlist **stack_A);

void	merge_chunks_of_one_size(t_merge *data);
size_t	init_oper_one_nchnk(t_merge *data, size_t *chunk_0, size_t *chunk_1);

int		is_same_chain(size_t a, size_t b, int mode);
size_t	find_chunk_size(t_dlist *stack, size_t cur_flag);
size_t	count_chunks(t_dlist *stack);

void	exec_n_cmd_merge(int cmd_num, size_t n, t_merge *data);

#endif

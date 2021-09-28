#ifndef MERGE_SORT_H
# define MERGE_SORT_H

typedef struct s_merge_data
{
    t_dlist **stack_A;
    t_dlist **stack_B;
    size_t i_A;
    size_t i_B;
    size_t cur_flag;
    int    algo_type;
    command *cmd_array;
    char    **op_lines;
}   t_merge_data;

enum stcks_names {first_stack, second_stack, stack_for_input, cur_stack};
enum oper_mode {from_b_to_a, from_a_to_a, from_a_to_b, from_b_to_b };

#define CHUNKS_DIFF 2

void 	merge_fl_change(t_dlist *stack_A, int mode, size_t *flag);
void 	merge_fl_change_bottom(t_dlist *stack_A, size_t count, size_t flag);
void 	merge_fl_change_next(t_dlist *stack_A, size_t count, size_t flag);
void merge_set_flag_second(t_dlist *cur, size_t *start);

void    init_2chnks(t_merge_data *data);
void    init_data_flags_and_stacks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data, t_stck_data *cmn_data);

void	merge_chunks_of_one_size(t_merge_data *data);
void    merge2_chunks_of_one_size(t_merge_data *data);

int     is_same_chain(size_t a, size_t b, int mode);
size_t	find_chunk_size(t_dlist *stack, size_t cur_flag);
size_t  find_bottom_chunk_size(t_dlist *stack);
size_t  count_chunks(t_dlist *stack);
size_t get_chain_changes(t_dlist *stack_A);

void    execute_n_command(int cmd_num, size_t n, t_merge_data *data);

#endif
#ifndef MERGE_SORT_H
# define MERGE_SORT_H

typedef struct s_merge_data
{
    t_dlist **stack_A;
    t_dlist **stack_B;
    size_t i_A;
    size_t i_B;
    size_t cur_flag;
}   t_merge_data;

enum stcks_names {first_stack=0, second_stack=1, stack_for_input=2, cur_stack=3};
enum oper_mode {from_b_to_a, from_a_to_a, from_a_to_b, from_b_to_b };

#define CHUNKS_DIFF 2

void 	merge_fl_change(t_dlist *stack_A, int mode, size_t flag);
void    init_2chnks(t_merge_data *data);
void	merge_chunks_of_one_size(t_merge_data *data);
size_t	find_chunk_size(t_dlist *stack, size_t cur_flag);
size_t  find_bottom_chunk_size(t_dlist *stack);
void    shift_small_bottom_chunk(t_merge_data *data, t_dlist **stck_ptr[4]);

#endif
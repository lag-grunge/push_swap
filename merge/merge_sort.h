#ifndef MERGE_SORT_H
# define MERGE_SORT_H

typedef struct s_merge_data
{
    size_t i_A;
    size_t i_B;
    size_t cur_flag;
}   t_merge_data;

void 	merge_fl_change(t_dlist *stack_A, int mode, size_t flag);
void    init_2chnks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data);
void	merge_chunks_of_one_size(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data);
size_t	find_chunk_size(t_dlist *stack, size_t cur_flag);

#endif
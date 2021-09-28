#include "push_swap.h"
#include "merge_sort.h"

void    merge_sort2(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *cmn_data)
{
    t_merge_data data;

    data.algo_type = 2;
    init_data_flags_and_stacks(stack_A, stack_B, &data, cmn_data);
    while (data.i_A != 1 || data.i_B != 0) {
        merge2_chunks_of_one_size(&data);
        data.i_A = count_chunks(*stack_A);
        data.i_B = count_chunks(*stack_B);
    }
}

void 	merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *cmn_data)
{
    t_merge_data    data;

    data.algo_type = 0;
    init_data_flags_and_stacks(stack_A, stack_B, &data, cmn_data);
    init_2chnks(&data);
    while (data.i_A != 1 || data.i_B != 0) {
        merge_chunks_of_one_size(&data);
        data.i_A = count_chunks(*stack_A);
        data.i_B = count_chunks(*stack_B);
    }
}
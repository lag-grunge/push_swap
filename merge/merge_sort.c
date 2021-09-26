#include "push_swap.h"
#include "merge_sort.h"

void    merge_sort2(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *cmn_data)
{
    t_merge_data data;

    data.algo_type = 2;
    init_data_flags_and_stacks(stack_A, stack_B, &data, cmn_data);
    //debug_print_stack(data.stack_A, data.stack_B);////
    while (data.i_A != 1 || data.i_B != 0) {
        merge_chunks_of_one_size(&data);
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
        //debug_print_stack(data.stack_A, data.stack_B);////
    }
}

//ПЕРЕБРОСИТЬ ПОЛОВИНУ В СТЕК Б
//РАЗМЕР ЦЕПОЧЕК = 1
//ПОКА НЕ ПОЛУЧИТСЯ БОЛЬШАЯ ЦЕПОЧКА (=data->size)
//	ОБЪЕДИНЯТЬ ЦЕПОЧКИ (ИЗ РАЗНЫХ СТЕКОВ >= 2 из ОДНОГО ЕСЛИ == 1, кроме случая когда на конце осталось по 1 элементу ) 


#include "push_swap.h"
#include "merge_sort.h"

/* merge_fl_change  - change flags
 * mode 0 - change in begin ( = pos of sorted array)
 * mode -1 - change when 1 chunk in stack
 * mode (>1) - change after merge of 2 chnks less length,
 * number of mode then is length of new chunk */

static void 	half_2stack_b(t_dlist **stack_A, t_dlist **stack_B, size_t size, t_merge_data *data)
{
	size_t	i;

	i = 0;
	while (i < size / 2)
	{
		execute_command("pb", stack_A, stack_B);
		i++;
	}
	data->i_A = size - i;
	data->i_B = i;
}

void 	merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *cmn_data)
{
    t_merge_data    data;

    merge_fl_change(*stack_A, 0, 0);
    half_2stack_b(stack_A, stack_B, cmn_data->size, &data);
    init_2chnks(stack_A, stack_B, &data);
	while (data.i_A > 1 && data.i_B > 0)
	    merge_chunks_of_one_size(stack_A, stack_B, &data);
}

//ПЕРЕБРОСИТЬ ПОЛОВИНУ В СТЕК Б
//РАЗМЕР ЦЕПОЧЕК = 1
//ПОКА НЕ ПОЛУЧИТСЯ БОЛЬШАЯ ЦЕПОЧКА (=data->size)
//	ОБЪЕДИНЯТЬ ЦЕПОЧКИ (ИЗ РАЗНЫХ СТЕКОВ >= 2 из ОДНОГО ЕСЛИ == 1, кроме случая когда на конце осталось по 1 элементу ) 


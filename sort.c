#include "push_swap.h"

void sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
    t_dlist 	*stack_B;

    if (data.size > 1 && data.size < 6) { small_size(&stack_A, data.size); }
    else {
        init_stack(0, NULL, &stack_B, &data);
        big_sort(&stack_A, &stack_B, &data);
        free_stack(stack_B);
    }
    // 0 (ARG= )
    // 1 - 0
    // 2 - AVG - 0, MAX - 1 )))
    // 3 - AVG - 1, MAX -  2
    // 4 - AVG - 4, MAX - 7
    // 5 - WRONG ------------------------------------

    //asipes_sort(stack_A, stack_B, data);
    /* 6 - AVG: 19, MAX:  22
     * 10 - AVG: 37 MAX:  44
     * 20 - AVG: 91 MAX:  105
     * 50 - AVG: 292 MAX:  320
     * 100 - AVG: 719 MAX:  776
     * 500 - AVG: 6994 MAX:  7495
    */

    //radix_sort(stack_A, stack_B, data->size);
    /* 6 - 29
     * 8 - 52
     * 10 - 65
     * 20 - 160
     * 50 - 467
     * 100 - 1084
     * 500 - 6784

     */
	// merge_sort2(stack_A, stack_B, data);
    /* 8 - WRONG
     * 10 - WRONG
     * 20 - WRONG
     * 50 - AVG: 421 MAX:  514
     * 100 - AVG: 959 MAX:  1063
     * 500 - AVG: 6606 MAX:  6824
     */
    merge_sort(stack_A, stack_B, data);
    /* 6,7 - WRONG
     * 6 - AVG: 25, MAX:  27
     * 8 - AVG: 33 MAX:  34
     * 10 - AVG: 56 MAX:  60
     * 20 - AVG: 145 MAX:  147
     * 50 - AVG: 427 MAX:  458
     * 100 - AVG: 984 MAX:  991
     * 500 - AVG: 6595 MAX:  6611
    */

    /* 6 - WRONG
     * 10 -
     * 20 -
     * 50 -
     * 100 -
     * 500 -
     */

}
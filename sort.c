#include "push_swap.h"

void big_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *data)
{
    //asipes_sort(stack_A, stack_B, data->size);
    radix_sort(stack_A, stack_B, data->size);
    /* 8 - WRONG
     * 10 - WRONG
     * 20 - WRONG
     * 50 - ???? AVG: 421 MAX:  713
     * 100 -
     * 500 - ??? AVG: 7022 MAX:  7318

     */
	// merge_sort2(stack_A, stack_B, data);
    /* 8 - WRONG
     * 10 - WRONG
     * 20 - WRONG
     * 50 - AVG: 421 MAX:  514
     * 100 - AVG: 959 MAX:  1063
     * 500 - AVG: 6606 MAX:  6824
     */
    //merge_sort(stack_A, stack_B, data);
    /* 6,7 - WRONG
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
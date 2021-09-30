#include "push_swap.h"

void sort(t_dlist **stack_A, t_stck_data *data)
{
    t_dlist 	*stack_B;

    if (data->size >= 2 && data->size <= 5)
    {
        small_size(stack_A, data->size);
        return ;
    }
    init_stack(0, NULL, &stack_B, data);
    if (6 <= data->size && data->size < ALGO_BORDER)
        asipes_sort(stack_A, &stack_B, data);
    else if (ALGO_BORDER <= data->size)
        merge_sort(stack_A, &stack_B, data);
    free_stack(stack_B);
}

// 0 (ARG= )
// 1 - 0
// 2 - AVG - 0, MAX - 1 )))
// 3 - AVG - 1, MAX -  2
// 4 - AVG - 4, MAX - 7
// 5 - AVG: 7 MAX:  9

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


//merge_sort(stack_A, stack_B, data);
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

/*ALGO_BORDER 100
asipes 98
MAX:  722
merge 102
MAX:  1011
ALGO_BORDER 120
asipes 118
MAX:  934
merge 122
MAX:  1245
ALGO_BORDER 140
asipes 138
MAX:  1117
merge 142
MAX:  1692
ALGO_BORDER 160
asipes 158
MAX:  1382
merge 162
MAX:  1938
ALGO_BORDER 180
asipes 178
MAX:  1544
merge 182
MAX:  2128
ALGO_BORDER 200
asipes 198
MAX:  1796
merge 202
MAX:  2294
ALGO_BORDER 220
asipes 218
MAX:  2085
merge 222
MAX:  2548
ALGO_BORDER 240
asipes 238
MAX:  2419
merge 242
MAX:  2828
ALGO_BORDER 260
asipes 258
MAX:  2697
merge 262
MAX:  3565
ALGO_BORDER 280
asipes 278
MAX:  2917
merge 282
MAX:  3787
ALGO_BORDER 300
asipes 298
MAX:  3214
merge 302
MAX:  4048
ALGO_BORDER 320
asipes 318
MAX:  3685
merge 322
MAX:  4340
ALGO_BORDER 340
asipes 338
MAX:  3747
merge 342
MAX:  4565
ALGO_BORDER 360
asipes 358
MAX:  4154
merge 362
MAX:  4778
ALGO_BORDER 380
asipes 378
MAX:  4749
merge 382
MAX:  5050
ALGO_BORDER 400
asipes 398
MAX:  4885
merge 402
MAX:  5164
ALGO_BORDER 420
asipes 418
MAX:  5430
merge 422
MAX:  5464
ALGO_BORDER 440
asipes 438
MAX:  5714
merge 442
MAX:  5728
ALGO_BORDER 460
asipes 458
MAX:  6403
merge 462
MAX:  6059
ALGO_BORDER 480
asipes 478
MAX:  6532
merge 482
MAX:  6391
ALGO_BORDER 500
asipes 498
MAX:  7044
merge 502
MAX:  6625
*/
#include "push_swap.h"
#include "merge_sort.h"

/* operate 2-chunks - init 2chunks, i.e. chains of list items with same flag
 * initially there are only 1-chunks, items have flag that eq their pos field
 * We have merge_data struct, that stores chunks of cur_size in A, chunks of cur_size in B,
 * after merge it equals the number before merge minus number of merging iters
 * with stack (31 1-chunk (15 iter) 16 chunk = 15 2-chunk + 1 1-chunk)
 * There are practically equal amount of items, may be differ not more than 1
 * Also if there is not pair for item not in its stack nor in another one
 * we account it as 1-chunk with new flag
 * For these issues we use tail_2chunks
 * A: 31 1-chunk B: 31 1-chunk
 * (31 / 2 = 15 iter)
 * 16 chunk = 15x2 + 1
 * 16 chunk = 15x2 + 1
 * o_tail_chunk
 * 16 chunk = 16x2
 * 15 chunk = 15x2
 * */

static void o_both_tail_equal(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data)
{
    if (get_pos(*stack_A) < get_pos(*stack_B))
    {
        execute_command("pb", stack_A, stack_B);
        execute_command("rb", stack_A, stack_B);
        execute_command("rb", stack_A, stack_B);
        merge_fl_change_bottom(*stack_B, 2, data->cur_flag);
        data->i_B++;
    }
    else
    {
        execute_command("pa", stack_A, stack_B);
        execute_command("ra", stack_A, stack_B);
        execute_command("ra", stack_A, stack_B);
        merge_fl_change_bottom(*stack_A, 2, data->cur_flag);
        data->i_A++;
    }
}

static void o_a_tail_longer(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data)
{
    if (get_flag((*stack_A)->next) > data->cur_flag)
    {
        if (get_pos(*stack_A) > get_pos((*stack_A)->next))
            execute_command("sa", stack_A, stack_B);
        execute_command("rr", stack_A, stack_B);
        execute_command("ra", stack_A, stack_B);
        merge_fl_change_bottom(*stack_A, 2, data->cur_flag);
        merge_fl_change_bottom(*stack_B, 1, data->cur_flag + 1);
    }
    else
    {
        execute_command("ra", stack_A, stack_B);
        merge_fl_change_bottom(*stack_A, 1, data->cur_flag);
    }
    data->i_A++;
}
static void	o_tail_2chnks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data)
{
    size_t  tailA;
    size_t  tailB;

    tailA = find_chunk_size(*stack_A, data->cur_flag);
    tailA += find_chunk_size((*stack_A)->next, data->cur_flag);
    tailB = find_chunk_size(*stack_B, data->cur_flag);
    if (tailA == tailB)
        o_both_tail_equal(stack_A, stack_B, data);
    else
        o_a_tail_longer(stack_A, stack_B, data);
    data->cur_flag = 0;
}

static void oper_two_top_elem(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data)
{
    int retA;
    int retB;

    retA = 0;
    retB = 0;
    if (get_pos(*stack_A) > get_pos((*stack_A)->next))
        retA = 1;
    if (get_pos(*stack_B) > get_pos((*stack_B)->next))
        retB = 1;
    if (retA && retB)
        execute_command("ss", stack_A, stack_B);
    else if (retA)
        execute_command("sa", stack_A, stack_B);
    else if (retB)
        execute_command("sb", stack_A, stack_B);
    execute_command("rr", stack_A, stack_B);
    execute_command("rr", stack_A, stack_B);
    merge_fl_change_bottom(*stack_B, 2, data->cur_flag);
    merge_fl_change_bottom(*stack_A, 2, data->cur_flag + 1);
    data->cur_flag += 2;
}

void init_2chnks(t_merge_data *data)
{
    size_t  ib;
    size_t  ia;

    ib = data->i_B;
    ia = data->i_A;
    while (ib > 1) {
        oper_two_top_elem(data->stack_A, data->stack_B, data);
        ib -= 2;
        ia -= 2;
    }
    data->i_A = data->i_B / 2;
    data->i_B = data->i_B / 2;
    if (!ib && !ia)
    {
        data->cur_flag = 0;
        //debug_print_stack(data->stack_A, data->stack_B);
        return;
    }
    o_tail_2chnks(data->stack_A, data->stack_B, data);
    //debug_print_stack(data->stack_A, data->stack_B);
}
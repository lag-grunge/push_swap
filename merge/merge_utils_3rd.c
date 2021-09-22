#include "push_swap.h"
#include "merge_sort.h"

/* merge chunks of one size, accurately not more than this size
 * we operate one pair of chunks, then rotate merged result on the
 * bottom as these chunks are situated on top of the stacks A and B
 * we found size of chunks, if this size eq 0, it means this chunk new
 * one so we've rotated whole stack and can continue only with other
 * if it has chunk */

static size_t    oper_one_elem(t_dlist **stack_A, t_dlist **stack_B, t_dlist *cur_stack, t_dlist *stack_for_input)
{
    size_t  ret;

    ret = 0;
    if (stack_for_input == *stack_A)
    {
        if (cur_stack == *stack_B && (get_pos(*stack_A) > get_pos(*stack_B)))
        {
            execute_command("pa", stack_A, stack_B);
            ret += execute_command("ra", stack_A, stack_B);
        }
        if (cur_stack == *stack_A && (get_pos(*stack_A) < get_pos(*stack_B)))
            ret += execute_command("ra", stack_A, stack_B);
    }
    else if (stack_for_input == *stack_B)
    {
        if (cur_stack == *stack_A && (get_pos(*stack_A) < get_pos(*stack_B)))
        {
            execute_command("pb", stack_A, stack_B);
            ret += execute_command("rb", stack_A, stack_B);
        }
        if (cur_stack == *stack_B && (get_pos(*stack_A) > get_pos(*stack_B)))
            ret += execute_command("rb", stack_A, stack_B);
    }
    return (ret);
}

static int oper_one_nchnk(t_dlist **stack_A, t_dlist **stack_B, t_dlist *stack_for_input, t_merge_data *data)
{
    size_t  chunk_a;
    size_t  chunk_b;
    size_t  chunk_res;

    chunk_a = find_chunk_size(*stack_A, data->cur_flag);
    chunk_b = find_chunk_size(*stack_B, data->cur_flag);
    chunk_res = chunk_a + chunk_b;
    if (!chunk_res)
        return (0);
    if (!chunk_a && stack_for_input == *stack_A)
        stack_for_input = *stack_B;
    if (!chunk_b && stack_for_input == *stack_B)
        stack_for_input = *stack_A;
    if (stack_for_input == *stack_A)
        data->i_A++;
    else
        data->i_B++;
    while (chunk_a || chunk_b)
    {
        if (chunk_a)
            chunk_a -= oper_one_elem(stack_A, stack_B, *stack_A, stack_for_input);
        if (chunk_b)
            chunk_b -= oper_one_elem(stack_A, stack_B, *stack_B, stack_for_input);
    }
    merge_fl_change(stack_for_input, chunk_res, data->cur_flag);
    data->cur_flag++;
    return (1);
}

static void init_merge_chunks_of_one_size(t_merge_data *data, size_t *i_min, size_t *i_max, t_dlist **stck_ptr[2])

{
    t_dlist **cur_stack;

    *i_min = data->i_B;
    *i_max = data->i_A;
    if (data->i_A <= data->i_B)
    {
        cur_stack = stck_ptr[1];
        stck_ptr[1] = stck_ptr[0];
        stck_ptr[0] = cur_stack;
        *i_min = data->i_A;
        *i_max = data->i_B;
    }
    data->i_A = 0;
    data->i_B = 0;
}

void	merge_chunks_of_one_size(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data)
{
    t_dlist **stck_ptr[2];
    size_t  i_min;
    size_t  i_max;

    stck_ptr[0] = stack_A;
    stck_ptr[1] = stack_B;
    init_merge_chunks_of_one_size(data, &i_min, &i_max, stck_ptr);
    while (i_max || i_min)
    {
        if (i_max)
            oper_one_nchnk(stack_A, stack_B, *stck_ptr[1], data);
        i_max -= (i_max > 0);
        i_min -= (i_min > 0);
        if (i_min)
            oper_one_nchnk(stack_A, stack_B, *stck_ptr[0], data);
        i_min -= (i_min > 0);
        i_max -= (i_max > 0);
    }
    data->cur_flag = 0;
}

/*static void	o_tail_nchnks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data, t_dlist *second)
{
    if (data->i_A == data->i_B)
    {
        oper_one_nchnk(stack_A, stack_B, second);
    }
    else if (data->i_A > data->i_B)
    {
        oper_one_nchnk(stack_A, stack_B, stack_B);
        oper_one_nchnk(stack_A, stack_B, stack_A);
    }
    else if (data->i_A < data->i_B)
    {
        oper_one_nchnk(stack_A, stack_B, stack_A);
        oper_one_nchnk(stack_A, stack_B, stack_B);
    }
}
*/
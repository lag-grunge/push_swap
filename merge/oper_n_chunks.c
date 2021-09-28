#include "push_swap.h"
#include "merge_sort.h"

/* merge chunks of one size, accurately not more than this size
 * we operate one pair of chunks, then rotate merged result on the
 * bottom as these chunks are situated on top of the stacks A and B
 * we found size of chunks, if this size eq 0, it means this chunk new
 * one so we've rotated whole stack and can continue only with other
 * if it has chunk */

static int      crit_of_action(t_merge_data *data, t_dlist **stck_ptr[4], int mode, int oper)
{
    int ret1;
    int ret2;

    ret1 = 0;
    ret2 = 0;
    if (oper == from_b_to_a || oper == from_b_to_b)
        ret1 = (stck_ptr[cur_stack] == data->stack_B);
    else if (oper == from_a_to_a || oper == from_a_to_b)
        ret1 = (stck_ptr[cur_stack] == data->stack_A);
    if (!mode)
        return (ret1);
    if (oper == from_b_to_a || oper == from_b_to_b)
        ret2 = (get_pos(*data->stack_A) > get_pos(*data->stack_B));
    else if (oper == from_a_to_a || oper == from_a_to_b)
        ret2 = (get_pos(*data->stack_A) < get_pos(*data->stack_B));
    return (ret1 && ret2);
}

static size_t    oper_one_elem(t_merge_data *data, t_dlist **stck_ptr[4], int mode, int (*crit)())
{
    size_t  ret;

    ret = 0;
    if (stck_ptr[stack_for_input] == data->stack_A)
    {
        if (crit(data, stck_ptr, mode, from_b_to_a))
        {
            execute_command("pa", data->stack_A, data->stack_B);
            ret += execute_command("ra", data->stack_A, data->stack_B);
        }
        else if (crit(data, stck_ptr, mode, from_a_to_a))
            ret += execute_command("ra", data->stack_A, data->stack_B);
    }
    else if (stck_ptr[stack_for_input] == data->stack_B)
    {
        if (crit(data, stck_ptr, mode, from_a_to_b))
        {
            execute_command("pb", data->stack_A, data->stack_B);
            ret += execute_command("rb", data->stack_A, data->stack_B);
        }
        else if (crit(data, stck_ptr, mode, from_b_to_b))
            ret += execute_command("rb", data->stack_A, data->stack_B);
    }
    return (ret);
}

static size_t init_oper_one_nchnk(t_dlist **stck_ptr[4], t_merge_data *data, size_t *chunk_0, size_t *chunk_1)
{
    *chunk_0 = find_chunk_size(*stck_ptr[first_stack], data->cur_flag);
    *chunk_1 = find_chunk_size(*stck_ptr[second_stack], data->cur_flag);
    if (!*chunk_0 && stck_ptr[stack_for_input] == stck_ptr[first_stack])
        stck_ptr[stack_for_input] = stck_ptr[second_stack];
    if (!*chunk_1 && stck_ptr[stack_for_input] == stck_ptr[second_stack])
        stck_ptr[stack_for_input] = stck_ptr[first_stack];
    if (stck_ptr[stack_for_input] == data->stack_A)
        data->i_A++;
    else
        data->i_B++;
    return (*chunk_0 + *chunk_1);
}

static int oper_one_nchnk(t_dlist **stck_ptr[4], t_merge_data *data)
{
    size_t  chunk_0;
    size_t  chunk_1;
    size_t  chunk_res;

    chunk_res = init_oper_one_nchnk(stck_ptr, data, &chunk_0, &chunk_1);
    if (!chunk_res)
        return (0);
    while (chunk_0 || chunk_1)
    {
        stck_ptr[cur_stack] = stck_ptr[first_stack];
        if (chunk_0)
            chunk_0 -= oper_one_elem(data, stck_ptr, chunk_0 && chunk_1, &crit_of_action);
        stck_ptr[cur_stack] = stck_ptr[second_stack];
        if (chunk_1)
            chunk_1 -= oper_one_elem(data, stck_ptr, chunk_1 && chunk_0, &crit_of_action);
    }
    merge_fl_change_bottom(*stck_ptr[stack_for_input], chunk_res, data->cur_flag);
    data->cur_flag++;
    return (1);
}


static void init_merge_chunks_of_one_size(t_merge_data *data, size_t **i_min, size_t **i_max, t_dlist **stck_ptr[4])
{
    t_dlist **cur_stack;

    stck_ptr[first_stack] = data->stack_A;
    stck_ptr[second_stack] = data->stack_B;
    *i_min = &data->i_B;
    *i_max = &data->i_A;
    if (data->i_A <= data->i_B)
    {
        cur_stack = stck_ptr[second_stack];
        stck_ptr[second_stack] = stck_ptr[first_stack];
        stck_ptr[first_stack] = cur_stack;
        *i_min = &data->i_A;
        *i_max = &data->i_B;
    }
}

void    merge2_chunks_of_one_size(t_merge_data *data)
{
    t_dlist **stck_ptr[4];
    size_t  *i_min;
    size_t  *i_max;
    size_t  i;
    int     flag;

    init_merge_chunks_of_one_size(data, &i_min, &i_max, stck_ptr);
    i = *i_min;
    flag = i % 2;
    while (i)
    {
        if (i % 2 == flag || (*i_max / *i_min >= CHUNKS_DIFF))
            stck_ptr[stack_for_input] = stck_ptr[second_stack];
        else
            stck_ptr[stack_for_input] = stck_ptr[first_stack];
        oper_one_nchnk(stck_ptr, data);
        *i_max = *i_max - 1;
        *i_min = *i_min - 1;
        i--;
    }
    merge_fl_change(*stck_ptr[first_stack], -3, &data->cur_flag);
    data->cur_flag = 0;
}

void	merge_chunks_of_one_size(t_merge_data *data)
{
    t_dlist **stck_ptr[4];
    size_t  *i_min;
    size_t  *i_max;

    init_merge_chunks_of_one_size(data, &i_min, &i_max, stck_ptr);
    while (*i_max || *i_min)
    {
        stck_ptr[stack_for_input] = stck_ptr[second_stack];
        if (*i_max)
            oper_one_nchnk(stck_ptr, data);
        *i_min -= (*i_max > 0 && *i_min > 0);
        *i_max -= (*i_max > 0);
        stck_ptr[stack_for_input] = stck_ptr[first_stack];
        if (*i_min)
            oper_one_nchnk(stck_ptr, data);
        *i_max -= (*i_min > 0 && *i_max > 0);
        *i_min -= (*i_min > 0);
    }
    data->cur_flag = 0;
}
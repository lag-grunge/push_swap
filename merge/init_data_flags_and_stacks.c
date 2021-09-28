#include "push_swap.h"
#include "merge_sort.h"

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

static void find_dest_to_neigh_chain(t_dlist *stack, size_t *next_dest, size_t *prev_dest)
{
    size_t  z;
    size_t  flag;
    t_dlist *cur;

    cur = stack;
    flag = get_flag(cur);
    z = 1;
    cur = cur->next;
    while (is_same_chain(get_flag(cur), flag, 0) && cur != stack)
    {
        z++;
        cur = cur->next;
    }
    *next_dest = z;
    if (!prev_dest)
        return ;
    cur = stack;
    z = 1;
    cur = cur->prev;
    while (is_same_chain(get_flag(cur), flag, 0) && cur != stack)
    {
        z++;
        cur = cur->prev;
    }
    *prev_dest = z - 1;
}

static int operate_chain(t_merge_data *data, size_t *next_dest, size_t *prev_dest, size_t changes)
{
    t_dlist         **stack_A;
    t_dlist         **stack_B;
    static size_t   i;

    stack_A = data->stack_A;
    stack_B = data->stack_B;
    find_dest_to_neigh_chain(*stack_A, next_dest, prev_dest);
    if (!i && (get_flag(*stack_A) + 1 == 0 || get_flag(*stack_A) == 0))
        execute_n_command(rra, *prev_dest, data);
    else if (i % 2 == 1 && *next_dest > 1)
    {
            execute_n_command(pb, *next_dest, data);
            merge_fl_change_next(*stack_B, *next_dest, changes - 1 - data->cur_flag);
            data->cur_flag++;
            data->i_B++;
    }
    else
        execute_n_command(ra, *next_dest, data);
    if (++i == changes)
    {
        i = 0;
        return (0);
    }
    return (1);
}

static void minus_flag_chains2stack_b(t_dlist **stack_A, t_merge_data *data)
{
    size_t      next_dest;
    size_t      prev_dest;
    size_t      changes;
    size_t      ret;

    data->i_B = 0;
    changes = get_chain_changes(*stack_A);
    ret = operate_chain(data, &next_dest, &prev_dest, changes);
    while (ret)
        ret = operate_chain(data, &next_dest, NULL, changes);
    data->cur_flag = 0;
}

void    init_data_flags_and_stacks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data, t_stck_data *cmn_data)
{
    size_t  next_dest;
    size_t  prev_dest;

    data->stack_A = stack_A;
    data->stack_B = stack_B;
    data->cmd_array = cmn_data->cmd_array;
    data->op_lines = cmn_data->op_lines;
    if (data->algo_type == 0) {
        merge_fl_change(*stack_A, 0, NULL);
        half_2stack_b(stack_A, stack_B, cmn_data->size, data);
        data->cur_flag = 0;
    }
    else if (data->algo_type == 2) {
        data->cur_flag = 0;
        merge_fl_change(*stack_A, -2, NULL);
        minus_flag_chains2stack_b(stack_A, data);
        merge_fl_change(*stack_A, -3, &data->cur_flag);
        data->i_A = count_chunks(*stack_A);
        operate_chain(data, &next_dest, &prev_dest, 1);
    }
}
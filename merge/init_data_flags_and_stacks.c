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

static int is_same_chain(size_t a, size_t b)
{
    if ((a + 1 == 0) && (b + 1 == 0))
        return (1);
    if ((a + 1 > 1) && (b + 1 > 1))
        return (1);
    return (0);
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
    while (is_same_chain(get_flag(cur), flag) && cur != stack)
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
    while (is_same_chain(get_flag(cur), flag) && cur != stack)
    {
        z++;
        cur = cur->prev;
    }
    *prev_dest = z - 1;
}

static void    execute_n_command(int cmd_num, size_t n, t_merge_data *data)
{
    size_t  i;

    i = 0;
    while (i < n)
    {
        if (ra <= cmd_num && cmd_num < pa)
            data->cmd_array[cmd_num](data->stack_A);
        else if (rb <= cmd_num && cmd_num < pb)
            data->cmd_array[cmd_num](data->stack_B);
        else if (pa == cmd_num || (rr <= cmd_num && cmd_num <= ss))
            data->cmd_array[cmd_num](data->stack_A, data->stack_B);
        else if (pb == cmd_num)
            data->cmd_array[cmd_num](data->stack_B, data->stack_A);
        put_command(data->op_lines[cmd_num]);
        i++;
    }
}

static void operate_chain(t_merge_data *data, size_t *next_dest, size_t *prev_dest, size_t changes)
{
    t_dlist **stack_A;
    t_dlist **stack_B;
    static int i;

    stack_A = data->stack_A;
    stack_B = data->stack_B;
    find_dest_to_neigh_chain(*stack_A, next_dest, prev_dest);
    if (!i && (get_flag(*stack_A) + 1 == 0))
        execute_n_command(rra, *prev_dest, data);
    else if (i % 2 == 1) {
        execute_n_command(pb, *next_dest, data);
        merge_fl_change_next(*stack_B, *next_dest, changes - 1 - data->cur_flag);
        data->i_B++;
    }
    else if (!i || (i % 2 == 0 && i)) {
        execute_n_command(ra, *next_dest, data);
        if (!i)
            merge_fl_change_bottom(*stack_A, *next_dest + *prev_dest, data->cur_flag++);
        else
            merge_fl_change_bottom(*stack_A, *next_dest, data->cur_flag++);
        data->i_A++;
    }
    i++;
}

static size_t get_chain_changes(t_dlist *stack_A) {
    t_dlist *cur;
    size_t cur_flag;
    size_t next_flag;
    size_t changes;

    changes = 0;
    cur = stack_A;
    while (cur != stack_A || !changes)
    {
        cur_flag = get_flag(cur);
        next_flag = get_flag(cur->next);
        if (!is_same_chain(cur_flag, next_flag))
            changes++;
        cur = cur->next;
    }
    return (changes);
}

static void zero_flag_chunks2stack_b(t_dlist **stack_A, t_merge_data *data)
{
    size_t      next_dest;
    size_t      prev_dest;
    size_t      changes;

    data->i_A = 0;
    data->i_B = 0;
    data->cur_flag = 0;
    changes = get_chain_changes(*stack_A);
    operate_chain(data, &next_dest, &prev_dest, changes);
    while (data->i_A != changes / 2 || data->i_B != changes / 2) {
        operate_chain(data, &next_dest, NULL, changes);
    }
    data->cur_flag = 0;
}

void    init_data_flags_and_stacks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data, t_stck_data *cmn_data)
{
    data->stack_A = stack_A;
    data->stack_B = stack_B;
    data->cmd_array = cmn_data->cmd_array;
    data->op_lines = cmn_data->op_lines;
    if (data->algo_type == 0) {
        merge_fl_change(*stack_A, 0, 0);
        half_2stack_b(stack_A, stack_B, cmn_data->size, data);
        data->cur_flag = 0;
    }
    else if (data->algo_type == 2) {
        merge_fl_change(*stack_A, -2, 0);
        zero_flag_chunks2stack_b(stack_A, data);
    }
}
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

static int operate_chain(t_merge_data *data, size_t *next_dest, size_t *prev_dest, size_t changes)
{
    t_dlist         **stack_A;
    t_dlist         **stack_B;
    static size_t   i;

    stack_A = data->stack_A;
    stack_B = data->stack_B;
    find_dest_to_neigh_chain(*stack_A, next_dest, prev_dest);
    if (!i && (get_flag(*stack_A) + 1 == 0))
        execute_n_command(rra, *prev_dest, data);
    else if (i % 2 == 1 && *next_dest > 1) {
            execute_n_command(pb, *next_dest, data);
            merge_fl_change_next(*stack_B, *next_dest, changes / 2 - 1 - data->cur_flag);
            data->cur_flag++;
            data->i_B++;
        }
    else if ((i % 2 == 1) || (!i) || (i % 2 == 0 && i))
        execute_n_command(ra, *next_dest, data);
    if (++i == changes)
    {
        i = 0;
        return (0);
    }
    return (1);
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
    size_t      ret;

    changes = get_chain_changes(*stack_A);
    ret = operate_chain(data, &next_dest, &prev_dest, changes);
    while (ret)
        ret = operate_chain(data, &next_dest, NULL, changes);
}

/*static int crit_stop(t_dlist *stack_A)
{
    t_dlist     *cur;
    t_dlist     *next;

    cur = stack_A;
    next = NULL;
    while (cur != stack_A || next == NULL)
    {
        next = cur->next;
        if ((get_flag(cur) + 1 == 0) &&  (get_flag(next) + 1 == 0))
            return (1);
        cur = cur->next;
    }
    return (0);
}*/

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
        data->cur_flag = 0;
        data->i_A = 0;
        data->i_B = 0;
        merge_fl_change(*stack_A, -2, 0);
        zero_flag_chunks2stack_b(stack_A, data);
        merge_fl_change(*stack_A, -3, 0);
    }
}
#include "push_swap.h"
#include "merge_sort.h"

void    exec_n_cmd_merge(int cmd_num, size_t n, t_merge_data *data)
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


#include "push_swap.h"
#include "merge_sort.h"

size_t  find_bottom_chunk_size(t_dlist *stack)
{
    t_dlist     *cur;
    t_ps_data   *content;
    size_t      flag;
    size_t      ret;

    if (!stack)
        return (0);
    ret = 1;
    cur = stack->prev;
    content = cur->content;
    flag = content->flag;
    while (cur != stack)
    {
        cur = cur->prev;
        content = cur->content;
        if (flag != content->flag)
            break ;
        ret++;
    }
    return (ret);
}

size_t	find_chunk_size(t_dlist *stack, size_t cur_flag)
{
    size_t	    flag;
    size_t	    ret;
    t_dlist     *cur;
    t_ps_data   *content;

    if (!stack)
        return (0);
    content = stack->content;
    flag = content->flag;
    if (flag < cur_flag)
        return (0);
    ret = 1;
    cur = stack->next;
    content = cur->content;
    while (content->flag == flag && cur != stack)
    {
        ret++;
        cur = cur->next;
        content = cur->content;
    }
    return (ret);
}

static void move_bottom_chunk(t_merge_data *data, t_dlist **stack, size_t bottom_chunk)
{
    size_t  i;
    char    *op_line;

    i = 0;
    if (stack == data->stack_A)
        op_line = ft_strdup("rra");
    else
        op_line = ft_strdup("rrb");
    while (i < bottom_chunk)
    {
        execute_command(op_line, data->stack_A, data->stack_B);
        i++;
    }
    free(op_line);
}

void shift_small_bottom_chunk(t_merge_data *data, t_dlist **stck_ptr[4])
{
    size_t  bottom_chunk;
    size_t  forward_chunk;

    bottom_chunk = find_bottom_chunk_size(*stck_ptr[first_stack]);
    forward_chunk = find_chunk_size(*stck_ptr[first_stack], 0);
    if (forward_chunk / bottom_chunk >= CHUNKS_DIFF)
        move_bottom_chunk(data, stck_ptr[first_stack], bottom_chunk);
}
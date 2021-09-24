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
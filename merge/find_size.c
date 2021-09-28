#include "push_swap.h"
#include "merge_sort.h"

int is_same_chain(size_t a, size_t b, int mode)
{
    if (a == b)
        return (1);
    if (mode)
        return (0);
    if ((a + 1 > 1) && (b + 1 > 1))
        return (1);
    return (0);
}

size_t  find_bottom_chunk_size(t_dlist *stack)
{
    t_dlist     *cur;
    size_t      flag;
    size_t      ret;

    if (!stack)
        return (0);
    ret = 1;
    cur = stack->prev;
    flag = get_flag(cur);
    while (cur != stack)
    {
        cur = cur->prev;
        if (!is_same_chain(get_flag(cur), flag, 1))
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

    if (!stack)
        return (0);
    flag = get_flag(stack);
    if (flag < cur_flag)
        return (0);
    ret = 1;
    cur = stack->next;
    while (is_same_chain(get_flag(cur), flag, 1) && cur != stack)
    {
        ret++;
        cur = cur->next;
    }
    return (ret);
}

size_t  count_chunks(t_dlist *stack)
{
    t_dlist *cur;
    t_dlist *next;
    size_t  res;
    size_t  cur_flag;
    size_t  next_flag;

    if (!stack)
        return (0);
    res = 1;
    cur = stack;
    cur_flag = get_flag(cur);
    next = NULL;
    while (cur->next != stack)
    {
        next = cur->next;
        next_flag = get_flag(next);
        if (!is_same_chain(next_flag, cur_flag, 1))
            res++;
        cur = next;
        cur_flag = next_flag;
    }
    return (res);
}

size_t get_chain_changes(t_dlist *stack_A)
{
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
        if (!is_same_chain(cur_flag, next_flag, 0))
            changes++;
        cur = cur->next;
    }
    return (changes);
}


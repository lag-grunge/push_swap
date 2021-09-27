#include "push_swap.h"
#include "merge_sort.h"

static size_t correct_set_flag_second(t_dlist *cur)
{
    size_t  res;

    while (get_pos(cur->prev) < get_pos(cur))
    {
        *set_flag(cur->prev) = 0;
        cur = cur->prev;
        res++;
    }
    return (res);
}

void    merge_set_flag_second(t_dlist *cur, void *params)
{
    static int          flag;
    size_t              next_flag;
    size_t              cur_pos;
    size_t              prev_pos;
    size_t              next_pos;

    next_flag = get_flag(cur->next);
    cur_pos = get_pos(cur);
    next_pos = get_pos(cur->next);
    if (!flag || (next_flag == 0 && cur_pos < next_pos))
        *set_flag(cur) = 0;
    else
    {
        prev_pos = get_pos(cur->prev);
        if (prev_pos < cur_pos)
            *set_flag(cur) = get_flag(cur->prev);
        else
            *set_flag(cur) = get_flag(cur->prev) + 1;
    }
    if (!flag)
        flag = 1;
    if (next_flag == 0 && cur_pos < next_pos)
        *(size_t *) params =  1 + correct_set_flag_second(cur);
}

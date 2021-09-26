#include "push_swap.h"
#include "merge_sort.h"

/* merge_fl_change  - change flags
 * mode 0 - change in begin ( = pos of sorted array)
 * mode -1 - change when 1 chunk in stack
 * mode (>1) - change after merge of 2 chnks less length,
 * number of mode then is length of new chunk */

static void merge_set_flag_default(t_dlist *cur, void *flag)
{
    t_ps_data   *content;

    content = cur->content;
    if (!flag) {
        content->flag = -(1 + content->pos);
        return;
    }
    content->flag = *(size_t *)flag;
}

void 	merge_fl_change_bottom(t_dlist *stack_A, size_t count, size_t flag)
{
    t_dlist *cur;
    size_t  i;

    i = 0;
    cur = stack_A->prev;
    while (i < count)
    {
        merge_set_flag_default(cur, &flag);
        cur = cur->prev;
        i++;
    }
}

static void    merge_set_flag_chain(t_dlist *cur, void *params)
{
    t_ps_data   *content;
    t_ps_data   *content_next;
    t_ps_data   *content_prev;

    content = cur->content;
    content_next = cur->next->content;
    content_prev = cur->prev->content;
    if (content->pos < content_next->pos)
    {
        merge_set_flag_chain(cur->next, params);
        if (content_prev->pos < content->pos)
            content->flag = 1 + content_next->flag;
        else
            content->flag = -1;
    }
    else {
        if (content_prev->pos < content->pos)
            content->flag = 1;
        else
            content->flag = -1;
    }
}

void    merge_fl_change_next(t_dlist *stack, size_t count, size_t flag)
{
    size_t i;

    i = 0;
    while (i < count)
    {
        *set_flag(stack) = flag;
        stack = stack->next;
        i++;
    }
}

void 	merge_fl_change(t_dlist *stack_A, int mode, size_t flag)
{
    if (mode == -1)
        ft_dlstmap(stack_A, &merge_set_flag_default, &flag);
    else if (mode == 0)
        ft_dlstmap(stack_A, &merge_set_flag_default, NULL);
    else if (mode == -2)
        ft_dlstmap(stack_A, &merge_set_flag_chain, NULL);
}
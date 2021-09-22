#include "push_swap.h"

/* merge_fl_change  - change flags
 * mode 0 - change in begin ( = pos of sorted array)
 * mode -1 - change when 1 chunk in stack
 * mode (>1) - change after merge of 2 chnks less length,
 * number of mode then is length of new chunk */

static void merge_set_flag(t_dlist *cur, void *flag)
{
    t_ps_data   *content;

    content = cur->content;
    /*if (mode == 0)
    {
        content->flag = content->pos;
        return;
    }*/
    content->flag = *(size_t *)flag;
}

static void merge_set_flag_default(t_dlist *cur, void *flag)
{
    t_ps_data   *content;

    content = cur->content;
    if (!flag)
        content->flag = content->pos;
}

static void 	merge_fl_change_bottom(t_dlist *stack_A, int mode, size_t flag)
{
    t_dlist *cur;
    int     i;

    i = 0;
    cur = stack_A->prev;
    while (i < mode)
    {
        merge_set_flag(cur, &flag);
        cur = cur->prev;
        i++;
    }
}

/*static void 	merge_fl_change_next(t_dlist *stack_A, int mode, size_t flag)
{
    t_dlist *cur;

    cur = stack_A;
    merge_set_flag(cur, mode, flag);
    cur = cur->next;
    while (cur != stack_A)
    {
        merge_set_flag(cur, mode, flag);
        cur = cur->next;
    }
}*/

void 	merge_fl_change(t_dlist *stack_A, int mode, size_t flag)
{
    if (mode > 0)
    {
        merge_fl_change_bottom(stack_A, mode, flag);
        return;
    }
    if (mode == -1)
        ft_dlstmap(stack_A, &merge_set_flag, &flag);
    if (mode == 0)
        ft_dlstmap(stack_A, &merge_set_flag_default, NULL);
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
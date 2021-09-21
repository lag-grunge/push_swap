#include "push_swap.h"

/* merge_fl_change  - change flags
 * mode 0 - change in begin ( = pos of sorted array)
 * mode 1 - change when 1 chunk in stack
 * mode (>1) - change after merge of 2 chnks less length,
 * number of mode then is length of new chunk */

typedef struct s_merge_data
{
    size_t i_A;
    size_t i_B;
    size_t cur_flag;
}   t_merge_data;

static void set_flag(t_dlist *stack, size_t *flag)
{
    if (!flag)
    {
        cur->content->flag = cur->content->pos;
        return;
    }
    cur->content->flag = *flag;
}

void 	merge_fl_change(t_dlist **stack_A, int mode, size_t *flag)
{
	t_dlist *cur;
    size_t  i;

	cur = *stack_A;
    if (mode == 0 || mode == -1)
    {
        if (mode == 0)
            flag = NULL;
        set_flag(cur, flag);
        cur = cur->next;
        while (cur != *stack_A)
        {
            set_flag(cur, flag);
            cur = cur->next;
        }
        if (flag)
            *flag = *flag + 1;
        return;
    }
    cur = (*stack_A)->prev;
    i = 0;
    while (i < mode)
    {
        set_flag(cur, flag);
        cur = cur->prev;
        i++;
    }
    *flag = *flag + 1;
}

static void	o_tail_2chnks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data)
{
    if (data->i_A == data->i_B)
    {
        if (get_pos(*stack_A) < get_pos(*stack_B))
        {
            execute_command("pb", stack_A, stack_B);
            execute_command("rb", stack_A, stack_B);
            execute_command("rb", stack_A, stack_B);
            merge_fl_change(stack_B, 2, &data->cur_flag);
        }
        execute_command("pa", stack_A, stack_B);
        execute_command("ra", stack_A, stack_B);
        execute_command("ra", stack_A, stack_B);
        merge_fl_change(stack_A, 2, &data->cur_flag);
        return ;
    }
    if (get_pos(*stack_A) > get_pos((*stack_A)->next))
        execute_command("sa", stack_A, stack_B);
    execute_command("rr", stack_A, stack_B);
    execute_command("ra", stack_A, stack_B);
    merge_fl_change(stack_A, 2, &data->cur_flag);
    merge_fl_change(stack_B, 1, &data->cur_flag);
}

static int o_2chnks(t_dlist **stack_A, t_dlist **stack_B, size_t *cur_flag)
{
    int retA;
    int retB;

    retA = 0;
    retB = 0;
    if (get_pos(*stack_A) > get_pos((*stack_A)->next))
        retA = 1;
    if (get_pos(*stack_B) > get_pos((*stack_B)->next))
        retB = 1;
    if (retA && retB)
        execute_command("ss", stack_A, stack_B);
    else if (retA)
        execute_command("sa", stack_A, stack_B);
    else if (retB)
        execute_command("sb", stack_A, stack_B);
    execute_command("rr", stack_A, stack_B);
    execute_command("rr", stack_A, stack_B);
    merge_fl_change(stack_A, 2, cur_flag);
    merge_fl_change(stack_B, 2, cur_flag);
}

void init_2chnks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data)
{
    size_t  ib;

    ib = data->i_B;
    while (ib > 1) {
        o_2chnks(stack_A, stack_B, &data->cur_flag);
        ib -= 2;
    }
    data->i_A = data->i_A - data->i_B / 2;
    data->i_B = data->i_B - data->i_B / 2;
    if (!ib)
        return ;
    o_tail_2chnks(stack_A, stack_B, data);
}

void 	half_2stack_b(t_dlist **stack_A, t_dlist **stack_B, size_t size, t_merge_data *data)
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

size_t	find_chunk_size(t_dlist *stack, size_t chunk_size, size_t *cur_flag)
{
	size_t	flag;
	size_t	ret;
    t_dlist *cur;

    if (!stack)
        return (0);
	ret = 1;
	flag = stack->content->flag;
	cur = stack->next;
	while (stack->content->flag == flag && cur != stack)
	{
		ret++;
		stack = stack->next;
	}
	return (ret);
}

int oper_one_elem(t_dlist **stack_A, t_dlist **stack_B, t_dlist *cur_stack, t_dlist *stack_for_input)
{
    int     ret;

    ret = 0;
    if (get_pos(*stack_A) < get_pos(*stack_B) && stack_for_input == *stack_A)
        if (cur_stack == *stack_A)
            ret = execute_command("ra", stack_A, stack_B);
    if (get_pos(*stack_A) > get_pos(*stack_B) && stack_for_input == *stack_A)
        if (cur_stack == *stack_B)
            ret = execute_command("pa", stack_A, stack_B);
    if (get_pos(*stack_A) < get_pos(*stack_B) && stack_for_input == *stack_B)
        if (cur_stack == *stack_A)
            ret = execute_command("pb", stack_A, stack_B);
    if (get_pos(*stack_A) > get_pos(*stack_B) && stack_for_input == *stack_B)
        if (cur_stack == *stack_B)
            ret = execute_command("rb", stack_A, stack_B);
    return (ret);
}

void	oper_one_nchnks(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data, t_dlist *stack_for_input)
{
    size_t chunk_a;
    size_t chunk_b;

    chunk_a = find_chunk_size(*stack_A);
    chunk_b = find_chunk_size(*stack_B);
    while (chunk_a && chunk_b)
    {
        chunk_a -= oper_one_elem(stack_A, stack_B, *stack_A, stack_for_input);
        chunk_b -= oper_one_elem(stack_A, stack_B, *stack_B, stack_for_input);
    }
    if (!chunk_a)
    {

    }
}

void	merge_chunks_of_one_size(t_dlist **stack_A, t_dlist **stack_B, t_merge_data *data, size_t max_chunk_size)
{
    t_dlist *first;
    t_dlist *second;
    size_t  i_min;
    size_t  iter;
    void    (*oper_chunk)(t_dist **, t_dlist **, t_merge_data *, size_t);

    first = stack_A;
    second = stack_B;
    i_min = data->i_B;
    oper_chunk = oper;
    if (data->i_A <= data->i_B)
    {
        first = stack_B;
        second = stack_A;
        i_min = data->i_A;
    }
    iter = i_min / 2;
    while (i_min > 1) {
        oper_one_nchnks_2A(first, second, data, max_chunk_size);
        oper_one_nchnks(second, first, data, max_chunk_size);
        i_min -= 2;
    }
    data->i_A = data->i_A - iter;
    data->i_B = data->i_B - iter;
    if (!i_min)
        return ;
    o_tail_nchnks(stack_A, stack_B, data);
}

void 	merge_sort(t_dlist **stack_A, t_dlist **stack_B, t_stck_data *cmn_data)
{
	size_t          max_chunk_size;
    t_merge_data    data;

    merge_fl_change(stack_A, 0, 0);
    half_2stack_b(stack_A, stack_B, cmn_data->size, &data);
    init_2chnks(stack_A, stack_B, &data);
	max_chunk_size = 2;
	while (data->i_A > 1 && data->i_B > 0)
	{
		merge_chunks(stack_A, stack_B, data, max_chunk_size);
		max_chunk_size *= 2;
	}
	return ;	
}

//ПЕРЕБРОСИТЬ ПОЛОВИНУ В СТЕК Б
//РАЗМЕР ЦЕПОЧЕК = 1
//ПОКА НЕ ПОЛУЧИТСЯ БОЛЬШАЯ ЦЕПОЧКА (=data->size)
//	ОБЪЕДИНЯТЬ ЦЕПОЧКИ (ИЗ РАЗНЫХ СТЕКОВ >= 2 из ОДНОГО ЕСЛИ == 1, кроме случая когда на конце осталось по 1 элементу ) 


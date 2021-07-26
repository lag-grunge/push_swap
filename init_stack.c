#include "push_swap.h"
#include "libft.h"


/*		ВЫДЕЛИТЬ МАССИВА ЦЕЛЫХ ЧИСЕЛ РАЗМЕРОВ В КОЛИЧЕСТВО ЭЛЕМЕНТОВ
			ДЛЯ КАЖДОГО АРГУМЕНТА НАЧИНАЯ С ПОСЛЕДНЕГО
				СДЕЛАТЬ СПЛИТ АРГУМЕНТА НА ЭЛЕМЕНТЫ
				ДЛЯ КАЖДОГО ЭЛЕМЕНТА СПЛИТА НАЧИНАЯ С ПОСЛЕДНЕГО
					ПЕРЕВЕСТИ В ЦЕЛОЕ
					БЫЛО ЛИ ТАКОЕ ЧИСЛО ЕСЛИ ДА
						ОСВОБОДИТЬ ПАМЯТЬ
						ЗАВЕРШИТЬ ПРОГРАММУ
					ЗАПИСАТЬ ЧИСЛО В МАССИВ НАВЕРХ СТЕКА (МАССИВ1)
*/

int	check_is_uniq(t_list *stack, int elem)
{
	while (stack)
	{
		if (elem == ((t_ps_data *)(stack->content))->val)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	add_new_elem(t_list **stack, int elem)
{
	t_ps_data	*new_data;
	t_list		*new_list;

	new_data = (t_ps_data *)malloc(sizeof(t_ps_data) * 1);
	new_data->val = elem;
	new_data->pos = -1;
	new_list = ft_lstnew(new_data);
	if (!new_list)
		return (0);
	ft_lstadd_front(stack, new_list);
	return (1);
}

size_t	ft_spllen(char **spl)
{
	size_t	i;

	i = 0;
	while (*spl++)
		i++;
	return (i);
}

int	proc_elem(t_list **stack, char **arg_sp, int j)
{
	int elem;

	elem = ft_atoi(arg_sp[j]);
	if (!(check_is_uniq(*stack, elem))) 
		return (2);
	else if (!(add_new_elem(stack, elem)))
		return (3);
	return (0);
}

t_list	*init_stack(int argc, char *argv[])
{
	int		i;
	int		j;
	char	**arg_sp;
	int		ret;
	t_list *stack;

	i = argc;
	ret = 0;
	stack = NULL;
	while (--i > 0)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(3, (void *)stack, &free_stack); 
		j = ft_spllen(arg_sp);
		while (--j > -1 && ret == 0)
			ret = proc_elem(&stack, arg_sp, j);
		free_split(arg_sp);
		if (ret)
			exit_error(ret, (void *)stack, &free_stack);
	}
	return (stack);
}

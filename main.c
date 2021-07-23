#include "push_swap.h"
#include "libft.h"

void	free_split(void *data)
{
	size_t	i;
	char 	**arg_sp;

	i = 0;
	arg_sp = (char **)data;
	while (arg_sp[i])
	{
		free(arg_sp[i]);
		i++;
	}
	free(arg_sp);
}

void	free_stack(void *data)
{
	t_list	*stack;

	stack = (t_list *)data;
	ft_lstclear(&stack, &free);
}

void exit_error(size_t err, void *strct, void (*free_func)(void *))
{
	if (strct)
	{
		if (free_func == &free_stack)
			free_func(strct);
		if (free_func == &free_split)
			free_func(strct);
	}
	if (err == 1)
		write(2, "Error: non-integer elem\n", 24);
	else if (err == 2)
		write(2, "Error: non-unique elem\n", 23);
	else if (err == 3)
		write(2, "Error: cannot allocate memory or non-correct arg\n", 48);
	exit (err);
}
//	ПРОЧИТАТЬ ДАННЫЕ В СТЕК ( СТРОКА ПОСЛЕДНИЙ ЭТО ВНИЗУ СТЕКА, ПЕРВЫЙ - ВВЕРХУ)
//		ДЛЯ КАЖДОГО АРГУМЕНТА
//			СДЕЛАТЬ СПЛИТ АРГУМЕНТА
//			ДЛЯ КАЖДОГО ЭЛЕМЕНТА СПЛИТА АРГУМЕНТА
//				ПРОВЕРИТЬ ВХОДНОЙ ЭЛЕМЕНТ АРГУМЕНТА
//					ЦЕЛОЕ ЛИ ЧИСЛО ЕСЛИ НЕТ
//						ВЫВЕСТИ СООБЩЕНИЕ ОБ ОШИБКЕ
//						ОСВОБОДИТЬ ПАМЯТЬ СПЛИТА
//						ЗАВЕРШИТЬ ПРОГРАММУ
//				ПЕРЕЙТИ К СЛЕДУЮЩЕМУ ЭЛЕМЕНТУ АРГУМЕНТА
//			ПРИБАВИТЬ КОЛИЧЕСТВО ЭЛЕМЕНТОВ
//			ОСВОБОДИТЬ ПАМЯТЬ СПЛИТА
//			ПЕРЕЙТИ К СЛЕДУЮЩЕМУ АРГУМЕНТУ

int check_is_zero(char *s) ///////
{
	if (*s != '+' && *s != '-' && *s != '0')
		return (0);
	while (*s && *s == '0')
		s++;
	if (!*s)
		return (1);
	else
		return (0);
}

size_t	check_input(int argc, char *argv[])
{
	int		i;
	int		j;
	int		elem;
	int		size;
	char	**arg_sp;
	
	i = 0;
	size = 0;
	while (++i < argc)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(3, NULL, NULL);
		j = -1;
		while (arg_sp[++j])
		{
			elem = ft_atoi(arg_sp[j]);
			if (!elem && !(check_is_zero(arg_sp[j])))
				exit_error(1, (void *)arg_sp, &free_split);
		}
		size += j;
		free_split(arg_sp);
	}
	return (size);
}


//		ВЫДЕЛИТЬ МАССИВА ЦЕЛЫХ ЧИСЕЛ РАЗМЕРОВ В КОЛИЧЕСТВО ЭЛЕМЕНТОВ
//			ДЛЯ КАЖДОГО АРГУМЕНТА НАЧИНАЯ С ПОСЛЕДНЕГО
//				СДЕЛАТЬ СПЛИТ АРГУМЕНТА НА ЭЛЕМЕНТЫ
//				ДЛЯ КАЖДОГО ЭЛЕМЕНТА СПЛИТА НАЧИНАЯ С ПОСЛЕДНЕГО
//					ПЕРЕВЕСТИ В ЦЕЛОЕ
//					БЫЛО ЛИ ТАКОЕ ЧИСЛО ЕСЛИ ДА
//						ОСВОБОДИТЬ ПАМЯТЬ
//						ЗАВЕРШИТЬ ПРОГРАММУ
//					ЗАПИСАТЬ ЧИСЛО В МАССИВ НАВЕРХ СТЕКА (МАССИВ1)
//

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

//		ВЫДЕЛИТЬ ДВА МАССИВА ЦЕЛЫХ ЧИСЕЛ РАЗМЕРОВ В КОЛИЧЕСТВО ЭЛЕМЕНТОВ
//		ОТСОРТИРОВАТЬ МАССИВ (СОРТИРОВКА ВСТАВКОЙ)
//			ДЛЯ КАЖДОГО ЭЛЕМЕНТА МАССИВА
//				СРАВНИВАТЬ НОВОЕ ЧИСЛО С ПОСЛЕДНИМ ЭЛЕМЕНТОМ МАССИВА СОРТИРОВКОЙ
//				ПОКА НЕ БУДЕТ БОЛЬШЕ НОВЫЙ ЭЛЕМЕНТ СРАВНИТЬ С ПРЕДЫДУЩИМ И НЕ ДОЙДЕМ ДО НАЧАЛА
//					ПРИРАВНЯТЬ СЛЕДУЮЩИЙ ПРЕДЫДУЩЕМУ
//				ЗАПИСАТЬ НОВОЕ ЧИСЛО В МАССИВ СОРТИРОВКОЙ НА ТЕКУЩЕЕ МЕСТО

void	insert(t_list *cur, size_t i, int *arr_sorted)
{
	int	new_elem;

	new_elem = ((t_ps_data *)(cur->content))->val;
	while (i > 0 && new_elem < arr_sorted[i])
	{
		arr_sorted[i] = arr_sorted[i - 1];
		i--;
	}
	arr_sorted[i] = new_elem;
}

void	correct_pos(t_list *stack, int *arr_sorted)
{
	int		elem;
	size_t	i;
	t_list	*cur;

	cur = stack;
	while (cur)
	{
		elem = ((t_ps_data *)(cur->content))->val;
		i = 0;
		while (elem != arr_sorted[i])
			i++;
		((t_ps_data *)(cur->content))->pos = i;
		cur = cur->next;
	}
}

int		*insertion_sort(t_list *stack, size_t size)
{
	int		*arr_sorted;
	size_t	i;
	t_list  *cur;

	cur = stack;
	arr_sorted = (int *)malloc(sizeof(int) * size);
	if (!arr_sorted)
		exit_error(3, NULL, NULL);
	i = 0;
	while (i < size)
	{
		insert(cur, i, arr_sorted);
		cur = cur->next;
		i++;
	}
	correct_pos(stack, arr_sorted);
	return (arr_sorted);
}

void	rotate(t_list **stack)
{
	t_list	*elem;

	elem = *stack;
	if (!elem || !elem->next)
		return ;
	*stack = elem->next;
	(ft_lstlast(*stack))->next = elem;
	elem->next = NULL;
}

void	push(t_list **stack1, t_list **stack2)
{
	t_list	*elem;

	elem = *stack2;
	if (!elem)
		return ;
	*stack2 = elem->next;
	elem->next = NULL;
	ft_lstadd_front(stack1, elem);
}

void	swap(t_list **stack)
{
	t_list	*elem;
	t_list	*second;
	t_list	*third;

	elem = *stack;
	if (!elem)
		return ;
	second = elem->next;
	if (!second)
		return ;
	third = second->next;
	second->next = elem;
	elem->next = third;
	*stack = second;
}

#include <stdio.h>
t_list	*partition(t_list **stack1, size_t size, int medium)
{
	void print_stack(t_list *);
	size_t	i;
	t_list	*stack2;

	i = 0;
	stack2 = NULL;
	while (i++ < size)
	{
		if (((t_ps_data *)((*stack1)->content))->val <= medium)
		{
			push(&stack2, stack1); ///////
			printf("pb\n");
			print_stack(*stack1);
			write(1, "\n", 1);
			print_stack(stack2);
		}
		else
		{
			rotate(stack1); //////
			printf("ra\n");
			print_stack(*stack1);
			write(1, "\n", 1);
			print_stack(stack2);
		}
	}
	return (stack2);
}

void print_arr(int *arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		printf("%d\n", arr[size - i - 1]);
		i++;
	}
}

void print_stack(t_list *stack)
{
	t_list *cur;

	cur = stack;
	while (cur)
	{
		printf("%d %zu\n", ((t_ps_data *)(cur->content))->val, ((t_ps_data *)(cur->content))->pos);
		cur = cur->next;
	}
}

void	small_size(t_list **stack_A, int size)
{
	if (size == 2)
		small_2(stack_A);
	else if (size == 3) 
		small_3(stack_A);
	else if (size == 4) 
		small_4(stack_A);
	else if (size == 5) 
		small_5(stack_A);

	
	exit_error(0, (void *)stack_A, &free_stack);
}

int main(int argc, char *argv[])
{
	int		size_A;
	int		size;
	t_list *stack_A;
	t_list *stack_B;
	int	*arr_sorted;

//	ПРОЧИТАТЬ ДАННЫЕ В СТЕК ( СТРОКА ПОСЛЕДНИЙ ЭТО ВНИЗУ СТЕКА, ПЕРВЫЙ - ВВЕРХУ)

//		ПРОВЕРИТЬ ДАННЫЕ
	size = check_input(argc, argv);
	size_A = size;
//		ЗАПИСАТЬ ДАННЫЕ В СТЕК
	stack_A = init_stack(argc, argv);
//	ОТСОРТИРОВАТЬ МАССИВ и произвести изменения в списке 
	arr_sorted = insertion_sort(stack_A, size);


//
//	ОТСОРТИРОВАТЬ СТЕК
//	ЕСЛИ РАЗМЕР 2 .. 5
	small_size(&stack_A, size);

//  ЕСЛИ РАЗМЕР БОЛЬШЕ 5
//		РАЗДЕЛИТЬ ДАННЫЕ ПОПОЛАМ МЕЖДУ СТЕКОМ A и СТЕКОМ B
		print_stack(stack_A);
		write(1, "\n", 1);
		stack_B = partition(&stack_A, size, arr_sorted[size / 2]); /////
		printf("stack_A\n");
		print_stack(stack_A);
		write(1, "\n", 3);
		printf("stack_B\n");
		print_stack(stack_B);

		
//		ОПРЕДЕЛИТЬ КАКОЕ ДЕЙСТВИЕ НЕОБХОДИМО, ИСХОДЯ ИЗ АЛГОРИТМА СОРТИРОВКИ
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК A
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК B
//			СДЕЛАТЬ ЛИ СВОП СТЕК A
//			СДЕЛАТЬ ЛИ СВОП СТЕК B
//		СДЕЛАТЬ ДЕЙСТВИЕ и ЗАПИСАТЬ ДЕЙСТВИЕ
//			
//

	
	
}

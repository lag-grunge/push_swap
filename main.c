#include <unistd.h>
#include <stdlib.h>
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
	t_stack	*stack;

	stack = (t_stack *)data;
	free(stack->arr);
	free(stack);
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
	if (err == 2)
		write(2, "Error: non-unique elem\n", 23);
	if (err == 3)
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
			if (!elem && !(check_is_zero(arg_sp[j]))) ///////
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

t_stack	*init_stack(size_t size, t_stack *peer)
{
	t_stack	*new_stack;

	new_stack = (t_stack *)malloc(sizeof(t_stack) * 1);
	if (!new_stack)
		exit_error(3, NULL, NULL);
	new_stack->cap = size;
	new_stack->top = 0;
	new_stack->arr = (int *)malloc(sizeof(int) * new_stack->cap);
	if (!new_stack->arr)
		exit_error(3, (void *)new_stack, &free_stack);
	if (peer)
	{
		new_stack->peer = peer;
		peer->peer = new_stack;
	}
	return (new_stack);
}

size_t	ft_spllen(char **arg_sp)
{
	size_t	i;

	i = 0;
	while (*arg_sp++)
		i++;
	return (i);
}

int	check_is_uniq_elem(t_stack *stack, int elem)
{
	size_t	i;

	i = 0;
	while (i < stack->top)
	{
		if (elem == stack->arr[i])
			return (0);
		i++;
	}
	return (1);
}

static void	fill_stack(t_stack *stack, int argc, char *argv[])
{
	size_t	i;
	int		j;
	int		elem;
	char	**arg_sp;

	i = argc;
	while (--i > 0)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(3, (void *)stack, &free_stack); 
		j = ft_spllen(arg_sp);
		while (--j > -1)
		{
			elem = ft_atoi(arg_sp[j]);
			if (!(check_is_uniq_elem(stack, elem))) /////
			{
				free_split(arg_sp);
				exit_error(2, (void *)stack, &free_stack);
			}
			stack->arr[stack->top++] = elem;
		}
		free_split(arg_sp);
	}
}

//		ВЫДЕЛИТЬ ДВА МАССИВА ЦЕЛЫХ ЧИСЕЛ РАЗМЕРОВ В КОЛИЧЕСТВО ЭЛЕМЕНТОВ
//		ОТСОРТИРОВАТЬ МАССИВ (СОРТИРОВКА ВСТАВКОЙ)
//			ДЛЯ КАЖДОГО ЭЛЕМЕНТА МАССИВА
//				СРАВНИВАТЬ НОВОЕ ЧИСЛО С ПОСЛЕДНИМ ЭЛЕМЕНТОМ МАССИВА СОРТИРОВКОЙ
//				ПОКА НЕ БУДЕТ БОЛЬШЕ НОВЫЙ ЭЛЕМЕНТ СРАВНИТЬ С ПРЕДЫДУЩИМ И НЕ ДОЙДЕМ ДО НАЧАЛА
//					ПРИРАВНЯТЬ СЛЕДУЮЩИЙ ПРЕДЫДУЩЕМУ
//				ЗАПИСАТЬ НОВОЕ ЧИСЛО В МАССИВ СОРТИРОВКОЙ НА ТЕКУЩЕЕ МЕСТО

void	insert(t_stack *stack, size_t cur, int *arr_sorted)
{
	int	new_elem;

	new_elem = stack->arr[stack->top - cur - 1];
	while (cur > 0 && new_elem < arr_sorted[stack->top - cur])
	{
		arr_sorted[stack->top - cur - 1] = arr_sorted[stack->top - cur];
		cur--;
	}
	arr_sorted[stack->top - cur - 1] = new_elem;
}

int		*insertion_sort(t_stack *stack)
{
	int		*arr_sorted;
	size_t	cur;

	arr_sorted = (int *)malloc(sizeof(int) * stack->cap);
	if (!arr_sorted)
		exit_error(3, NULL, NULL);
	
	cur = 0;
	while (cur < stack->cap)
		insert(stack, cur++, arr_sorted);
	return (arr_sorted);
}

void	rotate(t_stack *stack)
{
	int elem;
	size_t cur;

	elem = stack->arr[stack->top - 1];
	cur = 0;
	while (cur < stack->top - 1)
	{
		stack->arr[stack->top - cur - 1] = stack->arr[stack->top - cur - 2];
		cur++;
	}
	stack->arr[0] = elem;
}

void	push(t_stack *stack1)
{
	t_stack *peer;

	peer = stack1->peer;
	stack1->arr[stack1->top] = peer->arr[peer->top - 1];
	peer->top--;
	stack1->top++;
}

#include <stdio.h>
void 	partition(t_stack *stack1, t_stack *stack2, int medium)
{
	size_t	i;
	void print_arr(int *, size_t);

	i = stack1->top;
	while (i > 0)
	{
		if (stack1->arr[stack1->top - 1] > medium)
		{
			push(stack2); ///////
			printf("pb\n");
			print_arr(stack1->arr, stack1->top);
			write(1, "\n", 1);
			print_arr(stack2->arr, stack2->top);
		}
		else
		{
			rotate(stack1); //////
			printf("ra\n");
			print_arr(stack1->arr, stack1->top);
			write(1, "\n", 1);
			print_arr(stack2->arr, stack2->top);
		}
		i--;
	}
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

int main(int argc, char *argv[])
{
	int		size;
	t_stack *stack_A;
	t_stack *stack_B;
	int	*arr_sorted;

//	ПРОЧИТАТЬ ДАННЫЕ В СТЕК ( СТРОКА ПОСЛЕДНИЙ ЭТО ВНИЗУ СТЕКА, ПЕРВЫЙ - ВВЕРХУ)

//		ПРОВЕРИТЬ ДАННЫЕ
	size = check_input(argc, argv);


//		ВЫДЕЛИТЬ МАССИВА ЦЕЛЫХ ЧИСЕЛ РАЗМЕРОВ В КОЛИЧЕСТВО ЭЛЕМЕНТОВ
	stack_A = init_stack(size, NULL);  
	fill_stack(stack_A, argc, argv);
//
//	ОТСОРТИРОВАТЬ МАССИВ И ВЫДЕЛИТЬ ПАМЯТЬ ПОД СТЕК B
//		ВЫДЕЛИТЬ ДВА МАССИВА ЦЕЛЫХ ЧИСЕЛ РАЗМЕРОВ В КОЛИЧЕСТВО ЭЛЕМЕНТОВ

	stack_B = init_stack(size, stack_A);
	arr_sorted = insertion_sort(stack_A);

// 	print_arr(stack_A->arr, stack_A->top);
// 	write(1, "\n", 1);
//	print_arr(arr_sorted, size);


//
//	ОТСОРТИРОВАТЬ СТЕК
//		РАЗДЕЛИТЬ ДАННЫЕ ПОПОЛАМ МЕЖДУ СТЕКОМ A и СТЕКОМ B
		print_arr(stack_A->arr, stack_A->top);
		write(1, "\n", 1);
		partition(stack_A, stack_B, arr_sorted[(stack_A->cap - 1) / 2]); /////
		print_arr(stack_A->arr, stack_A->top);
		write(1, "\n", 1);
		print_arr(stack_B->arr, stack_B->top);

//			ДЛЯ КАЖДОГО ЭЛЕМЕНТА
//		ОПРЕДЕЛИТЬ КАКОЕ ДЕЙСТВИЕ НЕОБХОДИМО, ИСХОДЯ ИЗ АЛГОРИТМА СОРТИРОВКИ
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК A
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК B
//			СДЕЛАТЬ ЛИ СВОП СТЕК A
//			СДЕЛАТЬ ЛИ СВОП СТЕК B
//		СДЕЛАТЬ ДЕЙСТВИЕ
//			
//		ЗАПИСАТЬ ДЕЙСТВИЕ
//			
//

	
	
}
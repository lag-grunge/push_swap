
#include "push_swap.h"
#include "libft.h"

/*		ВЫДЕЛИТЬ ДВА МАССИВА ЦЕЛЫХ ЧИСЕЛ РАЗМЕРОВ В КОЛИЧЕСТВО ЭЛЕМЕНТОВ
		ОТСОРТИРОВАТЬ МАССИВ (СОРТИРОВКА ВСТАВКОЙ)
			ДЛЯ КАЖДОГО ЭЛЕМЕНТА МАССИВА
				СРАВНИВАТЬ НОВОЕ ЧИСЛО С ПОСЛЕДНИМ ЭЛЕМЕНТОМ МАССИВА СОРТИРОВКОЙ
				ПОКА НИ НЕ ДОЙДЕМ ДО НАЧАЛА И НЕ БУДЕТ БОЛЬШЕ НОВЫЙ ЭЛЕМЕНТ СРАВНИТЬ С ПРЕДЫДУЩИМ 
					ПРИРАВНЯТЬ СЛЕДУЮЩИЙ ПРЕДЫДУЩЕМУ
				ЗАПИСАТЬ НОВОЕ ЧИСЛО В МАССИВ СОРТИРОВКОЙ НА ТЕКУЩЕЕ МЕСТО
*/			

void	insert(t_list *cur, size_t i, int *arr_sorted)
{
	int	new_elem;

	new_elem = ((t_ps_data *)(cur->content))->val;
	while (i > 0 && new_elem < arr_sorted[i - 1])
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
		exit_error(3, NULL, NULL, NULL);
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

void	check_if_stack_sorted(t_list **stack, int chckr, t_stck_data *data)
{
	t_list	*cur;
	size_t	i;

	cur = *stack;
	i = 0;
	while (cur)
	{
		if (!(seek_pos(cur, i, 1)))
		{
			if (chckr)
				break ;
			return ;
		}
		i++;
		cur = cur->next;
	}
	if (i < data->size)
	{
		write(1, "KO\n", 3);
		exit_error(5, (void *)*stack, &free_stack, data);
	}
	else if (chckr)
		write(1, "OK\n", 3);
	else 
		exit_error(0, (void *)*stack, &free_stack, data);
}
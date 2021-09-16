#include "push_swap.h"

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
	t_dlist	*stack;

	stack = (t_dlist *)data;
	if (stack)
		ft_dlst_clear(&stack, &free);
}

void exit_error(size_t err, void *strct, free_func f, t_stck_data *data)
{
	if (strct)
		f(strct);
	if (data)
	{
		if (data->arr_sorted)
			free(data->arr_sorted);
		free(data);
	}
	if (err == 1)
		write(2, "Error: non-integer elem\n", 24);
	else if (err == 2)
		write(2, "Error: non-unique elem\n", 23);
	else if (err == 3)
		write(2, "Error: cannot allocate memory or non-correct arg\n", 48);
	else if (err == 4)
		write(2, "Error: checker got non-correct command\n", 39);
	else if (err == 5)
		write(2, "Error: stack_A is not full or not sorted\n", 41);
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

int check_is_zero_or_overflow(char *s, int elem) ///////
{
	if (!elem || elem == -1)
	{
		if (*s != '+' && *s != '-' && *s != '0')
			return (0);
		while (*s && *s == '0')
			s++;
		if (!*s || ((elem == -1) && (*s != '1' || s[1])))
			return (1);
		else
			return (0);
	}
	else
		return (1);
}

void	check_input(int argc, char *argv[], t_stck_data *data)
{
	int		i;
	int		j;
	int		elem;
	char	**arg_sp;
	
	i = 0;
	data->size = 0;
	while (++i < argc)
	{
		arg_sp = ft_split(argv[i], ' ');
		if (!arg_sp)
			exit_error(3, NULL, NULL, data);
		j = -1;
		while (arg_sp[++j])
		{
			elem = ft_atoi(arg_sp[j]);
			if (!(check_is_zero_or_overflow(arg_sp[j], elem)))
				exit_error(1, (void *)arg_sp, &free_split, data);
		}
		data->size += j;
		free_split(arg_sp);
	}
	if (!data->size)
		exit_error(0, NULL, NULL, data);
	data->i_A = data->size;
	data->i_B = 0;
}


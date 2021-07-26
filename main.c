#include "push_swap.h"

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
	int		part;
	int		size;
	t_list *stack_A;
	t_list *stack_B;
	int	*arr_sorted;

//	ПРОЧИТАТЬ ДАННЫЕ В СТЕК ( СТРОКА ПОСЛЕДНИЙ ЭТО ВНИЗУ СТЕКА, ПЕРВЫЙ - ВВЕРХУ)

//		ПРОВЕРИТЬ ДАННЫЕ
	size = check_input(argc, argv);
//		ЗАПИСАТЬ ДАННЫЕ В СТЕК
	stack_A = init_stack(argc, argv);
	stack_B = NULL;
//	ОТСОРТИРОВАТЬ МАССИВ и произвести изменения в списке 
	arr_sorted = insertion_sort(stack_A, size);
//  ПРОВЕРИТЬ ОТСОРТИРОВАН ЛИ СТЕК, если ДА завершаем программу.
	check_if_list_sorted(); //////
	
//
//	ОТСОРТИРОВАТЬ СТЕК
//	ЕСЛИ РАЗМЕР 2 .. 5
	if (size > 1 && size < 6)
	{
		small_size(&stack_A, size);
	}
	else
	{
//  ЕСЛИ РАЗМЕР БОЛЬШЕ 5
//		РАЗДЕЛИТЬ ДАННЫЕ ПОПОЛАМ МЕЖДУ СТЕКОМ A и СТЕКОМ B
		part = how_many_parts(); ////////
		while (1)
		{
		
			print_stack(stack_A);
			write(1, "\n", 1);
			partition(&stack_B, &stack_A, part, size); /////
			printf("stack_A\n");
			print_stack(stack_A);
			write(1, "\n", 3);
			printf("stack_B\n");
			print_stack(stack_B);
		}
	}
		
//		ОПРЕДЕЛИТЬ КАКОЕ ДЕЙСТВИЕ НЕОБХОДИМО, ИСХОДЯ ИЗ АЛГОРИТМА СОРТИРОВКИ
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК A
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК B
//			СДЕЛАТЬ ЛИ СВОП СТЕК A
//			СДЕЛАТЬ ЛИ СВОП СТЕК B
//		СДЕЛАТЬ ДЕЙСТВИЕ и ЗАПИСАТЬ ДЕЙСТВИЕ
//			
//

	
	
}

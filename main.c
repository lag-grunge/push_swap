#include "push_swap.h"

void	small_size(t_list **stack_A, int size)
{
//	print_stack(*stack_A);
	if (size == 2)
		small_2(stack_A);
	else if (size == 3) 
		small_3(stack_A, 0);
	else if (size == 4) 
		small_4(stack_A);
	else if (size == 5) 
		small_5(stack_A);
//	print_stack(*stack_A);
}

int main(int argc, char *argv[])
{
	t_list 	**stack_A;
	int		size;
	int		*arr_sorted;
	t_list 	**stack_B;

//	ПРОЧИТАТЬ ДАННЫЕ В СТЕК ( СТРОКА ПОСЛЕДНИЙ ЭТО ВНИЗУ СТЕКА, ПЕРВЫЙ - ВВЕРХУ)

	
//		ПРОВЕРИТЬ ДАННЫЕ
	size = check_input(argc, argv);
//		ЗАПИСАТЬ ДАННЫЕ В СТЕК
	stack_A = (t_list **)malloc(sizeof(t_list *) * 1);
	init_stack(argc, argv, stack_A);
	stack_B = NULL;
//	ОТСОРТИРОВАТЬ МАССИВ и произвести изменения в списке 
	arr_sorted = insertion_sort(*stack_A, size);
//	print_arr(arr_sorted, size);
//  ПРОВЕРИТЬ ОТСОРТИРОВАН ЛИ СТЕК, если ДА завершаем программу.
	check_if_stack_sorted(stack_A, size, 0, arr_sorted); //////

//
//	ОТСОРТИРОВАТЬ СТЕК
//	ЕСЛИ РАЗМЕР 2 .. 5
	if (size > 1 && size < 6)
	{
		small_size(stack_A, size);
		exit_error(0, (void *)*stack_A, &free_stack, arr_sorted);
	}
	else
//  ЕСЛИ РАЗМЕР БОЛЬШЕ 5
	big_sort(stack_A, stack_B, size);

		
//		ОПРЕДЕЛИТЬ КАКОЕ ДЕЙСТВИЕ НЕОБХОДИМО, ИСХОДЯ ИЗ АЛГОРИТМА СОРТИРОВКИ
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК A
//			НАДО ЛИ ПРОВЕРНУТЬ СТЕК B
//			СДЕЛАТЬ ЛИ СВОП СТЕК A
//			СДЕЛАТЬ ЛИ СВОП СТЕК B
//		СДЕЛАТЬ ДЕЙСТВИЕ и ЗАПИСАТЬ ДЕЙСТВИЕ
//			
//

	
	
}

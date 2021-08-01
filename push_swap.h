#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_ps_data	{
	int		val;
	size_t	pos;
}				t_ps_data;

/* ОСВОБОЖДЕНИЕ ПАМЯТИ */
void	free_split(void *data);
void	free_stack(void *data);
void exit_error(size_t err, void *strct, void (*free_func)(void *));


/* СОРТИРОВКА ЭЛЕМЕНТОВ СТЕКА В МАССИВЕ И ДОБАВЛЕНИЕ ПОРЯДКОГО НОМЕРА 
  В ОТСОРТИРОВАННОМ МАССИВ В КАЖДЫЙ СООТВЕТСТВЕННЫЙ ЭЛЕМЕНТ*/
void	insert(t_list *cur, size_t i, int *arr_sorted);
int		*insertion_sort(t_list *stack, size_t size)
void	correct_pos(t_list *stack, int *arr_sorted);

/* БАЗОВЫЕ ОПЕРАЦИИ СОРТИРОВКИ */
void	rotate(t_list **stack);
void	push(t_list **stack1, t_list **stack2);
void	swap(t_list **stack);

/* CОРТИРОВКА 2, 3 */
void	small_size(t_list **stack_A, int size);

/* ОТЛАДОЧНАЯ ИНФОРМАЦИЯ  УДАЛИТЬ */

#include <stdio.h>
void 	print_arr(int *arr, size_t size);
void 	print_stack(t_list *stack);


#endif

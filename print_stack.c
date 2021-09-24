#include "push_swap.h"
#include <stdarg.h>

static void print_string(t_dlist *stack, void *arg)
{
    t_ps_data   *content;

    content = stack->content;
    if (!arg)
        printf("%zu %d %zu\n", content->pos, content->val, content->flag);
}

void	print_stack(t_dlist *stack)
{
    if (stack)
        ft_dlstmap(stack, &print_string, NULL);
}

void	print_arr(int *arr, size_t size)
{
	size_t	i;

	i = 0;
	write(1, "arr\n", 4);
	while (i < size)
	{
		printf("%zu %d\n", i, arr[i]);
		i++;
	}
}

void	debug_print_stack(t_dlist **stack_A, t_dlist **stack_B)
{
    if (stack_A) {
        printf("stack_A\n");
        print_stack(*stack_A);
    }
    else
        printf("stack_A is null\n");
	if (stack_B)
	{
		printf("stack_B\n");
		print_stack(*stack_B);
	}
    else
        printf("stack_A is null\n");
	sleep(7);
}
